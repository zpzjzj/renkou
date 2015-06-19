#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "model/objectlistmodel.h"
#include "model/newobjectlistmodel.h"
#include "model/projectionlistmodel.h"
#include "controller/objectlistmanager.h"

#include "view/paramselectwidget.h"
#include "view/projectionmanagement.h"
#include "view/projectionbodywidget.h"

#include <QHBoxLayout>
#include <QListView>

#include <QIcon>
#include <QtDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //test widget


    //MENU
    //project menu
    connect(ui->NewProject, SIGNAL(triggered()), this, SLOT(addProjectActionTriggered()));
    connect(ui->OpenProject, SIGNAL(triggered()), this, SLOT(openProjectActionTriggered()));
    connect(ui->SearchObject, SIGNAL(triggered()), this, SLOT(searchObjectActionTriggered()));
    connect(ui->AddObject, SIGNAL(triggered()), this, SLOT(addObjectAcionTriggered()));
    connect(ui->Quit, SIGNAL(triggered()), this, SLOT(quitActionTriggered()));
    //simulation menu
    connect(ui->CalculateSim, SIGNAL(triggered()), this, SLOT(calculateSimActionTriggered()));
    connect(ui->ShowSim, SIGNAL(triggered()), this, SLOT(showSimActionTriggered()));
    connect(ui->EvaluateSim, SIGNAL(triggered()), this, SLOT(evaluateSimActionTriggered()));
    //connect(ui->ReportSim, SIGNAL(triggered()), this, SLOT());

    //help menu
    connect(ui->About, SIGNAL(triggered()), this, SLOT(aboutActionTriggered()));


    //connect(this, SIGNAL(projectOpened()), this, SLOT(enableActions()));

    //init layout
//    QGridLayout *layout = new QGridLayout;
    objListModel = new ObjectListModel;
    connect(objListModel, SIGNAL(valueChanged()), this, SLOT(ObjectCountChanged()));
    stackWidget = new QStackedWidget();

    //for
    QLabel *blankLabel = new QLabel(tr("Please select projection"));
    stackWidget->addWidget(blankLabel);
    ui->scrollArea->setWidget(stackWidget);

    //right widget

//    bodyWidget = new ProjectionBodyWidget;
//    stackWidget->addWidget(bodyWidget);

    //toolbar

    createActions();
    createMenus();
    createToolbars();

    this->activeProjection->setModel(objListModel);
}

MainWindow::~MainWindow()
{
    delete ui;

    while (stackWidget->count() >0){
        stackWidget->removeWidget(stackWidget->currentWidget());
    }
}

void MainWindow::createMenus() {
//    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu = new QMenu(tr("&File"), this);
    menuBar()->insertMenu(ui->File->menuAction(), fileMenu);
    fileMenu->addActions({newProj, saveProj, openProj, closeProj});

}

void MainWindow::createActions() {
    //File Actions
    newProj = new QAction(QIcon(":/icon/icon/new.png"), tr("&New Projection"), this);
    newProj->setShortcuts(QKeySequence::New);
    connect(newProj, SIGNAL(triggered()), this, SLOT(addProjectActionTriggered()));

    saveProj = new QAction(QIcon(":/icon/icon/save.png"), tr("&Save Projection"), this);
    saveProj->setEnabled(false);
    connect(saveProj, SIGNAL(triggered()), this, SLOT(saveProjection()));

    //TODO
    openProj = new QAction(QIcon(":/icon/icon/open.png"), tr("&Open Projection"), this);
    openProj->setEnabled(true);

    closeProj = new QAction(QIcon(":/icon/icon/close.png"), tr("&Close Projection"), this);
    closeProj->setEnabled(false);
    connect(closeProj, SIGNAL(triggered()), this, SLOT(closeProjection()));

    //Projection Actions
    //TODO
    importData = new QAction(QIcon(":/icon/icon/importData.png"), tr("&Import data"), this);
    importData->setEnabled(false);

    //TODO 暂时无需“导入参数”行为，在页面上直接操作
    importPara = new QAction(QIcon(":/icon/icon/importPara.png"), tr("Import Parameters"), this);
    importPara->setEnabled(false);

    proCalculate = new QAction(QIcon(":/icon/icon/calculator.png"), tr("&do calculate"), this);
    proCalculate->setEnabled(false);
    connect(proCalculate, SIGNAL(triggered()), this, SLOT(calculateSimActionTriggered()));
}

