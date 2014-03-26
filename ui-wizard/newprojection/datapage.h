#ifndef DATAPAGE_H
#define DATAPAGE_H

#include <QWizardPage>
class QCheckBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QRadioButton;
class DataPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit DataPage(QWidget *parent = 0);
private:
    QLabel *classNameLabel;
    QLabel *baseClassLabel;
    QLineEdit *classNameLineEdit;
    QLineEdit *baseClassLineEdit;

signals:

public slots:

};

#endif // DATAPAGE_H
