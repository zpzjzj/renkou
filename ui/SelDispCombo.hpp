#ifndef SELDISPCOMBO_HPP
#define SELDISPCOMBO_HPP

#include <uiitem.h>
#include <QDialog>
#include <QListWidget>
#include <QStackedWidget>
#include <QPushButton>
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
public slots:
    /**
     * @brief afterSelect
     *          generate scheme
     *          show indicator select ui
     */
    void afterSelect();
private:
    Ui::SelDispCombo *ui;
    ParasManager* mParasManager;
};

#endif // SELDISPCOMBO_HPP
