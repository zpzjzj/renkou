#include "newprojectionwizard.hpp"
#include "wizardpages.h"
#include "ui_newprojectionwizard.h"
#include <QDebug>
#include <QWidget>
NewProjectionWizard::NewProjectionWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::NewProjectionWizard), iconOn(new QIcon), iconOff(new QIcon)
{
    ui->setupUi(this);

    //!icon init
    QImage image(":/icon/Checkbox empty 16x16.png");
    iconOff->addPixmap(QPixmap::fromImage(image), QIcon::Normal, QIcon::Off);
    iconOff->addPixmap(QPixmap::fromImage(image), QIcon::Active, QIcon::Off);
    iconOff->addPixmap(QPixmap::fromImage(image), QIcon::Selected, QIcon::Off);

    image = QImage(":/icon/Checkbox 16x16.png");
    iconOn->addPixmap(QPixmap::fromImage(image), QIcon::Normal, QIcon::Off);
    iconOn->addPixmap(QPixmap::fromImage(image), QIcon::Active, QIcon::Off);
    iconOn->addPixmap(QPixmap::fromImage(image), QIcon::Selected, QIcon::Off);

    for (int i=0; i<ui->dataPageBox->count(); i++){
        ui->dataPageBox->setItemIcon(i, *iconOff);
    }
    //!icon init

    addPage(new DataPage);
    connect(ui->dataPageBox, SIGNAL(currentChanged(int)), this, SLOT(pageChecked(int)));
}

NewProjectionWizard::~NewProjectionWizard()
{
    delete ui;
    delete iconOff;
    delete iconOn;
}

void NewProjectionWizard::pageChecked(int index){
    ui->dataPageBox->setItemIcon(index, *iconOn);
}
