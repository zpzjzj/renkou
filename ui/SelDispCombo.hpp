#ifndef SELDISPCOMBO_HPP
#define SELDISPCOMBO_HPP

#include <uiitem.h>
#include <QDialog>
#include <QListWidget>
#include <QStackedWidget>

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

private:
    Ui::SelDispCombo *ui;
};

#endif // SELDISPCOMBO_HPP