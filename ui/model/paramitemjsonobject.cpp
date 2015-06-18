#include "paramitemjsonobject.h"
#include "paramvaluejsonobject.h"

#include <QJsonArray>
#include <QList>

ParamItemJsonObject::ParamItemJsonObject(const QString &_name, ItemType _type) {
    insert("name", _name);

    type = _type;
    if (type == DATA) {
        insert("type", "data");
    } else if (type == OPTIONS) {
        insert("type", "options");
    }
}

ParamItemJsonObject::~ParamItemJsonObject()
{

}

bool ParamItemJsonObject::addOptionValues(QList<QString> options) {
    if (type == DATA) return false;

    QJsonArray array;
    foreach(QString _name, options) {
        array.append(QJsonValue(_name));
    }

    insert("value", array);

    return true;
}

bool ParamItemJsonObject::addDataValue(const QString &_value) {
    if (type == OPTIONS) return false;

    insert("value", ParamValueJsonObject(_value));

    return true;
}

