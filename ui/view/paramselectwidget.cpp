#include "paramselectwidget.h"

#include "model/demoobject.h"
#include "model/paramvaluejsonobject.h"

#include <QtWidgets>
#include <QSignalMapper>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVariant>
#include <QtDebug>

//#include "paramselectiontabwidget.h"
ParamSelectWidget::ParamSelectWidget(QString &_filename, QWidget *parent) :
    QWidget(parent)
{
    filename = _filename;



    init();
}

ParamSelectWidget::ParamSelectWidget(const DemoObject &object, QWidget *parent) :
    QWidget(parent)
{

    filename = object.filepath();
    init();
}

void ParamSelectWidget::init() {
    this->paraList = new QList<QList<QMap<QString, QObject*>*>*>();
    this->buttonList = new QList<QWidget*>;
    this->lineEditList = new QList<QWidget*>;

    this->signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(importDataButtonPressed(int)));

    qDebug() << "MainWindowRightWidget::init()"<<endl;

    QGridLayout *gridLayout = new QGridLayout();

//    this->tabWidget = new ParamSelectionTabWidget();
    tabWidget = new QTabWidget();

    gridLayout->addWidget(tabWidget);

//    QPushButton *button1 = new QPushButton("button1");
//    gridLayout->addWidget(button1);
    if (!loadJsonDocument(filename)){
        qWarning("Couldn't open param.json");
    }
    else {
        qWarning("load param.json");

    }
    this->setLayout(gridLayout);
}

bool ParamSelectWidget::loadJsonDocument(QString &filename){
    QFile jsonFile(filename);
    if (! jsonFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open %s", filename);
        return false;
    } else {
        qWarning("Open %s", filename);
        QJsonParseError json_error;
        QByteArray dataArray = jsonFile.readAll();
        QJsonDocument jsonDoc(QJsonDocument::fromJson(dataArray, &json_error));
        if (json_error.error == QJsonParseError::NoError) {
            qWarning("NO ERROR");
            if (jsonDoc.isArray()) {
                QJsonArray jsonArray = jsonDoc.array();
                int i = 0;
                foreach (QJsonValue value, jsonArray) {
                    if (value.isObject()){
                        QJsonObject jsonObj = value.toObject();
                        parseParamTree(i, jsonObj);
                    }
                    else if (value.isString()){

                    }
                    else if (value.isUndefined()){

                    }
//                    qDebug()<<keyValue;
                    i++;
                }
            }
        } else {
            qWarning("error: %d", json_error.error);
        }
        jsonFile.close();
        return true;
    }
}

void ParamSelectWidget::parseParamTree(int tabIndex, QJsonObject &jsonObj) {

    QString name = jsonObj.value("name").toString();
    QString hint = jsonObj.value("hint").toString();

    QJsonValue option = jsonObj.value("items");
    if (option.isArray()){
        qDebug()<<name<<endl;
        if (tabIndex < this->tabWidget->count()){
            this->tabWidget->setTabText(tabIndex, name);
        } else {
            QWidget* newTabPage = new QWidget();
            this->tabWidget->addTab(newTabPage, name);
        }

        SubParaList subParaList = new QList<ParaWidgetItem>;
        this->paraList->append(subParaList);

        QFormLayout *layout = new QFormLayout();
        QWidget *tabPage = this->tabWidget->widget(tabIndex);

        QJsonArray optionArray = option.toArray();

        foreach(QJsonValue value, optionArray) {
            if (value.isObject()){

                QJsonObject subJsonObj = value.toObject();
                ParaWidgetItem paraItem = new QMap<QString, QObject*>;

                QString name = subJsonObj.value("name").toString();
                QLabel *label = new QLabel();
                label->setText(name);
                paraItem->insert("name", label);

                QString type = subJsonObj.value("type").toString();
                if (type == "options") {
                    QComboBox *comboBox = new QComboBox();

                    QJsonArray optionArray = subJsonObj.value("value").toArray();
                    foreach(QJsonValue value, optionArray) {
                        if (value.isObject()){
                            QJsonObject optionJsonObj = value.toObject();
                            QString optionName = optionJsonObj.value("name").toString();
                            comboBox->addItem(optionName);
                        } else if (value.isString()){
                            QString optionName = value.toString();
                            comboBox->addItem(optionName);
                        }
                    }
                    paraItem->insert("options", comboBox);
                    layout->addRow(label, comboBox);
                } else if (type == "data") {
                    QLineEdit *le = new QLineEdit();
                    QPushButton *button = new QPushButton();
                    button->setText(tr("Import"));
                    QHBoxLayout *hLayout = new QHBoxLayout();

                    this->signalMapper->setMapping(button, buttonList->count());
                    buttonList->append(button);
                    connect(button, SIGNAL(clicked()), this->signalMapper, SLOT(map()));

                    lineEditList->append(le);
                    paraItem->insert("data", le);

                    hLayout->addWidget(le);
                    hLayout->addWidget(button);
                    layout->addRow(label, hLayout);
                }

                subParaList->append(paraItem);
            }
        }

        layout->addRow(new QLabel(hint));
        tabPage->setLayout(layout);
    }
    else {
//        qWarning("name = %s");
    }
}

void ParamSelectWidget::importDataButtonPressed(int index) {
    QLineEdit *le = (QLineEdit*)lineEditList->at(index);
    QString filePath = QFileDialog::getOpenFileName(this, tr("choose the parameter file"));

    if (filePath != nullptr && filePath.size() > 0) {
        le->setText(filePath);
    }
}

bool ParamSelectWidget::saveAndExportPara() {
    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite)) {
        return false;
    } else {
        qDebug()<<"pages: " << this->paraList->count()<<endl;
        QJsonArray mainArray;
        for (int idx=0; idx<this->paraList->count(); idx++) {
            QJsonObject jsonPara;
            SubParaList subParaList = this->paraList->at(idx);
            jsonPara["name"] = this->tabWidget->tabText(idx);

            qDebug()<<"sub items:"<<subParaList->count();
            QJsonArray itemsArray;
            foreach(ParaWidgetItem item, *subParaList) {
                QJsonObject jsonObject;
                QLabel *nameLabel = (QLabel*)item->value("name");
                jsonObject["name"] = nameLabel->text();
                qDebug()<<"name: "<<nameLabel->text();

                QComboBox *value = (QComboBox*)item->value("options");
                QLineEdit *lineEdit = (QLineEdit*)item->value("data");
                if (value) {
                    jsonObject["type"] = QVariant("options").toString();
                    //TODO single choice, not using the array.
                    QJsonArray choices;
                    choices.append(value->currentText());
                    jsonObject["value"] = choices;
                }
                if (lineEdit){
                    jsonObject["type"] = QVariant("data").toString();
                    jsonObject["value"] = lineEdit->text();
                }
                itemsArray.append(jsonObject);
            }
            jsonPara["items"] = itemsArray;
            mainArray.append(jsonPara);
        }

        QJsonDocument saveDoc(mainArray);
        file.write(saveDoc.toJson());

        //TODO debug output
        if (QFile::exists("data.json")) {
            QFile::remove("data.json");
        }
        bool ret = file.copy("data.json");

        file.close();

    }


    return true;
}
