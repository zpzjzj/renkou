#include "newobjectwizardpage.h"
#include "ui_newobjectwizardpage.h"

#include "model/yearitemmodel.h"
#include "model/areaitemmodel.h"

#include "model/demoobject.h"

#include "controller/objectlistmanager.h"

#include "uimanager.h"

#include <QFileDialog>
#include <QFileSystemModel>

NewObjectWizardPage::NewObjectWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::NewObjectWizardPage)
{
    ui->setupUi(this);

    YearItemModel *yearItemlModel = new YearItemModel(this);
    ui->cBoxYear->setModel(yearItemlModel);

    AreaItemModel *areaItemModel = new AreaItemModel(this);
    ui->cBoxArea->setModel(areaItemModel);


    year = ui->cBoxYear->currentText().toInt();
    area = ui->cBoxArea->currentText();

    QString fileName = getFileName(year, area);
    filePath = QDir::currentPath().append(fileName);
    ui->lEditPath->setText(filePath);

    connect(ui->btnPath, SIGNAL(clicked()), this, SLOT(chooseObjectFilePath()));
    connect(ui->cBoxArea, SIGNAL(currentIndexChanged(QString)), this, SLOT(areaChanged(QString)));
    connect(ui->cBoxYear, SIGNAL(currentIndexChanged(QString)), this, SLOT(yearChanged(QString)));


}

NewObjectWizardPage::~NewObjectWizardPage()
{
    delete ui;
}

void NewObjectWizardPage::chooseObjectFilePath(){
    QString fileName = getFileName(year, area);
    filePath = QFileDialog::getSaveFileName(this, tr("选择保存对象路径"),
                               fileName,
                               tr("Demography Object File (*.dof)"));

    if (filePath != nullptr && filePath.size() > 0) {
        ui->lEditPath->setText(filePath);
    }
}

void NewObjectWizardPage::areaChanged(QString _area) {
    this->area = _area;
    reloadData();
}

void NewObjectWizardPage::yearChanged(QString _year){
    this->year = _year.toInt();
    reloadData();
}

void NewObjectWizardPage::finish() {
    DemoObject dObject = DemoObject(year, area);
    dObject.saveToFile(filePath);
    ObjectListManager *instance = ObjectListManager::getInstance();
    instance->addObject(dObject);
}

QString NewObjectWizardPage::getFileName(int year, QString area){
    QString fileName = "./";
    fileName = fileName
            .append(QVariant(year).toString())
            .append("_")
            .append(area)
            .append(".dof");
    return fileName;
}

void NewObjectWizardPage::reloadData() {
    QString fileName = getFileName(year, area);
    filePath = QDir::currentPath().append(fileName);
    ui->lEditPath->setText(filePath);
}

int NewObjectWizardPage::nextId() const{
    return -1;
}

bool NewObjectWizardPage::isComplete() const {
    if (filePath != nullptr && filePath.size() > 0) {
        return true;
    }
    return false;
}
