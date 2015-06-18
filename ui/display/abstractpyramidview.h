#ifndef ABSTRACTPYRAMIDVIEW_H
#define ABSTRACTPYRAMIDVIEW_H

#include "pyramidmodel.h"
#include <QGraphicsScene>

class AbstractPyramidView : public QGraphicsScene
{
    Q_OBJECT
public:
    AbstractPyramidView(PyramidModel *model, QObject *parent = 0);

    int currentYear() const;
    virtual void showPoints(bool flag) = 0;

signals:
    void animationOver();
    void yearChanged(int);

public slots:
    virtual void changeCurrentYear(int year) = 0;
    virtual void changeTime(qreal value) = 0;
    virtual void selectCurve(QString curvename) = 0;
    virtual void enableHorizonLine(bool flag);
    virtual void enableVerticalLine(bool flag);
    virtual void enableCrossLine(bool flag);

protected:
    int m_startYear;
    int m_endYear;
    int m_currentYear;
    PyramidModel *m_model;

    bool m_horizonFlag;
    bool m_verticalFlag;
    bool m_crossFlag;
};

#endif // ABSTRACTPYRAMIDVIEW_H
