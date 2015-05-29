#include <QTextCodec>
#include <QBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QToolBox>
#include <QBoxLayout>
#include <QLabel>
#include "Constants.h"
#include "coloriconengine.h"
#include "pyramidcontroller.h"
#include "pyramidstripview.h"
#include "pyramidbarview.h"
#include "ui_pyramidcontroller.h"

template <class PyramidController>
        const int Counted<PyramidController>::maxObjects = 15;

PyramidController::PyramidController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PyramidController)
{
    ui->setupUi(this);

    m_model = NULL;
    m_currentView = NULL;
    m_leMaxPopulation.clear();
    m_leMinPopulation.clear();
    m_leMiddleAge.clear();
    m_leAverageAge.clear();

    this->m_stateStop = NULL;
    this->m_statePlay = NULL;
    this->m_statePause = NULL;
    this->m_isPaused = false;

    this->m_timeLine = new MyTimeLine();

}

PyramidController::~PyramidController()
{
    delete ui;
    delete m_timeLine;
}

PyramidController* PyramidController::createPyramidController(QVector<QString> curves, DataSources files, int sy, int ey, QWidget *parent)
{
    PyramidController *pc = new PyramidController();
    if(pc->setup(curves, files, sy, ey))
        return pc;
    else{
        qDebug()<<"PyramidController::createPyramidController";
        return NULL;
    }
}

bool PyramidController::setup(QVector<QString> curves, DataSources files, int sy, int ey)
{
    bool ret = true;

    m_startYear = sy;
    m_endYear = ey;
    m_curves = curves;

    ret = setupPyramidModel(curves, files, sy, ey);
    if(!ret)
        return ret;
//    qDebug()<<"PyramidController::setup"<<"step1";

    ret = setupStateMachine();
    if(!ret)
        return ret;
//    qDebug()<<"PyramidController::setup"<<"step2";

    ret = setupWidgets();
    if(!ret)
        return ret;
//    qDebug()<<"PyramidController::setup"<<"step3";

    updateOnCurrentYearChanged(m_startYear);
    ui->radioBar->setChecked(true);

    return ret;
}

bool PyramidController::setupPyramidModel(QVector<QString> curves, DataSources files, int sy, int ey)
{
    bool ret = true;

    m_model = new PyramidModel(sy, ey, curves, files);

    QMap<QString, QColor> colortheme;
    colortheme.clear();
    for(int i=0; i<curves.size(); ++i){
        colortheme[curves[i]] = ColorForLine[i];
    }
    m_model->m_color = colortheme;

    return ret;
}

