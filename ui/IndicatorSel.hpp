#ifndef INDICATORSEL_HPP
#define INDICATORSEL_HPP

#include <QWizardPage>
#include "../Scheme/AbstractScheme.hpp"
#include <vector>
#include <QStandardItem>
#include <QStringListModel>

namespace Ui {
class IndicatorSel;
}

class IndicatorSel : public QWizardPage
{
    Q_OBJECT
public:
    IndicatorSel(QStringListModel *model, QWidget *parent = 0);
    ~IndicatorSel();
    /**
     * @brief disable mapDisp mode for same area disp
     */
    virtual void initializePage() override;
public:
    const static QString MAP_DISP_MODE;
private:
    Ui::IndicatorSel *ui;
};

#endif // INDICATORSEL_HPP
