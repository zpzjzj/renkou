#include "studyobject.h"

StudyObject::StudyObject(QObject *parent) :
    QObject(parent)
{
}

StudyObject::StudyObject(int year, QString &area, QObject *parent) :
    QObject(parent)
{
    this->year = year;
    this->area = new QString(area);
    xmlFilename = new QString(year);
    xmlFilename->append('_');
    xmlFilename->append(area);
    /**xmlFilename = "year_area"*/

    tmpXmlFilename = new QString(*xmlFilename);
    tmpXmlFilename->append("_tmp.xml");

    xmlFilename->append(".xml");
}

StudyObject::~StudyObject(){
    delete this->area;
}

int StudyObject::getYear() const{
    return year;
}

QString StudyObject::getArea() const{
    return *area;
}

void StudyObject::setYear(int year){
    this->year = year;
}

void StudyObject::setArea(const QString &area){
    if (this->area){
        delete this->area;
        this->area = new QString(area);
    }
    else {
        this->area = new QString(area);
    }
}

QString StudyObject::getXmlFilename(){
    return *xmlFilename;
}

QString StudyObject::getTmpXmlFilename(){
    return *tmpXmlFilename;
}
