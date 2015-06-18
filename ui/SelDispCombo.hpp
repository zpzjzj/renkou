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
    class selSchemeWizardPage;
}

class SelDispCombo : public QWizardPage, public UiItem
{
    Q_OBJECT

public:
    explicit SelDispCombo(QWidget *parent = 0);
    ~SelDispCombo();

    QListWidget* getParaListWidget();
    QStackedWidget* getStackedWidget();
    QPushButton* getSaveToFileBtn();
    QListView *getSchemeListWidget();

private:
    Ui::selSchemeWizardPage* ui;
    IndicatorSel* mIndicatorSel;
    QPushButton* mSaveButton;
};

#endif // SELDISPCOMBO_HPP
