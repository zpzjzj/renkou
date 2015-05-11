#include "../Scheme/jsonUtil.hpp"
#include "../Scheme/transfromPara.hpp"
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

ParasManager::ParasManager() : mMultiSelPara(nullptr) {}

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
    mAbstractSchemeList = scheme::map(mParaSet);
    return getAbstractSchemeList();
}

const QString& ParasManager::PARA_PATH() {
#ifdef __APPLE__
    static const QString PATH =
            QDir(QApplication::applicationDirPath())
            .absoluteFilePath("../Resources/para.json");
#else
    const QString PATH = "path_under_win";//TODO
#endif
    return PATH;
}
