#include "paramvaluejsonobject.h"

ParamValueJsonObject::ParamValueJsonObject(const QString &_name) :
    QJsonObject() {
    insert("name", _name);
}

ParamValueJsonObject::~ParamValueJsonObject()
{

}

