#ifndef STUDYOBJECT_H
#define STUDYOBJECT_H

#include <QObject>

class StudyObject : public QObject
{
    Q_OBJECT
public:
    explicit StudyObject(QObject *parent = 0);
    StudyObject(int year, QString& area, QObject *parent=0);
    ~StudyObject();

    int getYear() const;
    QString getArea() const;

    void setYear(int year);
    void setArea(const QString& area);

    QString getXmlFilename();
    QString getTmpXmlFilename();
signals:

public slots:

private:
    int year;
    QString* area;

    QString* tmpXmlFilename;
    QString* xmlFilename;
};

#endif // STUDYOBJECT_H
