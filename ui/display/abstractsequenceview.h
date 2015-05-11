#ifndef ABSTRACTSEQUENCEVIEW_H
#define ABSTRACTSEQUENCEVIEW_H

#include "sequencemodel.h"
#include <QGraphicsScene>

class AbstractSequenceView : public QGraphicsScene
{
    Q_OBJECT
public:
    AbstractSequenceView(SequenceModel *model, QObject *parent = 0);

    int currentYear() const;
    virtual void showPoints(bool flag);

signals:
    void animationOver();
    void yearChanged(int);

public slots:
    virtual void changeCurrentYear(int year) = 0;
    virtual void changeTime(qreal value) = 0;
    virtual void selectCurve(QString curve) = 0;
    virtual void enableHorizonLine(bool flag);
    virtual void enableVerticalLine(bool flag);
    virtual void enableCrossLine(bool flag);

protected:
    SequenceModel *m_model;
    int m_startYear;
    int m_endYear;
    int m_currentYear;

    bool m_horizonFlag;
    bool m_verticalFlag;
    bool m_crossFlag;
};

#endif // ABSTRACTSEQUENCEVIEW_H
