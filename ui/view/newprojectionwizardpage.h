#ifndef NEWPROJECTIONWIZARDPAGE_H
#define NEWPROJECTIONWIZARDPAGE_H

#include <QWizardPage>

namespace Ui {
class NewProjectionWizardPage;
}

class NewProjectionWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit NewProjectionWizardPage(QWidget *parent = 0);
    ~NewProjectionWizardPage();

    int nextId() const;

private:
    Ui::NewProjectionWizardPage *ui;
};

#endif // NEWPROJECTIONWIZARDPAGE_H
