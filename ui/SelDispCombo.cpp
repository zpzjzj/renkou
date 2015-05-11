#include "SelDispCombo.hpp"
#include "ui_selSchemeWizardPage.h"

SelDispCombo::SelDispCombo(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::selSchemeWizardPage)
{
    ui->setupUi(this);
    QObject::connect(ui->mParaListWidget, SIGNAL(currentRowChanged(int)),
                     ui->mStackedWidget, SLOT(setCurrentIndex(int)));
    ui->mParaListWidget->setCurrentRow(0);
    ui->mSelectedSchemeWidget->setMinimumHeight(80);
    mSaveButton = ui->buttonBox->addButton(tr("保存设置"), QDialogButtonBox::ActionRole);
}

SelDispCombo::~SelDispCombo()
{
    delete ui;
}

QListWidget* SelDispCombo::getParaListWidget() {
    return ui->mParaListWidget;
}

QStackedWidget* SelDispCombo::getStackedWidget() {
    return ui->mStackedWidget;
}

QPushButton* SelDispCombo::getSaveToFileBtn() {
    return mSaveButton;
}

QListView* SelDispCombo::getSchemeListWidget() {
    return ui->mSelectedSchemeWidget;
}

