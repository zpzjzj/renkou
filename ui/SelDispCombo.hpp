#ifndef SELDISPCOMBO_HPP
#define SELDISPCOMBO_HPP

#include <uiitem.h>
#include <QDialog>
#include <QListWidget>
#include <QStackedWidget>
#include <QPushButton>

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

private:
    Ui::SelDispCombo *ui;
};

#endif // SELDISPCOMBO_HPP
