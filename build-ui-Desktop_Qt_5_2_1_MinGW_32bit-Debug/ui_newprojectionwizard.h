/********************************************************************************
** Form generated from reading UI file 'newprojectionwizard.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPROJECTIONWIZARD_H
#define UI_NEWPROJECTIONWIZARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWizard>
#include <QtWidgets/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_NewProjectionWizard
{
public:
    QWizardPage *introPage;
    QGridLayout *gridLayout;
    QLabel *label;

    void setupUi(QWizard *NewProjectionWizard)
    {
        if (NewProjectionWizard->objectName().isEmpty())
            NewProjectionWizard->setObjectName(QStringLiteral("NewProjectionWizard"));
        NewProjectionWizard->resize(713, 514);
        introPage = new QWizardPage();
        introPage->setObjectName(QStringLiteral("introPage"));
        gridLayout = new QGridLayout(introPage);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(introPage);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        NewProjectionWizard->addPage(introPage);

        retranslateUi(NewProjectionWizard);

        QMetaObject::connectSlotsByName(NewProjectionWizard);
    } // setupUi

    void retranslateUi(QWizard *NewProjectionWizard)
    {
        NewProjectionWizard->setWindowTitle(QApplication::translate("NewProjectionWizard", "\346\226\260\345\273\272\351\242\204\346\265\213", 0));
        label->setText(QApplication::translate("NewProjectionWizard", "\346\226\260\345\273\272\351\242\204\346\265\213\345\220\221\345\257\274", 0));
    } // retranslateUi

};

namespace Ui {
    class NewProjectionWizard: public Ui_NewProjectionWizard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPROJECTIONWIZARD_H
