#include<QtWidgets>
#include"datapage.h"
#include "datatreewidget.h"
#include "datatreewidgetleaf.h"
#include "datatreemodel.h"
DataPage::DataPage(QWidget *parent)
    :QWizardPage(parent)
{

    treeWidget = new DataTreeWidget();

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(treeWidget, 0, 1);
    testLoad = new QPushButton("Load");
    layout->addWidget(testLoad, 0, 0);
    createActions();

    setLayout(layout);
}


void DataPage::open(){
    QString fileName(":/res/data/dataItem.xml");

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, tr("XML file"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return ;
    }
    QString type("importdata");
    if (treeWidget->read(&file, type)){
        //file loaded
    }
}

void DataPage::saveAs(int index){
    QString fileName("../data/dataPath.xml");

}

void DataPage::createActions(){

    connect(testLoad, SIGNAL(clicked()), this, SLOT(open()));

    //openAct = new Action(tr("&Open..."), this);

}

