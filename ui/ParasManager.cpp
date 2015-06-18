#include "../Scheme/jsonUtil.hpp"
#include "../Scheme/stlUtil.hpp"
#include "ParasManager.hpp"
#include "paraUtil.hpp"
#include <numeric>
#include <QDir>
#include <QFile>
#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <utility>

const QString ParasManager::PARA_ORI_PATH = ":/display/config/para_ori.json";

ParasManager::ParasManager() : mMultiSelPara(nullptr) {
    connect(this, SIGNAL(paraChanged(const scheme::Para*)), this, SLOT(updateParasList(const scheme::Para*)));
}

bool ParasManager::saveToFile(QString fname) {
    qDebug() << "ParasManager::saveToFile" << fname;
    QFile file(fname);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open save file" << fname
                   << "in ParasManager::saveToFile(const QString fname)";
        qWarning() << "err: " << file.errorString();
        return false;
    }
    QJsonObject object;
    object["paras"] = scheme::Para::writeParas(mParaSet);
    QJsonDocument doc(object);
    file.write(doc.toJson());
    file.close();
    return true;
}

/**
 * @brief ParasManager::buildMap
 *        recursive function, insert <child, parent> pair into map
 * @param para
 */
void ParasManager::buildMap(scheme::Para& para) {
    for(auto& paraPtr : para.getAndParas()) {
        buildMap(*paraPtr);
        mParentMap.insert(paraPtr.get(), &para);
    }

    for(auto& paraPtr : para.getOrParas()) {
        buildMap(*paraPtr);
        mParentMap.insert(paraPtr.get(), &para);
    }
}

namespace {
    bool setValue(scheme::Para::SelectedType val, scheme::Para& para) {
        auto old = para.getSelectedType();
        para.setSelectedType(val);
        return val != old;
    }

    /**
     *  @return isChanged
     */
    bool setValue(bool val, scheme::Para& para) {
        return setValue(val ? scheme::Para::SelectedType::SINGLE :
                            scheme::Para::SelectedType::INCOMPLETE,
                      para);
    }

    /**
     * @brief isSelComplete
     *          complete when all andParas are selected, and orParas has 1 or more selected
     * @param para
     *          higher level para
     * @return
     */
    scheme::Para::SelectedType getSelectionType(scheme::Para& para) {
        using SelectedType = scheme::Para::SelectedType;
        const auto& orParas = para.getOrParas();
        SelectedType orRes = orParas.empty() ? SelectedType::SINGLE :
                std::accumulate(orParas.begin(), orParas.end(),
                                             SelectedType::INCOMPLETE,
                                             [](SelectedType x, const scheme::Para::ParaPtr yPtr) {
            auto y = yPtr->getSelectedType();
            if(y == SelectedType::INCOMPLETE)
                return x;
            else if(y == SelectedType::MULTIPLE)
                return SelectedType::MULTIPLE;
            else
                return x != SelectedType::INCOMPLETE ? SelectedType::MULTIPLE : SelectedType::SINGLE;
        });
        qDebug() << "getSelectionType()" << para.getName();
        qDebug() << "orRes" << orRes;
        const auto& andParas = para.getAndParas();
        return std::accumulate(andParas.begin(), andParas.end(), orRes, // all orParas can be view as 1 andPara
                                               [](SelectedType x, const scheme::Para::ParaPtr yPtr) {
            auto y = yPtr->getSelectedType();
            if(x == SelectedType::INCOMPLETE || y == SelectedType::INCOMPLETE)
                return SelectedType::INCOMPLETE;
            else if(x == SelectedType::MULTIPLE || y == SelectedType::MULTIPLE)
                return SelectedType::MULTIPLE;
            else
                return SelectedType::SINGLE;
        });
    }

namespace map {
    using ParaRepre = ParasManager::ParaRepre;
    using Map = ParasManager::ParaValueMap;
    /**
     * @brief getValue
     * @param para
     * @param map
     * @param key
     *      put para's value into map
     */
    void getValue(const scheme::Para& para, Map& map, const ParaRepre& key) {
        if(!util::isSelected(para))
            return;
        if(!para.getVal().isEmpty()) {
            qDebug() << "void getValue(const scheme::Para& para, Map& map, const ParaRepre& key)";
            qDebug() << "value :" << QString("(%1, %2)").arg(para.getName(), para.getVal());
            map.insertMulti(key, std::make_pair(para.getName(), para.getVal()));
        } else {
            for(auto& paraPtr : para.getOrParas()) {
                getValue(*paraPtr, map, key);
            }
        }
    }

    void produceMap_helper(const scheme::Para::ParaSet& paras, Map& map);
    void produceMap_helper(const scheme::Para& para, Map& map) {
        if(!para.getKey().isEmpty()) {//if has key
            auto key = std::make_pair(para.getName(), para.getKey());
            map.remove(key);//clear former res
            qDebug() << "void produceMap_helper(const scheme::Para& para, Map& map)";
            qDebug() << "key :" << QString("(%1, %2)").arg(key.first, key.second);
            getValue(para, map, key);
        } else {
            produceMap_helper(para.getAndParas(), map);//find subparts
        }
    }

