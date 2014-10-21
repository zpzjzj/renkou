#ifndef DEMOOBJECT_H
#define DEMOOBJECT_H

#include <QString>
class QString;
class QJsonObject;
class QVariant;

class DemoObject
{
public:
    DemoObject();
    DemoObject(const DemoObject&other);
    DemoObject(const int year, const QString& area);

    QString toString();
    QVariant toVariant();
    void setObject(const int year, const QString &area);
    QJsonObject toJsonObject();
    bool saveToFile(const QString& fileName);

private:
    int m_year;
    QString m_area;
    QString m_path;
};

#endif // DEMOOBJECT_H
