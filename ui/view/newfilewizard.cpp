#include "newfilewizard.h"
#include "ui_newfilewizard.h"
#include "wizardpages.h"

NewFileWizard::NewFileWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::NewFileWizard)
{
    init();
}

NewFileWizard::NewFileWizard(UiManager *const uiManager, QWidget *parent)
    : QWizard(parent),
      UiItem(uiManager),
      ui(new Ui::NewFileWizard)

{
    init();
}

NewFileWizard::~NewFileWizard()
{
    delete ui;
}

//int NewFileWizard::nextId() const{
//    switch (currentId()){
//    case Page_Select:

//        return Page_Projection;
//        break;
//    case Page_NewObject:
//        return -1;
//        break;
//    case Page_NewProjection:
//        return Page_NewObject;
//        break;
//    }
//}

void NewFileWizard::init(){
    ui->setupUi(this);

    //connect page_id and Page
    setPage(Page_Select, new SelectWizardPage);
    setPage(Page_NewObject, new NewObjectWizardPage);
    setPage(Page_NewProjection, new NewProjectionWizardPage);
    //first page
    setStartId(Page_Select);

    //signal and slot
    connect(this, SIGNAL(accepted()), page(Page_NewObject), SLOT(finish()));
    connect(this, SIGNAL(finished(int)), this->parentWidget(), SLOT(repaint()));
}


