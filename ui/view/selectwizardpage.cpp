#include "selectwizardpage.h"
#include "ui_selectwizardpage.h"

#include "newobjectlistmodel.h"
#include "projectionlistmodel.h"

#include "newfilewizard.h"

#ifdef _DEBUG
#include <QtDebug>
#endif

SelectWizardPage::SelectWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::SelectWizardPage)
{
    ui->setupUi(this);

    //set Title label
    ui->lbObject->setText(QString("新建文件"));
    ui->lbProjection->setText(QString("新建工程"));

    //set model
    ui->objectListView->setModel(new NewObjectListModel);
    ui->projectionListView->setModel(new ProjectionListModel);

    connect(ui->objectListView, SIGNAL(clicked(QModelIndex)), this, SLOT(objectItemClicked(QModelIndex)));
    connect(ui->projectionListView, SIGNAL(clicked(QModelIndex)), this, SLOT(projectionItemClicked(QModelIndex)));
//    connect(ui->objectListView, SIGNAL())
}


SelectWizardPage::~SelectWizardPage()
{
    delete ui;
}

void SelectWizardPage::objectItemClicked(QModelIndex index){
#ifdef _DEBUG
    qDebug()<<"SelectWizardPage::objectItemClicked("<<index.row()<<index.data()<<")";
#endif
    isProjection = false;
}

void SelectWizardPage::projectionItemClicked(QModelIndex index){
#ifdef _DEBUG
    qDebug()<<"SelectWizardPage::projectionItemClicked("<<index.row()<<index.data()<<")";
#endif
    isProjection = true;
}

int SelectWizardPage::nextId() const{
    if (isProjection) {
        return NewFileWizard::Page_NewProjection;
    } else {
        return NewFileWizard::Page_NewObject;
    }
}
