#include<QtWidgets>
#include "datapage.h"
#include "objectlist.h"
#include "datatreewidget.h"
#include "datatreewidgetleaf.h"
#include "EnumClass.h"
DataPage::DataPage(QWidget *parent)
    :QWizardPage(parent)
{

    treeWidget = new DataTreeWidget();
    objectList = new ObjectList();

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(treeWidget, 0, 1);
    //testLoad = new QPushButton("Load");
    //layout->addWidget(testLoad, 0, 0);
    layout->addWidget(objectList, 0, 0);

    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 3);
    createActions();

    setLayout(layout);
}


void DataPage::open(StudyObject* object){
    /*first try, load tmp file*/
    QString fileName(EnumClass::PREFIX+object->getTmpXmlFilename());
    qDebug()<<"DataPage::open("<<fileName<<")";

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug()<<"FAILED";

        /*second try, load past-time file*/
        fileName = EnumClass::PREFIX+object->getXmlFilename();
        file.setFileName(fileName);

        qDebug()<<"DataPage::open("<<fileName<<")";

        if (!file.open(QFile::ReadOnly | QFile::Text)){
            qDebug()<<"FAILED";

            /*third try, load default config file;
             * DO NOT write to this file
             */
            fileName = tr(":/res/data/dataItem.xml");
            file.setFileName(fileName);

            qDebug()<<"DataPage::open("<<fileName<<")";
            if (!file.open(QFile::ReadOnly | QFile::Text)){
                qDebug()<<"FAILED";
                return ;
            } else{
                qDebug()<<"SUCCESS";
            }

        } else {
            qDebug()<<"SUCCESS";
        }
    }

    QString type("importdata");

    treeWidget = new DataTreeWidget;
    QGridLayout* g_layout = dynamic_cast<QGridLayout*>(this->layout());
    g_layout->addWidget(treeWidget, 0, 1);

    treeForObject.insert(object, treeWidget);
    if (treeWidget->read(&file, type, object)){
        //file loaded
        emit fileLoaded(object);
    }
}

void DataPage::saveAs(StudyObject *object){
    QString fileName(EnumClass::PREFIX+object->getXmlFilename());
    qDebug()<<tr("DataPage::saveAs() ") << fileName;

    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("XML Files"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    if (treeWidget->write(&file)){
    }
}

void DataPage::createActions(){
    connect(this, SIGNAL(completeChanged()), this, SLOT(clear()));

    connect(objectList, SIGNAL(rowChanged(StudyObject*)),
            this, SLOT(open(StudyObject*)));

}

void DataPage::clear(){

}

