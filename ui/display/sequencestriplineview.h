#ifndef SEQUENCESTRIPLINEVIEW_H
#define SEQUENCESTRIPLINEVIEW_H

#include "sequencemodel.h"
#include "myellipseitem.h"
#include "mylineitem.h"
#include "sequencestripviewitem.h"
#include "abstractsequenceview.h"
#include "mytextitem.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QVector>
#include <QMap>
#include <QGraphicsScene>

class SequenceStripLineView : public AbstractSequenceView
{
    Q_OBJECT
public:
    SequenceStripLineView(SequenceModel *model, QObject *parent = 0);

    void showPoints(bool flag);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

signals:
    void animationOver();
    void yearChanged(int);

public slots:
    void changeCurrentYear(int year);
    void changeTime(qreal value);
    void selectCurve(QString curve);
    void enableHorizonLine(bool flag);
    void enableVerticalLine(bool flag);
    void enableCrossLine(bool flag);

private:
    void initScene();

    void handleHorizonLine();
    void handleVerticalLine();
    void handleCrossLine();

    double m_width;
    double m_height;

    double m_plotX1;
    double m_plotX2;
    double m_plotY1;
    double m_plotY2;
    double m_labelMin;
    double m_labelMax;
    double m_ticks;

    double m_pointRadius;

    bool m_showPoints;

    SequenceStripViewItem *m_mainItem;
    QMap<QString, QVector<MyEllipseItem*> > m_points;

    MyTextItem* m_textItem;
    QGraphicsLineItem *m_horizonLine;
    QGraphicsLineItem *m_verticalLine;
    QList<MyTextItem*> m_texts;

    static const int kTextLayer = 21;
    static const int kPointLayerHigh = 11;
    static const int kPointLayerLow = 10;
    static const int kBackgroundLayer = 0;
};

#endif // SEQUENCESTRIPLINEVIEW_H
