#include "Para.hpp"
#include <QJsonObject>
#include <QJsonArray>
#include <algorithm>

/**
 * @author zhaoping
 *
 */

QDebug& operator << (QDebug& out, const scheme::Para::SelectedType type) {
    using SelectedType = scheme::Para::SelectedType;
    switch (type) {
    case SelectedType::INCOMPLETE :
        out << "incomplete";
        break;
    case SelectedType::SINGLE :
        out << "single";
        break;
    case SelectedType::MULTIPLE :
        out << "multiple";
        break;
    default:
        break;
    }
    return out;
}

scheme::Para::Para():mName(""), mKey(""), mVal(""),
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
    mAndParas(std::move(mAndParas)),
    mOrParas(std::move(mOrParas)),
    mSelectedType(para.mSelectedType){}

namespace{
void addPara(const scheme::Para::ParaPtr& para, scheme::Para::ParaSet& paraSet){
    paraSet.push_back(para);
}
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

void scheme::Para::read(const QJsonObject &json) {
    mName = json["name"].toString();
    mKey = json["key"].toString();
    mVal = json["val"].toString();
    mAndParas = readParas(json["andParas"].toArray());
    mOrParas = readParas(json["orParas"].toArray());
}

void scheme::Para::write(QJsonObject &json) const {
    json["name"] = mName;
    json["key"] = mKey;
    json["val"] = mVal;
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

scheme::Para::ParaSet scheme::Para::readParas(const QJsonArray &jsonArray) {
    ParaSet res;
    for (const auto& paraJson : jsonArray) {
        QJsonObject paraObject = paraJson.toObject();
        ParaPtr paraPtr(new Para());
        paraPtr->read(paraObject);
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
