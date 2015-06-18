#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtCore/QVariant>
#include <QtWidgets>

#include <QColor>
#include <QStandardItemModel>
#include <QPalette>

#include "uiitem.h"
namespace Ui {
    class MainWindow;
}

class ObjectListModel;
class QListView;
class ProjectionBodyWidget;

class MainWindow : public QMainWindow, public UiItem {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void createMenus();
    void createActions();
    void createToolbars();
    void enableActions();
    void setActionsEnabled(QList<QAction *> actions, bool enabled);
    bool save();
private slots:
    //project menu
    void addProjectActionTriggered();
    void openProjectActionTriggered();
    void saveProjection();
    void closeProjection();

    void searchObjectActionTriggered();
    void addObjectAcionTriggered();
    void quitActionTriggered();

    //simulation menu
    void calculateSimActionTriggered();
    void showSimActionTriggered();
    void evaluateSimActionTriggered();

    //help menu
    void aboutActionTriggered();

    //enable some actions after a project opened

    void newFileWizardFinished();
    void ObjectCountChanged();

private:
    Ui::MainWindow* ui;

    QListView *leftListView;
    ObjectListModel *objListModel;
    QStackedWidget *stackWidget;
    ProjectionBodyWidget *bodyWidget;

    QMenu *fileMenu;
    QToolBar *fileToolBar;
    QAction *newProj;
    QAction *saveProj;
    QAction *openProj;
    QAction *closeProj;

    QMenu *proMenu;
    QToolBar *proToolbar;
    QAction *importData;
    QAction *importPara;
    QAction *proCalculate;
    QComboBox *activeProjection;
//    void initLeftListView();
};

#endif // MAINWINDOW_H