bool PyramidController::setupWidgets()
{
    bool ret = true;

//    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    setLayout(ui->verticalLayout_Main);

    // 初始化各种可视化方式
    m_timeLine->setFrameRange(m_startYear, m_endYear);
    m_timeLine->setInterval(200);
    m_views.append(new PyramidStripView(m_model));
    m_views.append(new PyramidBarView(m_model));

    for(int i=0; i<m_views.size(); ++i){
        connect(m_timeLine, SIGNAL(timeChanged(qreal)), m_views[i], SLOT(changeTime(qreal)));
        connect(m_timeLine, SIGNAL(frameChanged(int)), m_views[i], SLOT(changeCurrentYear(int)));
        connect(ui->HLineButton, SIGNAL(toggled(bool)), m_views[i], SLOT(enableHorizonLine(bool)));
        connect(ui->VLineButton, SIGNAL(toggled(bool)), m_views[i], SLOT(enableVerticalLine(bool)));
        connect(ui->DualLineButton, SIGNAL(toggled(bool)), m_views[i], SLOT(enableCrossLine(bool)));
    }

    ui->NoLineButton->toggle();

//    qDebug()<<"PyramidController::setupWidgets"<<"check point1";

    // 初始化年份选择框
    ui->comboBox->addItem(tr("更改年份"));
    for(int i=m_startYear; i<=m_endYear; ++i){
        ui->comboBox->addItem(QString::number(i));
    }

    // 初始化关键数据显示板
    QToolBox* valueBox = new QToolBox(this);
    for(int i=0; i<m_curves.size(); ++i){
        QBoxLayout* innerlayout = new QBoxLayout(QBoxLayout::TopToBottom);
        innerlayout->setSpacing(5);

        QLabel* labeltitle = new QLabel(tr("曲线名称"), this);
        innerlayout->addWidget(labeltitle);

        QLineEdit* letitle = new QLineEdit(this);
        letitle->setText(m_curves[i]);
        letitle->setReadOnly(true);
        innerlayout->addWidget(letitle);

        QLabel *labelmaxpopulation = new QLabel(tr("最多人口"), this);
        innerlayout->addWidget(labelmaxpopulation);

        QLineEdit* lemaxpopulation = new QLineEdit(this);
        lemaxpopulation->setReadOnly(true);
        innerlayout->addWidget(lemaxpopulation);
        m_leMaxPopulation.push_back(lemaxpopulation);

        QLabel *labelminpopulation = new QLabel(tr("最少人口"), this);
        innerlayout->addWidget(labelminpopulation);

        QLineEdit* leminpopulation = new QLineEdit(this);
        leminpopulation->setReadOnly(true);
        innerlayout->addWidget(leminpopulation);
        m_leMinPopulation.push_back(leminpopulation);

        QLabel *labelaveage = new QLabel(tr("平均年龄"));
        innerlayout->addWidget(labelaveage);

        QLineEdit* leaveage = new QLineEdit(this);
        leaveage->setReadOnly(true);
        innerlayout->addWidget(leaveage);
        m_leAverageAge.push_back(leaveage);

        QLabel *labelmidage = new QLabel(tr("中位年龄"));
        innerlayout->addWidget(labelmidage);

        QLineEdit* lemidage = new QLineEdit(this);
        lemidage->setReadOnly(true);
        innerlayout->addWidget(lemidage);
        m_leMiddleAge.push_back(lemidage);

        QWidget* bgwidget = new QWidget(this);
        bgwidget->setLayout(innerlayout);

        valueBox->addItem(bgwidget, tr("年龄金字塔")+QString::number(i+1));
        QColor c = m_model->m_color.value(m_curves[i]);
        valueBox->setItemIcon(i, QIcon(new ColorIconEngine(c)));
    }

//    qDebug()<<"PyramidController::setupWidgets"<<"check point2";

    QBoxLayout* outerlayout = new QBoxLayout(QBoxLayout::TopToBottom);
    outerlayout->setMargin(5);
    outerlayout->addWidget(valueBox);
    ui->groupBox->setLayout(outerlayout);

    connect(m_timeLine, SIGNAL(frameChanged(int)), this, SLOT(updateOnCurrentYearChanged(int)));
    connect(valueBox, SIGNAL(currentChanged(int)), this, SLOT(selectCurve(int)));
    // create connections

    return ret;
}

bool PyramidController::setupStateMachine()
{
    int ret = true;

//    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    // create states
    m_statePlay = new QState(&m_stateMachine);
    m_statePlay->assignProperty(ui->PlayButton, "text", tr("暂停"));
    m_statePlay->assignProperty(ui->StopButton, "enabled", true);

    m_statePause = new QState(&m_stateMachine);
    m_statePause->assignProperty(ui->PlayButton, "text", tr("继续"));

    m_stateStop = new QState(&m_stateMachine);
    m_stateStop->assignProperty(ui->PlayButton, "text", tr("开始"));
    m_stateStop->assignProperty(ui->StopButton, "enabled", false);

    // create transititons
    m_statePlay->addTransition(ui->PlayButton, SIGNAL(clicked()), m_statePause);
    m_statePlay->addTransition(ui->StopButton, SIGNAL(clicked()), m_stateStop);
    m_statePlay->addTransition(m_timeLine, SIGNAL(finished()), m_stateStop);

    m_statePause->addTransition(ui->PlayButton, SIGNAL(clicked()), m_statePlay);
    m_statePause->addTransition(ui->StopButton, SIGNAL(clicked()), m_stateStop);

    m_stateStop->addTransition(ui->PlayButton, SIGNAL(clicked()), m_statePlay);

    // create connections
    connect(m_statePlay, SIGNAL(entered()),this, SLOT(start()));
    connect(m_stateStop, SIGNAL(entered()), this, SLOT(stop()));
    connect(m_statePause, SIGNAL(entered()), this, SLOT(pause()));

    m_stateMachine.setInitialState(m_stateStop);
    m_stateMachine.start();

    return ret;
}

