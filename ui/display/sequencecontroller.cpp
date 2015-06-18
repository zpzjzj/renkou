#include <QTextCodec>
#include <QBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QToolBox>
#include <QLabel>
#include <QList>
#include <QMutableMapIterator>
#include "coloriconengine.h"
#include "sequencecontroller.h"
#include "sequencestriplineview.h"
#include "sequencebarview3d.h"
#include "sequencebarview.h"
#include "Constants.h"
#include "ui_sequencecontroller.h"

template <class SequenceController>
        const int Counted<SequenceController>::maxObjects = 15;

SequenceController::SequenceController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SequenceController)
{
    ui->setupUi(this);

    m_model = NULL;
    m_leMaxValue.clear();
    m_leMinValue.clear();
    m_leAverageValue.clear();

    this->m_stateStop = NULL;
    this->m_statePlay = NULL;
    this->m_statePause = NULL;

    this->m_isPaused = false;

    this->m_timeLine = new MyTimeLine();
}

SequenceController::~SequenceController()
{
    delete ui;
    delete m_timeLine;
}

SequenceController* SequenceController::createSequenceController(QVector<QString> curves, DataSources files, int sy, int ey, QWidget *parent)
{
    SequenceController *sc = new SequenceController();
    if(sc->setup(curves, files, sy, ey))
        return sc;
    else{
        qDebug()<<"SequenceController::createSequenceController";
        return NULL;
    }
}

bool SequenceController::setup(QVector<QString> curves, DataSources files, int sy, int ey)
{
    bool ret = true;

    m_startYear = sy;
    m_endYear = ey;
    m_curves = curves;

    ret = setupSequenceModel(curves, files, sy, ey);
    if(! ret)
        return ret;

    ret = setupStateMachine();
    if(! ret)
        return ret;

    ret = setupWidgets();
    if(! ret)
        return ret;

    ui->radio3DBar->setChecked(true);
    updateOnCurrentYearChanged(m_startYear);

    return ret;
}

bool SequenceController::setupSequenceModel(QVector<QString> curves, DataSources files, int sy, int ey)
{
    bool ret = true;

    m_model = new SequenceModel(sy, ey, curves, files);
    QMutableMapIterator<QString, DataBlock> it(m_model->m_datas);
    int i=0;
    while(it.hasNext()){
        it.next();
        it.value().m_color = ColorForLine[i];
        i++;
    }

    return ret;
}

bool SequenceController::setupWidgets()
{
    bool ret = true;

//    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    setLayout(ui->verticalLayout_Main);

    // 初始化各种可视化方式
    m_views.clear();
    m_views["SequenceStripLineView"] = new SequenceStripLineView(m_model);
    m_views["SequenceBarView3D"] = new SequenceBarView3D(m_model);
    m_views["SequenceBarView"] = new SequenceBarView(m_model);

    m_timeLine->setFrameRange(m_startYear, m_endYear);
    m_timeLine->setInterval(500);

    foreach(AbstractSequenceView* view, m_views.values()){
        connect(m_timeLine, SIGNAL(frameChanged(int)), view, SLOT(changeCurrentYear(int)));
        connect(m_timeLine, SIGNAL(timeChanged(qreal)), view, SLOT(changeTime(qreal)));
        connect(ui->HLineButton, SIGNAL(toggled(bool)), view, SLOT(enableHorizonLine(bool)));
        connect(ui->VLineButton, SIGNAL(toggled(bool)), view, SLOT(enableVerticalLine(bool)));
        connect(ui->DualLineButton, SIGNAL(toggled(bool)), view, SLOT(enableCrossLine(bool)));
    }

    ui->NoLineButton->toggle();

    // 初始化年份选择框
    ui->comboBox->addItem(tr("更改年份"));
    for(int i=m_startYear; i<=m_endYear; ++i){
        ui->comboBox->addItem(QString::number(i));
    }

    // 初始化关键数据显示板
    QToolBox *valueBox = new QToolBox(this);
    for(int i=0; i<m_curves.size(); ++i){
        QBoxLayout* innerlayout = new QBoxLayout(QBoxLayout::TopToBottom);
        innerlayout->setSpacing(5);

        QLabel* labeltitle = new QLabel(tr("曲线名称"), this);
        innerlayout->addWidget(labeltitle);

        QLineEdit* letitle = new QLineEdit(this);
        letitle->setText(m_curves[i]);
        letitle->setReadOnly(true);
        innerlayout->addWidget(letitle);

        QLabel* labelmax = new QLabel(tr("最大值"), this);
        innerlayout->addWidget(labelmax);

        QLineEdit* lemax = new QLineEdit(this);
        lemax->setReadOnly(true);
        innerlayout->addWidget(lemax);
        m_leMaxValue.append(lemax);     // so called Java style

        QLabel* labelmin = new QLabel(tr("最小值"), this);
        innerlayout->addWidget(labelmin);

        QLineEdit* lemin = new QLineEdit(this);
        lemin->setReadOnly(true);
        innerlayout->addWidget(lemin);
        m_leMinValue.append(lemin);

        QLabel* labelave = new QLabel(tr("平均值"), this);
        innerlayout->addWidget(labelave);

        QLineEdit* leave = new QLineEdit(this);
        leave->setReadOnly(true);
        innerlayout->addWidget(leave);
        m_leAverageValue.append(leave);

        QWidget* bgwidget = new QWidget(this);
        bgwidget->setLayout(innerlayout);

        valueBox->addItem(bgwidget, tr("曲线")+QString::number(i+1));
        valueBox->setItemIcon(i, QIcon(new ColorIconEngine(m_model->m_datas[m_curves[i]].m_color)));
    }
    QBoxLayout *outerlayout = new QBoxLayout(QBoxLayout::TopToBottom);
    outerlayout->setMargin(5);
    outerlayout->addWidget(valueBox);
    ui->groupBox->setLayout(outerlayout);

    connect(m_timeLine, SIGNAL(frameChanged(int)), this, SLOT(updateOnCurrentYearChanged(int)));
    connect(valueBox, SIGNAL(currentChanged(int)), this, SLOT(selectCurve(int)));

    return ret;
}

