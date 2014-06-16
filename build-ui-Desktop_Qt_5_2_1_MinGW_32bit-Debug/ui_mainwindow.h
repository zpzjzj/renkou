/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *NewProject;
    QAction *OpenProject;
    QAction *SearchObject;
    QAction *AddObject;
    QAction *CloseProject;
    QAction *Quit;
    QAction *InputData;
    QAction *ImportData;
    QAction *WatchData;
    QAction *ModifyData;
    QAction *InputPara;
    QAction *ImportPara;
    QAction *CalculatePara;
    QAction *WatchPara;
    QAction *ModifyPara;
    QAction *CalculateSim;
    QAction *ShowSim;
    QAction *EvaluateSim;
    QAction *ReportSim;
    QAction *About;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTableView *objectTable;
    QFrame *line;
    QWidget *showWidget;
    QGroupBox *addObjectGroup;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lb_year;
    QComboBox *yearComboBox;
    QLabel *lb_area;
    QComboBox *comboArea;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QLineEdit *leProvinceCode;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btnAddNewObejct;
    QPushButton *btnAddExsitObject;
    QPushButton *btnFinish;
    QMenuBar *menuBar;
    QMenu *File;
    QMenu *DataManage;
    QMenu *Parameter;
    QMenu *Simulation;
    QMenu *Help;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(911, 519);
        NewProject = new QAction(MainWindow);
        NewProject->setObjectName(QStringLiteral("NewProject"));
        OpenProject = new QAction(MainWindow);
        OpenProject->setObjectName(QStringLiteral("OpenProject"));
        SearchObject = new QAction(MainWindow);
        SearchObject->setObjectName(QStringLiteral("SearchObject"));
        AddObject = new QAction(MainWindow);
        AddObject->setObjectName(QStringLiteral("AddObject"));
        AddObject->setEnabled(false);
        CloseProject = new QAction(MainWindow);
        CloseProject->setObjectName(QStringLiteral("CloseProject"));
        CloseProject->setEnabled(false);
        Quit = new QAction(MainWindow);
        Quit->setObjectName(QStringLiteral("Quit"));
        InputData = new QAction(MainWindow);
        InputData->setObjectName(QStringLiteral("InputData"));
        InputData->setEnabled(false);
        ImportData = new QAction(MainWindow);
        ImportData->setObjectName(QStringLiteral("ImportData"));
        ImportData->setEnabled(false);
        WatchData = new QAction(MainWindow);
        WatchData->setObjectName(QStringLiteral("WatchData"));
        WatchData->setEnabled(false);
        ModifyData = new QAction(MainWindow);
        ModifyData->setObjectName(QStringLiteral("ModifyData"));
        ModifyData->setEnabled(false);
        InputPara = new QAction(MainWindow);
        InputPara->setObjectName(QStringLiteral("InputPara"));
        InputPara->setEnabled(false);
        ImportPara = new QAction(MainWindow);
        ImportPara->setObjectName(QStringLiteral("ImportPara"));
        ImportPara->setEnabled(false);
        CalculatePara = new QAction(MainWindow);
        CalculatePara->setObjectName(QStringLiteral("CalculatePara"));
        CalculatePara->setEnabled(false);
        WatchPara = new QAction(MainWindow);
        WatchPara->setObjectName(QStringLiteral("WatchPara"));
        WatchPara->setEnabled(false);
        ModifyPara = new QAction(MainWindow);
        ModifyPara->setObjectName(QStringLiteral("ModifyPara"));
        ModifyPara->setEnabled(false);
        CalculateSim = new QAction(MainWindow);
        CalculateSim->setObjectName(QStringLiteral("CalculateSim"));
        CalculateSim->setEnabled(false);
        ShowSim = new QAction(MainWindow);
        ShowSim->setObjectName(QStringLiteral("ShowSim"));
        ShowSim->setEnabled(false);
        EvaluateSim = new QAction(MainWindow);
        EvaluateSim->setObjectName(QStringLiteral("EvaluateSim"));
        EvaluateSim->setEnabled(false);
        ReportSim = new QAction(MainWindow);
        ReportSim->setObjectName(QStringLiteral("ReportSim"));
        ReportSim->setEnabled(false);
        About = new QAction(MainWindow);
        About->setObjectName(QStringLiteral("About"));
        About->setEnabled(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        objectTable = new QTableView(centralWidget);
        objectTable->setObjectName(QStringLiteral("objectTable"));

        horizontalLayout->addWidget(objectTable);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        showWidget = new QWidget(centralWidget);
        showWidget->setObjectName(QStringLiteral("showWidget"));
        addObjectGroup = new QGroupBox(showWidget);
        addObjectGroup->setObjectName(QStringLiteral("addObjectGroup"));
        addObjectGroup->setEnabled(true);
        addObjectGroup->setGeometry(QRect(10, 120, 329, 191));
        addObjectGroup->setFlat(true);
        gridLayout = new QGridLayout(addObjectGroup);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lb_year = new QLabel(addObjectGroup);
        lb_year->setObjectName(QStringLiteral("lb_year"));

        horizontalLayout_2->addWidget(lb_year);

        yearComboBox = new QComboBox(addObjectGroup);
        yearComboBox->setObjectName(QStringLiteral("yearComboBox"));

        horizontalLayout_2->addWidget(yearComboBox);

        lb_area = new QLabel(addObjectGroup);
        lb_area->setObjectName(QStringLiteral("lb_area"));

        horizontalLayout_2->addWidget(lb_area);

        comboArea = new QComboBox(addObjectGroup);
        comboArea->setObjectName(QStringLiteral("comboArea"));
        comboArea->setEditable(false);

        horizontalLayout_2->addWidget(comboArea);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        label_3 = new QLabel(addObjectGroup);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        leProvinceCode = new QLineEdit(addObjectGroup);
        leProvinceCode->setObjectName(QStringLiteral("leProvinceCode"));

        horizontalLayout_3->addWidget(leProvinceCode);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        btnAddNewObejct = new QPushButton(addObjectGroup);
        btnAddNewObejct->setObjectName(QStringLiteral("btnAddNewObejct"));

        horizontalLayout_4->addWidget(btnAddNewObejct);

        btnAddExsitObject = new QPushButton(addObjectGroup);
        btnAddExsitObject->setObjectName(QStringLiteral("btnAddExsitObject"));

        horizontalLayout_4->addWidget(btnAddExsitObject);

        btnFinish = new QPushButton(addObjectGroup);
        btnFinish->setObjectName(QStringLiteral("btnFinish"));

        horizontalLayout_4->addWidget(btnFinish);


        gridLayout->addLayout(horizontalLayout_4, 2, 0, 1, 1);


        horizontalLayout->addWidget(showWidget);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(2, 2);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 911, 23));
        File = new QMenu(menuBar);
        File->setObjectName(QStringLiteral("File"));
        DataManage = new QMenu(menuBar);
        DataManage->setObjectName(QStringLiteral("DataManage"));
        Parameter = new QMenu(menuBar);
        Parameter->setObjectName(QStringLiteral("Parameter"));
        Simulation = new QMenu(menuBar);
        Simulation->setObjectName(QStringLiteral("Simulation"));
        Help = new QMenu(menuBar);
        Help->setObjectName(QStringLiteral("Help"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(File->menuAction());
        menuBar->addAction(DataManage->menuAction());
        menuBar->addAction(Parameter->menuAction());
        menuBar->addAction(Simulation->menuAction());
        menuBar->addAction(Help->menuAction());
        File->addAction(NewProject);
        File->addAction(OpenProject);
        File->addSeparator();
        File->addAction(SearchObject);
        File->addAction(AddObject);
        File->addSeparator();
        File->addAction(CloseProject);
        File->addAction(Quit);
        DataManage->addAction(InputData);
        DataManage->addAction(ImportData);
        DataManage->addSeparator();
        DataManage->addAction(WatchData);
        DataManage->addAction(ModifyData);
        Parameter->addAction(InputPara);
        Parameter->addAction(ImportPara);
        Parameter->addSeparator();
        Parameter->addAction(CalculatePara);
        Parameter->addSeparator();
        Parameter->addAction(WatchPara);
        Parameter->addAction(ModifyPara);
        Simulation->addAction(CalculateSim);
        Simulation->addAction(ShowSim);
        Simulation->addSeparator();
        Simulation->addAction(EvaluateSim);
        Simulation->addAction(ReportSim);
        Help->addAction(About);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        NewProject->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\351\242\204\346\265\213", 0));
        OpenProject->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\351\242\204\346\265\213", 0));
        SearchObject->setText(QApplication::translate("MainWindow", "\346\237\245\346\211\276\347\240\224\347\251\266\345\257\271\350\261\241", 0));
        AddObject->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\347\240\224\347\251\266\345\257\271\350\261\241", 0));
        CloseProject->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255\351\241\271\347\233\256", 0));
        Quit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", 0));
        InputData->setText(QApplication::translate("MainWindow", "\345\275\225\345\205\245", 0));
        ImportData->setText(QApplication::translate("MainWindow", "\345\257\274\345\205\245", 0));
        WatchData->setText(QApplication::translate("MainWindow", "\346\237\245\347\234\213", 0));
        ModifyData->setText(QApplication::translate("MainWindow", "\344\277\256\346\224\271", 0));
        InputPara->setText(QApplication::translate("MainWindow", "\345\275\225\345\205\245", 0));
        ImportPara->setText(QApplication::translate("MainWindow", "\345\257\274\345\205\245", 0));
        CalculatePara->setText(QApplication::translate("MainWindow", "\350\256\241\347\256\227", 0));
        WatchPara->setText(QApplication::translate("MainWindow", "\346\237\245\347\234\213", 0));
        ModifyPara->setText(QApplication::translate("MainWindow", "\344\277\256\346\224\271", 0));
        CalculateSim->setText(QApplication::translate("MainWindow", "\344\273\277\347\234\237\350\256\241\347\256\227", 0));
        ShowSim->setText(QApplication::translate("MainWindow", "\344\273\277\347\234\237\346\274\224\347\244\272", 0));
        EvaluateSim->setText(QApplication::translate("MainWindow", "\344\273\277\347\234\237\350\257\204\344\273\267", 0));
        ReportSim->setText(QApplication::translate("MainWindow", "\344\273\277\347\234\237\346\212\245\345\221\212", 0));
        About->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216", 0));
        lb_year->setText(QApplication::translate("MainWindow", "\345\237\272\345\271\264:", 0));
        lb_area->setText(QApplication::translate("MainWindow", "\345\234\260\345\214\272:", 0));
        comboArea->clear();
        comboArea->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\345\205\250\345\233\275", 0)
         << QApplication::translate("MainWindow", "\345\214\227\344\272\254", 0)
         << QApplication::translate("MainWindow", "\345\244\251\346\264\245", 0)
         << QApplication::translate("MainWindow", "\346\262\263\345\214\227", 0)
         << QApplication::translate("MainWindow", "\345\261\261\350\245\277", 0)
         << QApplication::translate("MainWindow", "\345\206\205\350\222\231\345\217\244", 0)
         << QApplication::translate("MainWindow", "\350\276\275\345\256\201", 0)
         << QApplication::translate("MainWindow", "\345\220\211\346\236\227", 0)
         << QApplication::translate("MainWindow", "\351\273\221\351\276\231\346\261\237", 0)
         << QApplication::translate("MainWindow", "\344\270\212\346\265\267", 0)
         << QApplication::translate("MainWindow", "\346\261\237\350\213\217", 0)
         << QApplication::translate("MainWindow", "\346\265\231\346\261\237", 0)
         << QApplication::translate("MainWindow", "\345\256\211\345\276\275", 0)
         << QApplication::translate("MainWindow", "\347\246\217\345\273\272", 0)
         << QApplication::translate("MainWindow", "\346\261\237\350\245\277", 0)
         << QApplication::translate("MainWindow", "\345\261\261\344\270\234", 0)
         << QApplication::translate("MainWindow", "\346\262\263\345\215\227", 0)
         << QApplication::translate("MainWindow", "\346\271\226\345\214\227", 0)
         << QApplication::translate("MainWindow", "\346\271\226\345\215\227", 0)
         << QApplication::translate("MainWindow", "\345\271\277\344\270\234", 0)
         << QApplication::translate("MainWindow", "\345\271\277\350\245\277", 0)
         << QApplication::translate("MainWindow", "\346\265\267\345\215\227", 0)
         << QApplication::translate("MainWindow", "\351\207\215\345\272\206", 0)
         << QApplication::translate("MainWindow", "\345\233\233\345\267\235", 0)
         << QApplication::translate("MainWindow", "\350\264\265\345\267\236", 0)
         << QApplication::translate("MainWindow", "\344\272\221\345\215\227", 0)
         << QApplication::translate("MainWindow", "\350\245\277\350\227\217", 0)
         << QApplication::translate("MainWindow", "\351\231\225\350\245\277", 0)
         << QApplication::translate("MainWindow", "\347\224\230\350\202\203", 0)
         << QApplication::translate("MainWindow", "\351\235\222\346\265\267", 0)
         << QApplication::translate("MainWindow", "\345\256\201\345\244\217", 0)
         << QApplication::translate("MainWindow", "\346\226\260\347\226\206", 0)
        );
        label_3->setText(QApplication::translate("MainWindow", "\345\210\206\347\234\201\344\273\243\347\240\201:", 0));
        btnAddNewObejct->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\346\226\260\345\257\271\350\261\241", 0));
        btnAddExsitObject->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\345\267\262\346\234\211\345\257\271\350\261\241", 0));
        btnFinish->setText(QApplication::translate("MainWindow", "\345\256\214\346\210\220", 0));
        File->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", 0));
        DataManage->setTitle(QApplication::translate("MainWindow", "\345\237\272\347\241\200\346\225\260\346\215\256", 0));
        Parameter->setTitle(QApplication::translate("MainWindow", "\345\237\272\346\234\254\345\217\202\346\225\260", 0));
        Simulation->setTitle(QApplication::translate("MainWindow", "\346\224\277\347\255\226\344\273\277\347\234\237", 0));
        Help->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
