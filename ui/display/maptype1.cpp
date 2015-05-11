#include <QtGui>
#include <QGLWidget>
#include <QTextCodec>
#include "maptype1.h"
#include "ui_maptype1.h"

MapType1::MapType1(QVector<QString> curve, QVector<FileInfo> file, int sYear, int eYear, QWidget *parent):
        QWidget(parent), m_startYear(sYear), m_endYear(eYear),
        ui(new Ui::MapType1)
{
    ui->setupUi(this);
    this->curves_ = curve;
    this->files_ = file;
    createGraphicsView(sYear, eYear);
    createStates();
    createTransitions();
    createConnections();
    initSideWidgets();

    stateMachine.setInitialState(initialState);
    stateMachine.start();
}

MapType1::~MapType1()
{
    delete ui;
}

void MapType1::createStates()
{
    //汉字支持
//    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    //初始停止键不可用
    initialState = new QState(&stateMachine);
    initialState->assignProperty(ui->stopButton, "enabled", false);

    normalState = new QState(&stateMachine);
    //开始播放，开始键文字改为“暂停”，停止键可用
    runningState = new QState(normalState);
    runningState->assignProperty(ui->playButton, "text", tr("暂停"));
    runningState->assignProperty(ui->stopButton, "enabled", true);

    pausedState = new QState(normalState);
    pausedState->assignProperty(ui->playButton ,"text", tr("继续"));

    stoppedState = new QState(normalState);
    stoppedState->assignProperty(ui->playButton, "text", tr("开始"));
    stoppedState->assignProperty(ui->stopButton, "enabled", false);

    finalState = new QFinalState(&stateMachine);
}

void MapType1::createConnections()
{
    connect(runningState, SIGNAL(entered()), this, SLOT(start()));
    connect(pausedState, SIGNAL(entered()), this, SLOT(pause()));
    connect(stoppedState, SIGNAL(entered()), this, SLOT(stop()));
}

void MapType1::pause()
{
    hm->pauseAnimation();
}

void MapType1::start()
{
    hm->startAnimation();
}

void MapType1::stop()
{
    hm->stopAnimation();
}

void MapType1::createTransitions()
{
    initialState->addTransition(initialState, SIGNAL(propertiesAssigned()), stoppedState);
    runningState->addTransition(ui->playButton, SIGNAL(clicked()), pausedState);
    runningState->addTransition(ui->stopButton, SIGNAL(clicked()), stoppedState);
    runningState->addTransition(hm, SIGNAL(animationOver()), stoppedState);
//    runningState->addTransition(ui->advance10YearButton, SIGNAL(clicked()), pausedState);
//    runningState->addTransition(ui->back10YearButton, SIGNAL(clicked()), pausedState);
//    runningState->addTransition(ui->ViewDataButton, SIGNAL(clicked()), pausedState);
    pausedState->addTransition(ui->playButton, SIGNAL(clicked()), runningState);
    pausedState->addTransition(ui->stopButton, SIGNAL(clicked()), stoppedState);
    stoppedState->addTransition(ui->playButton, SIGNAL(clicked()), runningState);
    pausedState->addTransition(hm, SIGNAL(animationOver()), stoppedState);
}

void MapType1::createGraphicsView(int sYear, int eYear)
{
    QStringList cur;
    for(int i=0; i<this->curves_.size(); ++i)
        cur<<this->curves_[i];

    dp = new DataProvider(sYear, eYear, cur, files_);
    hm = new HeightMap(this);
    hm->init(sYear, eYear, *dp);

    xSlider = createSlider();
    ySlider = createSlider();
    zSlider = createSlider();

    connect(xSlider, SIGNAL(valueChanged(int)), hm, SLOT(setXRotation(int)));
    connect(ySlider, SIGNAL(valueChanged(int)), hm, SLOT(setYRotation(int)));
    connect(zSlider, SIGNAL(valueChanged(int)), hm, SLOT(setZRotation(int)));
    connect(hm, SIGNAL(xRotationChanged(int)), xSlider, SLOT(setValue(int)));
    connect(hm, SIGNAL(yRotationChanged(int)), ySlider, SLOT(setValue(int)));
    connect(hm, SIGNAL(zRotationChanged(int)), zSlider, SLOT(setValue(int)));

    ui->horizontalLayout_2->addWidget(hm);
    ui->horizontalLayout_2->addWidget(xSlider);
    ui->horizontalLayout_2->addWidget(ySlider);
    ui->horizontalLayout_2->addWidget(zSlider);
    ui->horizontalLayout_2->setSpacing(10);
    ui->horizontalLayout_2->setMargin(10);
//    ui->widget->setLayout(ui->layout_graph);

    setLayout(ui->verticalLayout_main);

    xSlider->setValue(30 * 16);
    ySlider->setValue(0 * 16);
    zSlider->setValue(0 * 16);
    setWindowTitle(tr("Hello GL"));
}

void MapType1::initSideWidgets()
{
    ui->comboBox->addItem(tr("更改年份"));
    for(int k=m_startYear; k<=m_endYear; k++)
        ui->comboBox->addItem(QString::number(k));

    //默认使用柱状模式
    ui->barRadio->setChecked(true);
}

QSlider* MapType1::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360*16);
    slider->setSingleStep(8);
    slider->setPageStep(15*16);
    slider->setTickInterval(15*16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

void MapType1::on_advance10YearButton_clicked()
{
    int year = hm->getCurrentYear() + 10;
    hm->setCurrentYear(year);
}

void MapType1::on_back10YearButton_clicked()
{
    int year = hm->getCurrentYear() - 10;
    hm->setCurrentYear(year);
}

void MapType1::on_comboBox_currentIndexChanged(int index)
{
    if(index != 0){
        hm->setCurrentYear(ui->comboBox->itemText(index).toInt());
    }
}
