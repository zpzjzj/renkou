#ifndef SEQUENCECONTROLLER_H
#define SEQUENCECONTROLLER_H

#include <QWidget>
#include <QStateMachine>
#include <QGraphicsScene>
#include <QVector>
#include <QMap>
#include <QLineEdit>
#include "mytimeline.h"
#include "Objectcounter.h"
#include "FileInfo.h"
#include "sequencemodel.h"
#include "abstractsequenceview.h"

namespace Ui {
    class SequenceController;
}

class SequenceController : public QWidget , Counted<SequenceController>
{
    Q_OBJECT

public:
    using Counted<SequenceController>::objectCount;
    using Counted<SequenceController>::TooManyObjects;
    using DataSources = SequenceModel::DataSources;

    static SequenceController* createSequenceController(QVector<QString> curves, DataSources files, int sy, int ey, QWidget *parent=0);

    ~SequenceController();

public slots:
//    void setShowFlag(int f){}

private slots:
    void on_radio3DBar_toggled(bool checked);
    void on_radioBar_toggled(bool checked);
    void on_radioCurve_toggled(bool checked);
    void on_comboBox_currentIndexChanged(QString );
    void on_checkBox_toggled(bool checked);
    void on_Back10Button_clicked(bool checked);
    void on_Advance10Button_clicked(bool checked);
    void start();
    void pause();
    void stop();
    void updateOnCurrentYearChanged(int year);
    void selectCurve(int index);

private:
    explicit SequenceController(QWidget *parent = 0);
    bool setup(QVector<QString> curves, DataSources files, int sy, int ey);
    bool setupSequenceModel(QVector<QString> curves, DataSources files, int sy, int ey);
    bool setupWidgets();
    bool setupStateMachine();

    Ui::SequenceController *ui;

    QStateMachine m_stateMachine;
    QState* m_stateStop;
    QState* m_statePlay;
    QState* m_statePause;
    bool m_isPaused;

    SequenceModel *m_model;
    QMap<QString, AbstractSequenceView*> m_views;

    int m_startYear;
    int m_endYear;
    QVector<QString> m_curves;
    QVector<QLineEdit*> m_leMaxValue;
    QVector<QLineEdit*> m_leMinValue;
    QVector<QLineEdit*> m_leAverageValue;

    MyTimeLine *m_timeLine;
};

#endif // SEQUENCECONTROLLER_H
