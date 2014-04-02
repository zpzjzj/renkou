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
    QString fileName(EnumClass::PREFIX+object->getTmpXmlFilename());


    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        /*past-time files*/
        fileName = EnumClass::PREFIX+object->getXmlFilename();
        file.setFileName(fileName);

        if (!file.open(QFile::ReadOnly | QFile::Text)){

            return ;
        }
    }

    QString type("importdata");

    treeWidget = new DataTreeWidget;
    QGridLayout* g_layout = dynamic_cast<QGridLayout*>(this->layout());
    g_layout->addWidget(treeWidget, 0, 1);

    treeForObject.insert(object, treeWidget);
    if (treeWidget->read(&file, type, object)){
        //file loaded
        //statusBar()->showMessage(tr("File loaded"), 2000);
        emit fileLoaded(object);
    }
}

void DataPage::saveAs(StudyObject *object){
    QString fileName(EnumClass::PREFIX+object->getXmlFilename());

    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("SAX Bookmarks"),
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
    connect(objectList, SIGNAL(itemClicked(StudyObject*)),
            this, SLOT(open(StudyObject*)));

//    connect(this, SIGNAL(fileLoaded(StudyObject*)),
//            this, SLOT(saveAs(StudyObject*)));
    //openAct = new Action(tr("&Open..."), this);

}

void DataPage::clear(){

}