bool SequenceController::setupStateMachine()
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

void SequenceController::start()
{
//    qDebug()<<"SequenceController::start()";
    if(!m_isPaused){
        foreach(AbstractSequenceView* view, m_views.values()){
            view->changeCurrentYear(m_startYear);
        }
        m_timeLine->start();
    }
    else{
        m_timeLine->resume();
    }
    m_isPaused = false;
}

void SequenceController::pause()
{
//    qDebug()<<"SequenceController::pause()";
    m_timeLine->pause();
    m_isPaused = true;
}

void SequenceController::stop()
{
//    qDebug()<<"SequenceController::stop()";
    m_timeLine->stop();
    m_isPaused = false;
}

void SequenceController::on_Advance10Button_clicked(bool checked)
{
    Q_UNUSED(checked)
    int year = m_timeLine->getFrame()+10;
    m_timeLine->setFrame(year);
}

void SequenceController::on_Back10Button_clicked(bool checked)
{
    Q_UNUSED(checked)
    int year = m_timeLine->getFrame()-10;
    m_timeLine->setFrame(year);
}

void SequenceController::updateOnCurrentYearChanged(int year)
{
//    qDebug()<<year;
//    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    for(int i=0; i<m_curves.size(); ++i){
        int maxindex = m_model->m_datas[m_curves[i]].m_maxValueYear[year-m_startYear];
        int minindex = m_model->m_datas[m_curves[i]].m_minValueYear[year-m_startYear];
        double maxvalue = m_model->m_datas[m_curves[i]].m_data[maxindex];
        double minvalue = m_model->m_datas[m_curves[i]].m_data[minindex];
        double avevalue = m_model->m_datas[m_curves[i]].m_averageValue[year-m_startYear];
        QString str;
        char s[32];
        if(maxvalue > 100000)
            sprintf(s, "%.0f", maxvalue);
        else
            sprintf(s, "%6f", maxvalue);
        str = QString::number(maxindex+m_startYear)+QObject::tr("年，")+QString(s);
        m_leMaxValue[i]->setText(str);
        if(minvalue > 100000)
            sprintf(s, "%.0f", minvalue);
        else
            sprintf(s, "%6f", minvalue);
        str = QString::number(minindex+m_startYear)+QObject::tr("年，")+QString(s);
        m_leMinValue[i]->setText(str);
        if(avevalue > 100000)
            sprintf(s, "%.0f", avevalue);
        else
            sprintf(s, "%6f", avevalue);
        m_leAverageValue[i]->setText(QString(s));
    }
}

void SequenceController::on_checkBox_toggled(bool checked)
{
    foreach(AbstractSequenceView* view, m_views.values()){
        view->showPoints(checked);
    }
}

void SequenceController::on_comboBox_currentIndexChanged(QString s)
{
    bool ok;
    int year = s.toInt(&ok);
    if(ok){
        m_timeLine->setFrame(year);
    }
}

void SequenceController::on_radioCurve_toggled(bool checked)
{
    if(checked){
        ui->graphicsView->setScene(m_views["SequenceStripLineView"]);
        ui->checkBox->setDisabled(false);
        ui->groupBox_4->setDisabled(false);
    }
}


void SequenceController::on_radioBar_toggled(bool checked)
{
    if(checked){
        ui->graphicsView->setScene(m_views["SequenceBarView"]);
        ui->checkBox->setDisabled(true);
        ui->groupBox_4->setDisabled(true);
    }
}

void SequenceController::on_radio3DBar_toggled(bool checked)
{
    if(checked){
        ui->graphicsView->setScene(m_views["SequenceBarView3D"]);
        ui->checkBox->setDisabled(true);
        ui->groupBox_4->setDisabled(true);
    }
}

void SequenceController::selectCurve(int index)
{
    foreach(AbstractSequenceView * view, m_views.values()){
        view->selectCurve(m_curves[index]);
    }
}

