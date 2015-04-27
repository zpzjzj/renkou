#ifndef SELDISPCOMBO_HPP
#define SELDISPCOMBO_HPP

#include <uiitem.h>
#include <QDialog>
#include <QWizardPage>
#include <QListWidget>
#include <QStackedWidget>
#include <QPushButton>
#include "IndicatorSel.hpp"
#include "ParasManager.hpp"

namespace Ui {
class SelDispCombo;
}

class SelDispCombo : public QDialog, public UiItem
{
    Q_OBJECT

public:
    explicit SelDispCombo(QWidget *parent = 0);
    ~SelDispCombo();

    QListWidget* getParaListWidget();
    QStackedWidget* getStackedWidget();
    QPushButton* getSaveToFileBtn();
    QListWidget* getSchemeListWidget();

    void initIndicatorSel(ParasManager* parasManager) {
        mIndicatorSel = new IndicatorSel(parasManager, this);
        QObject::connect(this, &SelDispCombo::accepted, [this, parasManager]() {
            mIndicatorSel->setAbstractSchemes(parasManager->generate());
            mIndicatorSel->show();
        });
    }
private:
    Ui::SelDispCombo *ui;
    IndicatorSel* mIndicatorSel;
    QPushButton* mSaveButton;
};

#endif // SELDISPCOMBO_HPP
