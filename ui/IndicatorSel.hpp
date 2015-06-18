#ifndef INDICATORSEL_HPP
#define INDICATORSEL_HPP

#include <QWizardPage>
#include "SchemeListManager.hpp"
#include "../Scheme/AbstractScheme.hpp"
#include <vector>
#include <QStandardItem>

namespace Ui {
class IndicatorSel;
}

class IndicatorSel : public QWizardPage
{
    Q_OBJECT
public:
    IndicatorSel(SchemeListManager* schemeListManager, QWidget *parent = 0);
    ~IndicatorSel();
    /**
     * @brief disable mapDisp mode for same area disp
     */
    virtual void initializePage() override;

    /**
     * @brief bind view to model
     * @param manager
     */
    void bindListModel(SchemeListManager& manager);
public:
    const static QString MAP_DISP_MODE;
private:
    Ui::IndicatorSel *ui;
};

#endif // INDICATORSEL_HPP
