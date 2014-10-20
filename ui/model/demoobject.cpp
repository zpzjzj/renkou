#include "demoobject.h"


#include <QFile>

#include <QJsonObject>
#include <QJsonDocument>
#include <QVariant>
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



QString DemoObject::toString(){
    QString res;
    res.append(QString::number(m_year));
    res.append(m_area);
    return res;
}

QVariant DemoObject::toVariant(){
    QVariant variant(this->toString());
    return variant;
}

QJsonObject DemoObject::toJsonObject(){
    QJsonObject obj;
    obj.insert("year", this->m_year);
    obj.insert("area", this->m_area);
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
        QJsonObject jsonObj = this->toJsonObject();
        QJsonDocument jsonDoc;
        jsonDoc.setObject(jsonObj);
        QByteArray byteArray = jsonDoc.toJson((QJsonDocument::Compact));
        file.write(byteArray);

        file.close();
    }

}

