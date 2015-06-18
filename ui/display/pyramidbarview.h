#ifndef PYRAMIDBARVIEW_H
#define PYRAMIDBARVIEW_H

#include "abstractpyramidview.h"
#include "pyramidmodel.h"
#include "pyramidviewbaritem.h"
#include <QVector>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>

class PyramidBarView : public AbstractPyramidView
{
    Q_OBJECT
public:
    PyramidBarView(PyramidModel *model, QObject *parent=0);

    void showPoints(bool flag);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void changeCurrentYear(int year);
    void changeTime(qreal value);
    void selectCurve(QString curvename);

private:
    void initScene();

    bool m_showPoint;

    PyramidViewBarItem *m_mainItem;
};

#endif // PYRAMIDBARVIEW_H
