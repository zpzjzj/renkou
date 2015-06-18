#include "studyobject.h"
StudyObject::StudyObject(QObject *parent) :
    QObject(parent)
{
}

StudyObject::StudyObject(int year, const QString &area, QObject *parent) :
    QObject(parent)
{
    this->year = year;
    this->area = new QString(area);
    xmlFilename = new QString("dataItem_");
    xmlFilename->append(tr("%1").arg(year));
    xmlFilename->append("_");
    xmlFilename->append(area);
    /**xmlFilename = "year_area"*/

    tmpXmlFilename = new QString(*xmlFilename);
    tmpXmlFilename->append("_tmp.xml");

    xmlFilename->append(".xml");
}

StudyObject::StudyObject(const StudyObject &rhs):QObject(){
    *this = rhs;
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

StudyObject& StudyObject::operator=(const StudyObject& rhs){
    if (this == &rhs) return *this;//identity test

    delete area;
    area = new QString(*rhs.area);

    delete tmpXmlFilename;
    tmpXmlFilename = new QString(*rhs.tmpXmlFilename);

    delete xmlFilename;
    xmlFilename = new QString(*rhs.tmpXmlFilename);

    year = rhs.year;
    return *this;
}

bool StudyObject::operator==(const StudyObject &rhs){
    return(year == rhs.getYear() &&
           *area == rhs.getArea());
}



