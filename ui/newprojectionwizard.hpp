#ifndef NEWPROJECTIONWIZARD_HPP
#define NEWPROJECTIONWIZARD_HPP

#include <QWizard>
#include "uiitem.h"

namespace Ui {
class NewProjectionWizard;
}

class NewProjectionWizard : public QWizard,  public UiItem
{
    Q_OBJECT

public:
    explicit NewProjectionWizard(QWidget *parent = 0);
    ~NewProjectionWizard();

private:
    Ui::NewProjectionWizard *ui;

    QIcon *iconOff;
    QIcon *iconOn;
public slots:
    void pageChecked(int index);
};

#endif // NEWPROJECTIONWIZARD_HPP
