#ifndef SCHEMEDISPLAYWIZARD_HPP
#define SCHEMEDISPLAYWIZARD_HPP

#include <QWizard>
#include "uiitem.h"
#include "SelDispCombo.hpp"
#include "UiGenerator.hpp"
#include <memory>

namespace Ui {
class schemeDisplayWizard;
}

class SchemeDisplayWizard : public QWizard, public UiItem
{
    Q_OBJECT
public:
    using Schemes =  std::vector<SchemePtr>;
    using Category = schememetadata::Category;
    using SchemeList = std::vector<SchemePtr>;
    using AbstractSchemeList = ParasManager::AbstractSchemeList;
public:
    explicit SchemeDisplayWizard(QWidget *parent = 0);
    ~SchemeDisplayWizard();
    ParasManager* getParasManager() {
        return mParasManager.get();
    }
private slots:
    void accepted();
private:
    /**
     * @brief use current indicator and abstractSchemes to generate valid schemes
     * @param abstractSchemes
     * @param category
     * @return valid schemes
     */
    SchemeList getSchemes(schememetadata::Category category, const AbstractSchemeList& abstractSchemes, QVector<QString> &curves);
private:
    Ui::schemeDisplayWizard *ui;
    std::unique_ptr<ParasManager> mParasManager;
};

#endif // SCHEMEDISPLAYWIZARD_HPP
