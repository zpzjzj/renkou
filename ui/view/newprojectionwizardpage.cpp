#include "newprojectionwizardpage.h"
#include "ui_newprojectionwizardpage.h"

#include "newfilewizard.h"
NewProjectionWizardPage::NewProjectionWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::NewProjectionWizardPage)
{
    ui->setupUi(this);
}

NewProjectionWizardPage::~NewProjectionWizardPage()
{
    delete ui;
}

int NewProjectionWizardPage::nextId() const{
    return NewFileWizard::Page_NewObject;
}
