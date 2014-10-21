#ifndef STUDYOBJECT_H
#define STUDYOBJECT_H

#include <QObject>

class StudyObject : public QObject
{
    Q_OBJECT
public:
    explicit StudyObject(QObject *parent = 0);
    StudyObject(int year,const QString& area, QObject *parent=0);
    StudyObject(const StudyObject& other);
    ~StudyObject();

    int getYear() const;
    QString getArea() const;

    void setYear(int year);
    void setArea(const QString& area);

    QString getXmlFilename();
    QString getTmpXmlFilename();

    StudyObject& operator=(const StudyObject&);

    bool operator==(const StudyObject &rhs);
signals:


public slots:

private:
    int year;
    QString* area;

    QString* tmpXmlFilename;
    QString* xmlFilename;
};
#endif // STUDYOBJECT_H
