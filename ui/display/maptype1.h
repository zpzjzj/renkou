#ifndef MAPTYPE1_H
#define MAPTYPE1_H

#include <QWidget>
#include <QStateMachine>
#include "heightmap.h"
#include "dataprovider.h"
#include "FileInfo.h"
#include "Constants.h"

class QGLWidget;

QT_BEGIN_NAMESPACE
class QSlider;
class QTimer;
class QStateMachine;
class QState;
class QFinalState;
QT_END_NAMESPACE

namespace Ui {
    class MapType1;
}

class MapType1 : public QWidget
{
    Q_OBJECT
public:
    using DataSources = DataProvider::DataSources;
public:
    static MapType1* makeMapType1(QVector<QString> curve, DataSources file, int sYear, int eYear, QWidget *parent=0)
    { return new MapType1(curve, file, sYear, eYear, parent);}

    ~MapType1();

public slots:
    void setShowFlag(int f){m_ShowFlag = f;}

signals:
    void upperbound();  //  obsolete

private slots:
//    void on_colorRadio_toggled(bool checked);
//    void on_barRadio_toggled(bool checked);
    void on_comboBox_currentIndexChanged(int index);
    void on_back10YearButton_clicked();
    void on_advance10YearButton_clicked();
    void start();
    void pause();
    void stop();

private:
//    explicit MapType1(QWidget *parent=0);
    MapType1(QVector<QString> curve, DataSources file, int sYear, int eYear, QWidget *parent=0);
    QSlider *createSlider();
    void createStates();
    void createTransitions();
    void createConnections();
    void createGraphicsView(int sYear, int eYear);
    void initSideWidgets();

    int m_ShowFlag;

    Ui::MapType1 *ui;
    HeightMap *hm;

    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;

    QVector<QString> curves_;
    DataSources files_;
//    QTimer *timer;

    QStateMachine stateMachine;
    QState *initialState;
    QState *normalState;
    QState *stoppedState;
    QState *runningState;
    QState *pausedState;
    QFinalState *finalState;

    DataProvider *dp;
    int m_startYear;
    int m_endYear;
};

#endif // MAPTYPE1_H
