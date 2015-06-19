#include "demoobject.h"

#include "paramitemjsonobject.h"
#include "paramvaluejsonobject.h"

#include <QFile>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include <QVariant>
#include <QTextStream>
#include <QFileInfo>

DemoObject::DemoObject()
{
}

DemoObject::DemoObject(const DemoObject &other){
    m_year = other.m_year;
    m_area = other.m_area;
    m_path = other.m_path;
}

DemoObject::DemoObject(const int year, const QString &area){
    setObject(year, area);
}



QString DemoObject::toString() const{
    QFileInfo info(this->m_path);
    return info.baseName();
}

QVariant DemoObject::toVariant(){
    QVariant variant(this->toString());
    return variant;
}

QJsonObject DemoObject::toJsonObject(){
    QJsonObject obj;

    ParamItemJsonObject yearItem(QObject::tr("base year"), ParamItemJsonObject::OPTIONS);
    yearItem.addOptionValues({QString::number(this->m_year)});

    ParamItemJsonObject areaItem(QObject::tr("area"), ParamItemJsonObject::OPTIONS);
    areaItem.addOptionValues({this->m_area});

    obj.insert("name", QObject::tr("basic information of projection"));

    QJsonArray array;
    array.append(areaItem);
    array.append(yearItem);
    obj.insert("items", array);

    obj.insert("hint", QObject::tr("Hint:please keep the check state"));
    return obj;
}

void DemoObject::setObject(const int year, const QString &area){
    this->m_year = year;
    this->m_area = area;
}

bool DemoObject::saveToFile(const QString&fileName){
    this->m_path = fileName;

    QFile file(fileName);
    if (! file.open(QIODevice::WriteOnly)){
        qWarning("Couldn't create ");
        return false;
    } else {
        QFile jsonFile(":/json/config/param.json");
        if (! jsonFile.open(QIODevice::ReadOnly)) {
            return false;
        } else {
            QJsonParseError json_error;
            QByteArray dataArray = jsonFile.readAll();
            QJsonDocument jsonDoc(QJsonDocument::fromJson(dataArray, &json_error));
            QJsonArray jsonArray;
            if (jsonDoc.isArray()) {
                jsonArray = jsonDoc.array();
                jsonArray.insert(0, this->toJsonObject());

            }

            QJsonDocument saveDoc(jsonArray);
            file.write(saveDoc.toJson());
            jsonFile.close();
        }

        file.close();
    }
    return true;
}

QString DemoObject::filepath() const {
    return m_path;
}
