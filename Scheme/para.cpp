#include "Para.hpp"
#include <QJsonObject>
#include <QJsonArray>
#include <algorithm>

/**
 * @author zhaoping
 *
 */

scheme::Para::Para():name(""), key(""), val(""),
    andParas(Para::ParaSet()), orParas(Para::ParaSet()){

}

scheme::Para::Para(const QString& name,
                   const QString& key,
                   const QString& val,
                   const Para::ParaSet& andParas,
                   const Para::ParaSet& orParas)
    :name(name), key(key), val(val), andParas(andParas), orParas(orParas){}

scheme::Para::Para(Para&& para) :
    name(std::move(para.name)),
    key(std::move(para.key)),
    val(std::move(para.val)),
    andParas(std::move(andParas)),
    orParas(std::move(orParas)){}

scheme::Para::~Para(){

}

namespace{
void addPara(const scheme::Para::ParaPtr& para, scheme::Para::ParaSet& paraSet){
    paraSet.push_back(para);
}
}

void scheme::Para::addAndPara(const scheme::Para::ParaPtr& para) {
    addPara(para, andParas);
}

void scheme::Para::addOrPara(const scheme::Para::ParaPtr& para) {
    addPara(para, orParas);
}

void scheme::Para::rmOrPara(const QString& name) {
    std::remove_if(orParas.begin(), orParas.end(),
                   [&name](const ParaPtr& paraPtr){
        return paraPtr->getName() == name;}
    );
}

void scheme::Para::read(const QJsonObject &json) {
    name = json["name"].toString();
    key = json["key"].toString();
    val = json["val"].toString();
    andParas = readParas(json["andParas"].toArray());
    orParas = readParas(json["orParas"].toArray());
}

void scheme::Para::write(QJsonObject &json) const {
    json["name"] = name;
    json["key"] = key;
    json["val"] = val;
    json["andParas"] = writeParas(andParas);
    json["orParas"] = writeParas(orParas);
}

void scheme::Para::setAndParas(const ParaSet& paras) {
    andParas = paras;
}

const scheme::Para::ParaSet &scheme::Para::getAndParas() const {
    return andParas;
}

scheme::Para::ParaSet &scheme::Para::getAndParas() {
    return andParas;
}

void scheme::Para::setOrParas(const ParaSet& paras) {
    orParas = paras;
}

const scheme::Para::ParaSet &scheme::Para::getOrParas() const {
    return orParas;
}

scheme::Para::ParaSet &scheme::Para::getOrParas() {
    return orParas;
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
