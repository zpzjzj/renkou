#ifndef PYRAMIDSTRIPVIEW_H
#define PYRAMIDSTRIPVIEW_H

#include "abstractpyramidview.h"
#include "pyramidviewstripitem.h"
#include "pyramidmodel.h"
#include "myellipseitem.h"
#include "mytextitem.h"
#include <QVector>
#include <QMap>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>

class PyramidStripView : public AbstractPyramidView
{
    Q_OBJECT
public:
    PyramidStripView(PyramidModel *model, QObject *parent = 0);

    void showPoints(bool flag);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void changeCurrentYear(int year);
    void changeTime(qreal value);
    void selectCurve(QString curvename);
    void enableHorizonLine(bool flag);
    void enableVerticalLine(bool flag);
    void enableCrossLine(bool flag);

private:
    void initScene();

    void handleHorizonLine();
    void handleVerticalLine();
    void handleCrossLine();

    int m_currentYear;
    qreal m_currentTime;

    bool m_showPoint;

    PyramidViewStripItem *m_mainItem;
    QMap<QString, QVector<MyEllipseItem*> > m_points;

    double m_width;
    double m_height;

    double m_maleX1;
    double m_maleX2;
    double m_femaleX1;
    double m_femaleX2;
    double m_plotY1;
    double m_plotY2;
    double m_labelMin;
    double m_labelMax;
    double m_ticks;

    double m_pointRadius;

    MyTextItem *m_lastText;
    QList<MyTextItem*> m_texts;
    QGraphicsLineItem *m_horizonLine;
    QGraphicsLineItem *m_verticalLine;

    static const int kTextLayer = 21;
    static const int kPointLayerHigh = 11;
    static const int kPointLayerLow = 10;
    static const int kBackgroundLayer = 0;
};

#endif // PYRAMIDSTRIPVIEW_H
