#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <Qtwidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <Qtwidgets/QTableView>
#include <Qtwidgets/QHeaderView>

#include <QColor>
#include <QStandardItemModel>
#include <QPalette>

#include "uiitem.h"
namespace Ui {
    class MainWindow;
}

class MainWindowRightWidget;
class ObjectListModel;
class QListView;

class MainWindow : public QMainWindow, public UiItem {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();


private slots:
    //project menu
    void addProjectActionTriggered();
    void openProjectActionTriggered();
    void searchObjectActionTriggered();
    void addObjectAcionTriggered();
    void quitActionTriggered();
    //data manage menu
    void importDataActionTriggered();

    //parameter menu
    void importParaActionTriggered();

    //simulation menu
    void calculateSimActionTriggered();
    void showSimActionTriggered();
    void evaluateSimActionTriggered();

    //help menu
    void aboutActionTriggered();

    //enable some actions after a project opened

    void newFileWizardFinished();

private:
    Ui::MainWindow* ui;
    void enableActions();

    QListView *leftListView;
    ObjectListModel *objListModel;
    MainWindowRightWidget *rightWidget;
//    void initLeftListView();
};

#endif // MAINWINDOW_H
