#include "schemeDisplayWizard.hpp"
#include "ui_schemeDisplaywizard.h"
#include "../Scheme/schememetadata.h"
#include "../Scheme/Category.hpp"
#include "../Scheme/ConfigMan.hpp"
#include "display/sequencecontroller.h"
#include "display/maptype1.h"
#include "display/pyramidcontroller.h"

SchemeDisplayWizard::SchemeDisplayWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::schemeDisplayWizard),
    mParasManager(std::make_unique<ParasManager>())
{
    ui->setupUi(this);
    mParasManager->read();
    auto parasManagerPtr = mParasManager.get();
    auto selectSchemePage = new SelDispCombo(this);
    mSchemeListManager = new SchemeListManager(parasManagerPtr, this);
    auto uiGenerator = new UiGenerator {
            UiGenerator::PanelPtr(selectSchemePage),
            parasManagerPtr,
            mSchemeListManager
    };
    uiGenerator->generateUi();
    addPage(selectSchemePage);
    addPage(new IndicatorSel(mSchemeListManager, this));
    setWindowTitle(tr("方案演示"));
    resize(selectSchemePage->sizeHint());
    QObject::connect(this, SIGNAL(accepted()), this, SLOT(accepted()));
}

SchemeDisplayWizard::~SchemeDisplayWizard()
{
    delete ui;
}

namespace {
    using Category = schememetadata::Category;

    using SchemeList = std::vector<SchemePtr>;
    using AbstractSchemeList = ParasManager::AbstractSchemeList;

    /**
     * @brief use current indicator and abstractSchemes to generate valid schemes
     * @param abstractSchemes
     * @param category
     * @return valid schemes
     */
    SchemeList getSchemes(const AbstractSchemeList& abstractSchemes, schememetadata::Category category) {
        SchemeList res;
        schememetadataPtr meta = std::make_shared<schememetadata>(category);
        res.reserve(abstractSchemes.size());
        for(auto abstractSchemePtr : abstractSchemes) {
            auto scheme = abstractSchemePtr->generate(meta);
            if(scheme != nullptr) {
                qDebug() << "scheme: " << scheme->getName()
                         << "in IndicatorSel::getSchemes(schememetadata::Category category)";
                res.push_back(scheme);
            }
        }
        return res;
    }
}

namespace {

using DataSources = std::vector<SchemeIndicator<double> >;

DataSources getIndicators(SchemeList schemes, QString indicator) {
    DataSources res;
    for(auto scheme : schemes) {
        res.emplace_back(scheme->getIndicatorDouble(indicator));
    }
    return res;
}

using SchemeNames = QVector<QString>;

inline SchemeNames getSchemeNames(const SchemeListManager& listManager) {
    return listManager.getStrings();
}

QWidget* mapDisplay() {
//    return MapType1::makeMapType1(t_Curves, t_Files, t_StartYear, EndYear.toInt());
    return nullptr;
}

QWidget* sequence() {
//    return SequenceController::createSequenceController(t_Curves, t_Files, t_StartYear, EndYear.toInt());
    return nullptr;
}

QWidget* pyramid() {
//    return PyramidController::createPyramidController(t_Curves, t_Files, t_StartYear, EndYear.toInt());
    return nullptr;
}

}

void SchemeDisplayWizard::accepted() {
    qDebug() << "void SchemeDisplayWizard::accepted()";
    qDebug() << "indicator" << field("indicator");
    qDebug() << "category" << field("category");
    auto schemes = getSchemes(mParasManager->getAbstractSchemeList(), scheme::fromString(field("category").toString()));
    QWidget* widget = nullptr;
    auto curves = getSchemeNames(*mSchemeListManager);
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
