#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "model/objectlistmodel.h"
#include "model/newobjectlistmodel.h"
#include "model/projectionlistmodel.h"

#include "view/newfilewizard.h"
#include "view/mainwindowrightwidget.h"

#include <QHBoxLayout>
#include <QListView>

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
    //data manage menu
    connect(ui->ImportData, SIGNAL(triggered()), this, SLOT(importDataActionTriggered()));
    //parameter menu
    connect(ui->ImportPara, SIGNAL(triggered()), this, SLOT(importParaActionTriggered()));
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
    QHBoxLayout *hLayout = ui->hLayout;

    //left list view
    this->leftListView = new QListView(this);
    this->objListModel = new ObjectListModel;
    this->leftListView->setModel(objListModel);

    //right widget
    this->rightWidget = new MainWindowRightWidget(this);

    hLayout->addWidget(leftListView);
    hLayout->addWidget(rightWidget);
    //set left:right = 1:3
    hLayout->setStretch(0, 1);
    hLayout->setStretch(1, 3);

//    layout->addLayout(hLayout, 0, 0);
//    this->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enableActions(){
    ui->AddObject->setEnabled(true);
    ui->SearchObject->setEnabled(true);
    ui->CloseProject->setEnabled(true);
    ui->ImportData->setEnabled(true);
    ui->ImportPara->setEnabled(true);
    ui->CalculatePara->setEnabled(true);
    ui->ShowSim->setEnabled(true);
    ui->EvaluateSim->setEnabled(true);

}



void MainWindow::addProjectActionTriggered()
{
//    getUiManager()->active(UiManager::newprojectionwizard);
//    this->enableActions();

    //    uiManager->active(UiManager::Page::NewFileWizard);
        NewFileWizard *newFileWizard = new NewFileWizard(this);
    //    newFileWizard
        connect(newFileWizard, SIGNAL(accepted()), this, SLOT(newFileWizardFinished()));

        newFileWizard->setModal(true);
        newFileWizard->show();
}

void MainWindow::openProjectActionTriggered()
{
    getUiManager()->active(UiManager::openProject);
    this->enableActions();
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
void MainWindow::importDataActionTriggered()
{
    getUiManager()->active(UiManager::importBasicData);
}

void MainWindow::importParaActionTriggered()
{
    getUiManager()->active(UiManager::importBasicPara);
}

void MainWindow::calculateSimActionTriggered()
{
    //do some calculate in the background
    getUiManager()->active(UiManager::enterCalculate);
}

void MainWindow::showSimActionTriggered()
{
//    getUiManager()->active(UiManager::display);
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

    ObjectListModel *tmpModel = (ObjectListModel*)this->leftListView->model();
    tmpModel->refrushModel();
    this->update();
}






