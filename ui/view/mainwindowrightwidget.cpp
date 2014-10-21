#include "mainwindowrightwidget.h"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVariant>
#include <QtDebug>

MainWindowRightWidget::MainWindowRightWidget(QWidget *parent) :
    QWidget(parent)
{
    init();
}

void MainWindowRightWidget::init() {

    QGridLayout *gridLayout = new QGridLayout();

//    QPushButton *button1 = new QPushButton("button1");
//    gridLayout->addWidget(button1);
    if (!loadJsonDocument(_PARAM_JSON_FILE_PATH)){
//        list.clear();
    }
    else {

    }
    this->setLayout(gridLayout);
}

bool MainWindowRightWidget::loadJsonDocument(const char filename[]){
    QFile jsonFile(filename);
    if (! jsonFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open param.json");

        return false;
    } else {
        QJsonParseError json_error;
        QByteArray dataArray = jsonFile.readAll();
        QJsonDocument jsonDoc(QJsonDocument::fromJson(dataArray, &json_error));
        if (json_error.error == QJsonParseError::NoError) {
            if (jsonDoc.isArray()) {
                QJsonArray jsonArray = jsonDoc.array();
                foreach (QJsonValue value, jsonArray) {
                    if (value.isObject()){
                        QJsonObject jsonObj = value.toObject();
                        parseParamTree(jsonObj);
                    }
                    else if (value.isString()){

                    }
                    else if (value.isUndefined()){

                    }
//                    qDebug()<<keyValue;
                }
            }
        }
        jsonFile.close();
        return true;
    }
}

void MainWindowRightWidget::parseParamTree(QJsonObject &jsonObj) {
    QString name = jsonObj.value("name").toString();
    QJsonValue option = jsonObj.value("option");
    if (option.isArray()){
        QJsonArray optionArray = option.toArray();
        foreach(QJsonValue value, optionArray) {
            if (value.isObject()){

                QJsonObject subJsonObj = value.toObject();
                        parseParamTree(subJsonObj);
            }
        }
    }
    else {
        qDebug() << "name = " << name;
    }
}

