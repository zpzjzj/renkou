#include "newprojectionwizard.hpp"
#include "wizardpages.h"
#include "ui_newprojectionwizard.h"
#include <QDebug>
#include <QWidget>
NewProjectionWizard::NewProjectionWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::NewProjectionWizard), iconOff(new QIcon), iconOn(new QIcon)
{
    ui->setupUi(this);

    addPage(new DataPage);
    //!icon init
    QImage image(":/icon/Checkbox empty 16x16.png");
    iconOff->addPixmap(QPixmap::fromImage(image), QIcon::Normal, QIcon::Off);
    iconOff->addPixmap(QPixmap::fromImage(image), QIcon::Active, QIcon::Off);
    iconOff->addPixmap(QPixmap::fromImage(image), QIcon::Selected, QIcon::Off);

    image = QImage(":/icon/Checkbox 16x16.png");
    iconOn->addPixmap(QPixmap::fromImage(image), QIcon::Normal, QIcon::Off);
    iconOn->addPixmap(QPixmap::fromImage(image), QIcon::Active, QIcon::Off);
    iconOn->addPixmap(QPixmap::fromImage(image), QIcon::Selected, QIcon::Off);

    resize(1000, 620);
}

NewProjectionWizard::~NewProjectionWizard()
{
    delete ui;
    delete iconOff;
    delete iconOn;
}

void NewProjectionWizard::pageChecked(int index){
    qDebug()<<tr("NewProjectionWizard::pageChecked(int %1)").arg(index);
}