void MainWindow::createToolbars() {
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addActions({newProj, saveProj, openProj, closeProj});
    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    proToolbar = addToolBar(tr("Projection"));

    QLabel *hint = new QLabel(tr("active Projection"));
    proToolbar->addWidget(hint);

    activeProjection = new QComboBox(this);
    activeProjection->setMinimumWidth(100);
    activeProjection->setEnabled(false);

    connect(activeProjection, SIGNAL(currentIndexChanged(int)), stackWidget, SLOT(setCurrentIndex(int)));

    proToolbar->addWidget(activeProjection);

    //proToolbar->addActions({importData});
    proToolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    //计算
    proToolbar->addSeparator();
    proToolbar->addAction(proCalculate);
}

void MainWindow::enableActions(){
    setActionsEnabled({ui->AddObject,
                      ui->SearchObject,
                      ui->CloseProject,
                      //ui->ImportData,
//                      ui->ImportPara,
                      ui->CalculatePara,
                      ui->ShowSim,
                      ui->EvaluateSim}, true);
}

void MainWindow::setActionsEnabled(QList<QAction *> actions, bool enabled) {
    foreach(QAction *a, actions) {
        if (a->isEnabled() != enabled)
            a->setEnabled(enabled);
    }
}

void MainWindow::addProjectActionTriggered()
{
    ProjectionManagement *projectionManagement = new ProjectionManagement(this);
    connect(projectionManagement, SIGNAL(accepted()), this, SLOT(newFileWizardFinished()));
    projectionManagement->setModal(true);
    projectionManagement->show();
}

void MainWindow::openProjectActionTriggered()
{
    getUiManager()->active(UiManager::openProject);
    this->enableActions();
}

bool MainWindow::save() {
    ProjectionBodyWidget *current = (ProjectionBodyWidget *)stackWidget->currentWidget();
    return current->saveProjection();
}

void MainWindow::saveProjection() {
    qWarning("saving...");
    if (save()){
        QMessageBox::information(this, tr("Save success"),
                             tr("Current projection has saved successfully"), QMessageBox::Ok);
    } else {
        QMessageBox::critical(this, tr("Save failed"),
                              tr("Something bad happened"), QMessageBox::Ok);
    }
}

void MainWindow::closeProjection() {
    ProjectionBodyWidget *current = (ProjectionBodyWidget *)stackWidget->currentWidget();

    QMessageBox msgBox;
    msgBox.setText(tr("You are trying to close the projection."));
    msgBox.setInformativeText(tr("Do you want to save your projection?"));
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);


    int ret = msgBox.exec();
    if (ret != QMessageBox::Cancel) {
        if (ret == QMessageBox::Save) {
            //TODO Considerate the situation of not save successfully
            saveProjection();
        }

        stackWidget->removeWidget(current);
        ObjectListManager::getInstance()->deleteObjectAt(activeProjection->currentIndex());

        objListModel->refrushModel();
        this->update();
    } else {
        //do nothing
    }

}

void MainWindow::searchObjectActionTriggered()
{
    getUiManager()->active(UiManager::searchObject);
}

void MainWindow::addObjectAcionTriggered(){
//    ui->addObjectGroup->setVisible(true);
}

void MainWindow::quitActionTriggered(){
    this->close();
}


void MainWindow::calculateSimActionTriggered()
{
    //do some calculate in the background
    //TODO call the jar
    save();
    int ret = system("runJar");
    qWarning("system call ret:%d", ret);
}

void MainWindow::showSimActionTriggered()
{
    getUiManager()->active(UiManager::selDispCombo);
}

void MainWindow::evaluateSimActionTriggered()
{
    getUiManager()->active(UiManager::evaluate);
}

void MainWindow::aboutActionTriggered()
{

}

void MainWindow::newFileWizardFinished()
{

    qDebug()<<"New File Wizard Finished";

//    ObjectListModel *tmpModel = (ObjectListModel*)this->leftListView->model();
    objListModel->refrushModel();

    if (objListModel->testRowCount() > 0) {
        stackWidget->insertWidget(objListModel->testRowCount() - 1,
                                  new ProjectionBodyWidget(objListModel->backObject(), this));

        activeProjection->setCurrentIndex(objListModel->testRowCount() - 1 );

    }
    this->update();
}

void MainWindow::ObjectCountChanged() {
    if (objListModel->testRowCount() > 0) {
        if (!activeProjection->isEnabled()) {
            activeProjection->setEnabled(true);
        }
        setActionsEnabled({saveProj,
                           closeProj,
//                           importData,
                           importPara,
                           proCalculate}, true);
    } else {
        activeProjection->setEnabled(false);
        setActionsEnabled({saveProj,
                          closeProj,
//                          importData,
                          importPara,
                          proCalculate}, false);
    }
}






