#include "schemeDisplayWizard.hpp"
#include "ui_schemeDisplaywizard.h"
#include "../Scheme/schememetadata.h"
#include "../Scheme/Category.hpp"

SchemeDisplayWizard::SchemeDisplayWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::schemeDisplayWizard),
    mParasManager(std::make_unique<ParasManager>())
{
    ui->setupUi(this);
    mParasManager->read();
    auto parasManagerPtr = mParasManager.get();
    auto selectSchemePage = new SelDispCombo(this);
    auto schemeListManager = new SchemeListManager(parasManagerPtr, this);
    auto uiGenerator = new UiGenerator {
            UiGenerator::PanelPtr(selectSchemePage),
            parasManagerPtr,
            schemeListManager
    };
    uiGenerator->generateUi();
    addPage(selectSchemePage);
    addPage(new IndicatorSel(schemeListManager, this));
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

void SchemeDisplayWizard::accepted() {
    qDebug() << "void SchemeDisplayWizard::accepted()";
    qDebug() << "indicator" << field("indicator");
    qDebug() << "category" << field("category");
    auto schemes = getSchemes(mParasManager->getAbstractSchemeList(), scheme::fromString(field("category").toString()));
}
