#ifndef PARAMITEMJSONOBJECT_H
#define PARAMITEMJSONOBJECT_H

#include <QJsonObject>

class ParamItemJsonObject : public QJsonObject
{
public:
    enum ItemType{
        DATA, OPTIONS
    };
public:
    ParamItemJsonObject(const QString& _name, ItemType _type);
    ~ParamItemJsonObject();

    bool addOptionValues(QList<QString> options);
    bool addDataValue(const QString& _value);

private:
    ItemType type;
};

#endif // PARAMITEMJSONOBJECT_H
