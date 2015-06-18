#include "schemeDisplayWizard.hpp"
#include "ui_schemeDisplaywizard.h"
#include "../Scheme/schememetadata.h"
#include "../Scheme/Category.hpp"
#include "../Scheme/ConfigMan.hpp"
#include "display/sequencecontroller.h"
#include "display/maptype1.h"
#include "display/pyramidcontroller.h"
#include <QMessageBox>
#include <boost/foreach.hpp>

SchemeDisplayWizard::SchemeDisplayWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::schemeDisplayWizard),
    mParasManager(new ParasManager())
{
    ui->setupUi(this);
    mParasManager->read();
    auto parasManagerPtr = mParasManager.get();
    auto selectSchemePage = new SelDispCombo(this);
    auto uiGenerator = new UiGenerator {
            UiGenerator::PanelPtr(selectSchemePage),
            parasManagerPtr
    };
    uiGenerator->generateUi();
    addPage(selectSchemePage);
    addPage(new IndicatorSel(parasManagerPtr->getModel(), this));
    setWindowTitle(tr("仿真演示"));
    resize(selectSchemePage->sizeHint());
    QObject::connect(this, SIGNAL(accepted()), this, SLOT(accepted()));
}

SchemeDisplayWizard::~SchemeDisplayWizard()
{
    delete ui;
}

namespace {

using DataSources = std::vector<SchemeIndicator<double> >;
using SchemeList = std::vector<SchemePtr>;

DataSources getIndicators(SchemeList schemes, QString indicator) {
    DataSources res;
    for(auto scheme : schemes) {
        res.emplace_back(scheme->getIndicatorDouble(indicator));
    }
    return res;
}
}

void SchemeDisplayWizard::accepted() {
    qDebug() << "void SchemeDisplayWizard::accepted()";
    qDebug() << "indicator" << field("indicator");
    qDebug() << "category" << field("category");
    QVector<QString> curves;
    auto schemes = getSchemes(scheme::fromString(field("category").toString()), mParasManager->getAbstractSchemeList(), curves);
    if(schemes.empty()) {
        QMessageBox::warning(
            this,
            tr("方案指标演示"),
            tr("没有可以演示的数据，放弃演示"),
            QMessageBox::Ok);
        return;
    }

    QWidget* widget = nullptr;
    int startYear = Config::config.Int("START_YEAR");
    int endYear = Config::config.Int("END_YEAR");
    if(field("category").toString().contains(tr("分龄"))) {
        widget = PyramidController::createPyramidController(curves, schemes, startYear, endYear);
    } else {
        auto indicators = getIndicators(schemes, field("indicator").toString());
        if(field("dispMode") == IndicatorSel::MAP_DISP_MODE) {
            widget = MapType1::makeMapType1(curves, indicators, startYear, endYear);
        } else {
            widget = SequenceController::createSequenceController(curves, indicators, startYear, endYear);
        }
    }
    widget->show();
}

SchemeList SchemeDisplayWizard::getSchemes(schememetadata::Category category,
                                           const AbstractSchemeList& abstractSchemes,
                                           QVector<QString>& curves) {
    auto strArr = mParasManager->getModel()->stringList();//str representation of schemes
    const size_t size = strArr.size();
    SchemeList res;
    res.reserve(size);
    curves.reserve(size);
    schememetadataPtr meta = std::make_shared<schememetadata>(category);

    for(size_t i = 0; i < size; ++i) {
        auto& abstractSchemePtr = abstractSchemes[i];
        auto scheme = abstractSchemePtr->generate(meta);
        if(scheme != nullptr) {
            qDebug() << "scheme: " << scheme->getName()
                     << "in IndicatorSel::getSchemes(schememetadata::Category category)";
            QString fname = scheme->toInternalName();
            if(!QFile::exists(fname)) {
                QMessageBox::warning(
                    this,
                    tr("方案指标演示"),
                    tr("方案数据文件 %1 不存在，将不添加到比较列表中").arg(fname),
                    QMessageBox::Ok);
            } else {
                res.push_back(scheme);
                curves.push_back(strArr[i]);
            }
        }
    }
    return res;
}
