#ifndef NEWOBJECTWIZARDPAGE_H
#define NEWOBJECTWIZARDPAGE_H

#include <QWizardPage>

namespace Ui {
class NewObjectWizardPage;
}


class NewObjectWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit NewObjectWizardPage(QWidget *parent = 0);
    ~NewObjectWizardPage();

    int nextId() const;
    bool isComplete() const;


private:
    QString getFileName(int year, QString area);
    void reloadData();

public slots:
    void chooseObjectFilePath();
    void areaChanged(QString _area);
    void yearChanged(QString _year);
    void finish();
private:
    Ui::NewObjectWizardPage *ui;
    QString area;
    int year;
    QString filePath;
};

#endif // NEWOBJECTWIZARDPAGE_H
