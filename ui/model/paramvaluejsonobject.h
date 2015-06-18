#ifndef PARAMVALUEJSONOBJECT_H
#define PARAMVALUEJSONOBJECT_H

#include <QJsonObject>

class ParamValueJsonObject : public QJsonObject
{
public:
    explicit ParamValueJsonObject(const QString& _name);
    ~ParamValueJsonObject();
};

#endif // PARAMVALUEJSONOBJECT_H
