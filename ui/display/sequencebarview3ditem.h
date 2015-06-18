#ifndef SEQUENCEBARVIEW3DITEM_H
#define SEQUENCEBARVIEW3DITEM_H

#include "sequencemodel.h"
#include <QGraphicsObject>
#include <QVector>
#include <QPair>

QT_BEGIN_NAMESPACE
class QGraphicsItem;
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
QT_END_NAMESPACE

class SequenceBarView3DItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit SequenceBarView3DItem(SequenceModel *model, QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

signals:

public slots:
    void changeCurrentYear(int year);
    void changeCurrentT(qreal t);
    void selectCurve(QString curvename);

private:
    void drawBackground(QPainter *painter);
    void drawYearLabel(QPainter *painter);
    void drawVolumeLabel(QPainter *painter);
    void draw3DBars(QPainter *painter);
    void drawSelectedBar(QPainter *painter, QString curvename);

    SequenceModel *m_model;
    int m_startYear;
    int m_endYear;
    int m_currentYear;
    qreal m_currentT;

    double m_labelMax;
    double m_labelMin;
    int m_ticks;

    QVector<QPair<double, QString> > m_order;
    QString m_selectedCurve;

    double m_width;
    double m_height;

    double m_plotX1;
    double m_plotY1;
    double m_xLen;      //x方向的长度
    double m_yLen;      //y方向的长度
    double m_zLen;      //z方向的长度
    double m_margin;    //多出来的长度

    //x,y,z三个方向上的基向量
    QPointF m_xBase;
    QPointF m_yBase;
    QPointF m_zBase;
    QPointF m_leftDownPoint;
    QPointF m_zeroPoint;
};

#endif // SEQUENCEBARVIEW3DITEM_H
