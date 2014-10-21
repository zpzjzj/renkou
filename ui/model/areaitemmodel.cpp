#include "areaitemmodel.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

AreaItemModel::AreaItemModel(QObject *parent) :
    QStringListModel(parent)
{
    list.clear();

    if (!loadJsonDocument(_AREA_JSON_FILE_PATH)){
        list.clear();
    }
    else {
        this->setStringList(list);
    }
    this->setStringList(list);

}


bool AreaItemModel::loadJsonDocument(const char filename[]){
    QFile jsonFile(filename);
    if (! jsonFile.open(QIODevice::ReadOnly)){
        qWarning("Couldn't open area.json");

        return false;
    }
    else {
        QJsonParseError json_error;
        QByteArray dataArray = jsonFile.readAll();
        QJsonDocument jsonDoc(QJsonDocument::fromJson(dataArray, &json_error));
        if (json_error.error == QJsonParseError::NoError){
            if (jsonDoc.isArray()){
                QJsonArray jsonArray = jsonDoc.array();
                foreach(QJsonValue value, jsonArray){
                    if (value.isObject()){
                        QJsonObject jsonObj = value.toObject();
                        QString value = this->read(jsonObj, "label");
                        list << value;
                    }
                }

            }
        }
        jsonFile.close();
        return true;
    }
}

QString AreaItemModel::read(const QJsonObject &json, const QString&key){
     QString value = json[key].toString();
    return value;
}

