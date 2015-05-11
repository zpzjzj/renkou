#include "../Scheme/schememetadata.h"
#include "../Scheme/jsonUtil.hpp"
#include "IndicatorSel.hpp"
#include "ui_selIndicatorWizardPage.h"
#include "schemeDisplayWizard.hpp"
#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>
#include <QTreeView>
#include <QMessageBox>

IndicatorSel::IndicatorSel(SchemeListManager *schemeListManager, QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::IndicatorSel)
{
    ui->setupUi(this);
    schemeListManager->bindListView(ui->listView);
    registerField("indicator", ui->tabWidget, "indicator", SIGNAL(indicatorChanged(QString)));
    registerField("category*", ui->tabWidget, "category", SIGNAL(categoryChanged(QString)));
    registerField("dispMode", ui->dispModeComboBox, "currentText", SIGNAL(currentIndexChanged(const QString)));
}

IndicatorSel::~IndicatorSel()
{
    delete ui;
}

void IndicatorSel::bindListModel(SchemeListManager& manager) {
    manager.bindListView(ui->listView);
}

void IndicatorSel::initializePage() {
    const static QString AREA_STR = "diqu";
    const static QString MAP_DISP_MODE = IndicatorSel::tr("地图式显示");
    auto dispWizard = dynamic_cast<SchemeDisplayWizard*>(wizard());
    auto& abstractSchemes = dispWizard->getParasManager()->update();
    auto comboBox = ui->dispModeComboBox;
    int index = comboBox->findText(MAP_DISP_MODE);
    if(abstractSchemes.front()->value(AREA_STR) == abstractSchemes.back()->value(AREA_STR)) {
        comboBox->setItemData(index, MAP_DISP_MODE, Qt::UserRole - 1);
    }
}
