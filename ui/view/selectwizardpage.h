#ifndef SELECTWIZARDPAGE_H
#define SELECTWIZARDPAGE_H

#include <QWizardPage>

#include <QModelIndex>


namespace Ui {
class SelectWizardPage;
}

class SelectWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit SelectWizardPage(QWidget *parent = 0);
    ~SelectWizardPage();

    int nextId() const;

private:
    Ui::SelectWizardPage *ui;
    bool isProjection;

public slots:
    void objectItemClicked(QModelIndex index);
    void projectionItemClicked(QModelIndex index);

};

#endif // SELECTWIZARDPAGE_H