void PyramidController::setViewMode(int chosen)
{
}

void PyramidController::start()
{
    if(!m_isPaused){
        for(int i=0; i<m_views.size(); ++i){
            m_views[i]->changeCurrentYear(m_startYear);
        }
        m_timeLine->start();
    }
    else{
        m_timeLine->resume();
    }
    m_isPaused = false;
}

void PyramidController::pause()
{
    m_timeLine->pause();
    m_isPaused = true;
}

void PyramidController::stop()
{
    m_timeLine->stop();
    m_isPaused = false;
}

void PyramidController::on_Advance10Button_clicked(bool checked)
{
    Q_UNUSED(checked)
    int year = m_timeLine->getFrame() + 10;
    m_timeLine->setFrame(year);
}

void PyramidController::on_Back10Button_clicked(bool checked)
{
    Q_UNUSED(checked)
    int year = m_timeLine->getFrame() - 10;
    m_timeLine->setFrame(year);
}

void PyramidController::updateOnCurrentYearChanged(int year)
{
    // update key values
    for(int i=0; i<m_curves.size(); ++i){
        QString curve = m_curves[i];
        QString s;
        int offset = year - m_startYear;
        int maxage = m_model->m_maxPopulationAge[curve][offset];
        double maxpopulation = (m_model->m_femaleData)[curve][offset][maxage]
                               + (m_model->m_maleData)[curve][offset][maxage];
        int minage = m_model->m_minPopulationAge[curve][offset];
        double minpopulation = (m_model->m_femaleData)[curve][offset][minage]
                               + (m_model->m_maleData)[curve][offset][minage];
        double aveage = (m_model->m_aveAge)[curve][offset];
        double midage = (m_model->m_middleAge)[curve][offset];
        s = QString::number(maxage)+tr("岁，")+QString::number(maxpopulation)+tr("万人");
        m_leMaxPopulation[i]->setText(s);
        s = QString::number(minage)+tr("岁，")+QString::number(minpopulation)+tr("万人");
        m_leMinPopulation[i]->setText(s);
        s = QString::number(aveage)+tr("岁");
        m_leAverageAge[i]->setText(s);
        s = QString::number(midage)+tr("岁");
        m_leMiddleAge[i]->setText(s);
    }
}

void PyramidController::selectCurve(int index)
{
    for(int i=0; i<m_views.size(); ++i){
        m_views[i]->selectCurve(m_curves[index]);
    }
}

void PyramidController::on_comboBox_currentIndexChanged(QString s)
{
    bool ok;
    int year = s.toInt(&ok);
    if(ok){
        m_timeLine->setFrame(year);
    }
}

void PyramidController::on_radioCurve_toggled(bool checked)
{
    if(checked){
        ui->graphicsView->setScene(m_views[0]);
        ui->checkBox->setDisabled(false);
        ui->groupBox_4->setDisabled(false);
    }
}

void PyramidController::on_radioBar_toggled(bool checked)
{
    if(checked){
        ui->graphicsView->setScene(m_views[1]);
        ui->checkBox->setDisabled(true);
        ui->groupBox_4->setDisabled(true);
    }
}

void PyramidController::on_checkBox_toggled(bool checked)
{
    for(int i=0; i<m_views.size(); ++i){
        m_views[i]->showPoints(checked);
    }
}