    void produceMap_helper(const scheme::Para::ParaSet& paras, Map& map) {
        for(auto& paraPtr : paras) {
            produceMap_helper(*paraPtr, map);
        }
    }
}
    map::Map produceMap(const scheme::Para::ParaSet& paras) {
        map::Map res;
        map::produceMap_helper(paras, res);
        return res;
    }
#ifdef TRANSFORM_DEBUG
    void debugMap(map::Map map) {
        for(auto key : map.uniqueKeys()) {
            qDebug() << QString("(%1, %2):").arg(key.first, key.second);
            for(auto value : map.values(key)) {
                qDebug() << "-----"<< QString("(%1, %2)").arg(value.first, value.second);
            }
        }
    }
#endif

namespace transform {
    using ParaPair = ParasManager::ParaPair;
    std::vector<std::vector<ParaPair>> collect(const ::map::Map& map) {
        std::vector<std::vector<ParaPair>> res;
        for(auto key : map.uniqueKeys()) {
            std::vector<ParaPair> temp;
            auto values = map.values(key);
            temp.reserve(values.size());
            std::transform(values.begin(), values.end(), std::back_inserter(temp),
                           [&key](ParasManager::ParaRepre& value){
                return std::make_pair(key, value);
            });
            res.push_back(std::move(temp));
        }
        return res;
    }

    std::vector<std::vector<ParaPair>> combine(const std::vector<std::vector<ParaPair>>& paras) {
        using PairsSet = std::vector<std::vector<ParaPair>>;
        auto res = std::accumulate(paras.begin(), paras.end(),
                                   PairsSet{std::vector<ParaPair>()},
                                   [](PairsSet& set_x, const std::vector<ParaPair>& set_y){
            PairsSet res;
            for(auto &x : set_x) {
                for(auto &y : set_y) {
                    res.push_back(util::add(x, y));
                }
            }//combine every two collection
            return res;
        });
        return res;
    }

    QStringList toList(const std::vector<std::vector<ParaPair>>& paras) {
        QStringList res;
        res.reserve(paras.size());
        for(const std::vector<ParaPair>& set : paras) {//for each scheme
            QString str = std::accumulate(set.begin(), set.end(), QString(),
                            [](const QString& a, const ParaPair& b){
                auto str = b.second.first;
                return a.isEmpty() ? str : QString("%1/%2").arg(a).arg(str);
            });
            res.push_back(str);
        }
        return res;
    }
}
}

void ParasManager::read(QString filename) {
    auto doc = jsonUtil::readFile(filename);
    mParaSet = scheme::Para::readParas(doc.object()["paras"].toArray(), true);
    for(auto& paraPtr : mParaSet) {
        buildMap(*paraPtr);
        if(util::isMultiSelected(*paraPtr)) {
            if(mMultiSelPara == nullptr)
                mMultiSelPara = paraPtr.get();
            else {
                qWarning() << "multiple multi-selected para";
            }
        }
    }
    mResMap = produceMap(mParaSet);
    updateSchemeList();
}

scheme::Para* ParasManager::addOrPara(scheme::Para* para, const scheme::Para& orPara) {
    auto schemePtr = std::make_shared<scheme::Para>(orPara);
    para->addOrPara(schemePtr);
    auto ptr = schemePtr.get();
    mParentMap.insert(ptr, para);
    return ptr;
}

void ParasManager::setVal(bool val, scheme::Para* dest) {
    bool isSelectionTypeChanged = setValue(val, *dest);
    auto nextIter = mParentMap.find(dest);
    scheme::Para* curr;
    for( ;nextIter != mParentMap.end() && isSelectionTypeChanged;
            nextIter = mParentMap.find(curr)) {
        curr = nextIter.value();
        isSelectionTypeChanged = setValue(getSelectionType(*curr), *curr);
        qDebug() << "para" << curr->getName();
        qDebug() << "selectionTypeChanged:" << isSelectionTypeChanged;
        qDebug() << "type now:" << curr->getSelectedType();
    }

    //the whole para's state is changed
    if(nextIter == mParentMap.end() && isSelectionTypeChanged) {
        qDebug() << "ParasManager::setVal()" << "whole select state changed";
        if(mMultiSelPara == curr){ //not multi anymore
            mMultiSelPara = nullptr;
            emit multiParaChanged(mMultiSelPara);
        }
        else if(mMultiSelPara == nullptr && util::isMultiSelected(*curr)) {
            //new multi para
            mMultiSelPara = curr;
            emit multiParaChanged(curr);
        } else {
            emit paraStateChanged(curr);
        }
    }
    emit paraChanged(curr);
}

const ParasManager::AbstractSchemeList& ParasManager::update() {
    qDebug() << "AbstractScheme ParasManager::generate() const";
    static auto buffer = std::make_shared<SchemeBuffer>();
    AbstractSchemeList res;
    std::transform(mResList.begin(), mResList.end(), std::back_inserter(res),
                   [](std::vector<ParaPair> paras){
        std::shared_ptr<SchemeParameter> paraPtr = std::make_shared<SchemeParameterDefault>();
        for(const ParaPair& pair : paras) {
            paraPtr->set(pair.first.second, pair.second.second);
        }
        return std::make_shared<AbstractScheme>(paraPtr, buffer);
    });
    mAbstractSchemeList = std::move(res);
    return getAbstractSchemeList();
}

const QString& ParasManager::PARA_PATH() {
#ifdef __APPLE__
    static const QString PATH =
            QDir(QApplication::applicationDirPath())
            .absoluteFilePath("../Resources/para.json");
#else
    static const QString PATH = "config/para.json";//TODO
#endif
    return PATH;
}

/**
 * @brief ParasManager::updateParasList
 *          update map for the changed para
 * @param start
 */
void ParasManager::updateParasList(const scheme::Para* start) {
    auto changed = start;
    for(; changed != nullptr && changed->getKey().isEmpty(); changed = getParent(start)) {}
    if(changed == nullptr) {
        return;
    }//find key
    map::produceMap_helper(*changed, mResMap);//update
    updateSchemeList();
}
void ParasManager::updateSchemeList() {
    mResList = transform::combine(transform::collect(mResMap));
    mListModel.setStringList(transform::toList(mResList));
}

