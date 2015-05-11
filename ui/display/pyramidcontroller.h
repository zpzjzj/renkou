#ifndef PYRAMIDCONTROLLER_H
#define PYRAMIDCONTROLLER_H

#include <QState>
#include <QFinalState>
#include <QStateMachine>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QVector>
#include <QLineEdit>
#include <QWidget>
#include "Objectcounter.h"
#include "FileInfo.h"
#include "abstractpyramidview.h"
#include "mytimeline.h"

class PyramidView;
class QValueBoard;

namespace Ui {
    class PyramidController;
}

class PyramidController : public QWidget, private Counted<PyramidController>
{
    Q_OBJECT

public:
    using Counted<PyramidController>::objectCount;
    using Counted<PyramidController>::TooManyObjects;

    static PyramidController* createPyramidController(QVector<QString> curves, QVector<FileInfo> files, int sy, int ey, QWidget *parent=0);

    ~PyramidController();

public slots:
//    void setShowFlag(int f){}

private slots:
    void on_checkBox_toggled(bool checked);
    void on_radioBar_toggled(bool checked);
    void on_radioCurve_toggled(bool checked);
    void on_comboBox_currentIndexChanged(QString );
    void on_Back10Button_clicked(bool checked);
    void on_Advance10Button_clicked(bool checked);
    void start();
    void pause();
    void stop();
    void setViewMode(int chosen);   // 选择可视化效果
    void updateOnCurrentYearChanged(int year);
    void selectCurve(int index);

private:
    explicit PyramidController(QWidget *parent=0);
    bool setup(QVector<QString> curves, QVector<FileInfo> files, int sy, int ey);
    bool setupPyramidModel(QVector<QString> curve, QVector<FileInfo> files, int sy, int ey);
    bool setupWidgets();
    bool setupStateMachine();

    Ui::PyramidController *ui;

    QStateMachine m_stateMachine;
    QState* m_stateStop;
    QState* m_statePlay;
    QState* m_statePause;
    bool m_isPaused;

    PyramidModel *m_model;
    AbstractPyramidView* m_currentView;
    QVector<AbstractPyramidView*> m_views;

//    QGraphicsScene *m_scene;

    int m_startYear;
    int m_endYear;
    QVector<QString> m_curves;
    QVector<QLineEdit*> m_leMaxPopulation;
    QVector<QLineEdit*> m_leMinPopulation;
    QVector<QLineEdit*> m_leMiddleAge;
    QVector<QLineEdit*> m_leAverageAge;

    MyTimeLine *m_timeLine;
};

#endif // PYRAMIDCONTROLLER_H
