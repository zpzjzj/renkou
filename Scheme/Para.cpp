#include "jsonUtil.hpp"
#include "Para.hpp"
#include <QJsonObject>
#include <QJsonArray>
#include <algorithm>

/**
 * @author zhaoping
 *
 */

namespace {
    using SelectedType = scheme::Para::SelectedType;
    QMap<SelectedType, QString> selectedTypeMap = {
        std::make_pair(SelectedType::INCOMPLETE, "incomplete"),
        std::make_pair(SelectedType::SINGLE, "single"),
        std::make_pair(SelectedType::MULTIPLE, "multiple")
    };

    QString toString(const SelectedType type) {
        return selectedTypeMap.value(type, "");
    }

    SelectedType toEnum(const QString& str) {
        return selectedTypeMap.key(str, SelectedType::INCOMPLETE);
    }

    using Tag = scheme::Para::Tag;
    QMap<Tag, QString> tagMap = {
        std::make_pair(Tag::SINGLE_SELECT, "single_select")
    };

    QString toString(const Tag tag) {
        return tagMap.value(tag, "");
    }

    Tag toTag(const QString& str) {
        return tagMap.key(str);
    }
}

QDebug& operator << (QDebug& out, const scheme::Para::SelectedType type) {
    out << toString(type);
    return out;
}

inline void initResource() {
    Q_INIT_RESOURCE(config);
}

namespace {
    const QString SPECIAL_PARA_PATH = ":/json/config/special_paras.json";
    scheme::Para::ParaMap buildParaMap() {
        initResource();
        scheme::Para::ParaMap res;
        QJsonArray jsonArray = jsonUtil::readFile(SPECIAL_PARA_PATH).array();
        for(const auto& objectJson : jsonArray) {
            QJsonObject object = objectJson.toObject();
            res.insert(object["key"].toString(), scheme::Para::readParas(object["val"].toArray()));
        }
        return res;
    }
}

//singleton
const scheme::Para::ParaMap& scheme::Para::getParaMap() {
    static const scheme::Para::ParaMap paraMap = buildParaMap();
    return paraMap;
}

scheme::Para::Para():mName(""), mKey(""), mVal(""),
    mTags(Para::TagSet()),
    mAndParas(Para::ParaSet()), mOrParas(Para::ParaSet()),
    mSelectedType(SelectedType::INCOMPLETE){
}

scheme::Para::Para(const QString& name,
                   const QString& key,
                   const QString& val,
                   const Para::ParaSet& andParas,
                   const Para::ParaSet& orParas,
                   const SelectedType& selectedType)
    :mName(name), mKey(key), mVal(val), mAndParas(andParas), mOrParas(orParas), mSelectedType(selectedType){}

scheme::Para::Para(Para&& para) :
    mName(std::move(para.mName)),
    mKey(std::move(para.mKey)),
    mVal(std::move(para.mVal)),
    mTags(std::move(para.mTags)),
    mAndParas(std::move(mAndParas)),
    mOrParas(std::move(mOrParas)),
    mSelectedType(para.mSelectedType) {}

namespace{
void addPara(const scheme::Para::ParaPtr& para, scheme::Para::ParaSet& paraSet){
    paraSet.push_back(para);
}

scheme::Para::ParaSet clone(scheme::Para::ParaSet set) {
    scheme::Para::ParaSet res(set.size());
    std::transform(set.begin(), set.end(), res.begin(), [](scheme::Para::ParaPtr ptr){
        return std::make_shared<scheme::Para>(*ptr);
    });
    return res;
}
}

scheme::Para::Para(const Para &para)
    :mName(para.mName), mKey(para.mKey), mVal(para.mVal), mTags(para.mTags), mSelectedType(para.mSelectedType){
    mAndParas = clone(para.mAndParas);
    mOrParas = clone(para.mOrParas);
}

void scheme::Para::addAndPara(const scheme::Para::ParaPtr& para) {
    addPara(para, mAndParas);
}

void scheme::Para::addOrPara(const scheme::Para::ParaPtr& para) {
    addPara(para, mOrParas);
}

void scheme::Para::rmOrPara(const QString& name) {
    std::remove_if(mOrParas.begin(), mOrParas.end(),
                   [&name](const ParaPtr& paraPtr){
        return paraPtr->getName() == name;}
    );
}

void scheme::Para::read(const QJsonObject &json, bool hasAlias) {
    mName = json["name"].toString();
    mKey = json["key"].toString();
    mVal = json["val"].toString();
    auto iter = json.find("selectedType");
    if(iter != json.end()) {
        mSelectedType = toEnum((*iter).toString());
    }
    iter = json.find("tags");
    if(iter != json.end()) {
        qDebug() << "find tag";
        for(auto jsonObject : (*iter).toArray()) {
            mTags.push_back(toTag(jsonObject.toString()));
            qDebug() << "get tag" << jsonObject.toString() << mName;
        }
    }
    mAndParas = readParas(json["andParas"].toArray(), hasAlias);
    mOrParas = readParas(json["orParas"].toArray(), hasAlias);
}

void scheme::Para::write(QJsonObject &json) const {
    json["name"] = mName;
    json["key"] = mKey;
    json["val"] = mVal;
    QJsonArray tagArray;
    for(auto tag : mTags) {
        tagArray.append(toString(tag));
    }
    json["tags"] = tagArray;
    json["selectedType"] = toString(mSelectedType);
    json["andParas"] = writeParas(mAndParas);
    json["orParas"] = writeParas(mOrParas);
}

void scheme::Para::setAndParas(const ParaSet& paras) {
    mAndParas = paras;
}

const scheme::Para::ParaSet &scheme::Para::getAndParas() const {
    return mAndParas;
}

scheme::Para::ParaSet &scheme::Para::getAndParas() {
    return mAndParas;
}

void scheme::Para::setOrParas(const ParaSet& paras) {
    mOrParas = paras;
}

const scheme::Para::ParaSet &scheme::Para::getOrParas() const {
    return mOrParas;
}

scheme::Para::ParaSet &scheme::Para::getOrParas() {
    return mOrParas;
}

scheme::Para::ParaSet scheme::Para::readParas(const QJsonArray &jsonArray, bool hasAlias) {
    ParaSet res;
    for (const auto& paraJson : jsonArray) {
        QJsonObject paraObject = paraJson.toObject();
        ParaPtr paraPtr(new Para());
        paraPtr->read(paraObject, hasAlias);
        if(hasAlias && getParaMap().contains(paraPtr->getName())) {
            auto &paras = getParaMap()[paraPtr->getName()];
            res.insert(res.end(), paras.begin(), paras.end());
        } else
            res.push_back(paraPtr);
    }
    return res;
}

QJsonArray scheme::Para::writeParas(const ParaSet &paraSet) {
    QJsonArray res;
    foreach (const auto &paraPtr, paraSet) {
        QJsonObject paraObj;
        paraPtr->write(paraObj);
        res.append(paraObj);
    }
    return res;
}
