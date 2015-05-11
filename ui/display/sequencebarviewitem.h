#ifndef SEQUENCEBARVIEWITEM_H
#define SEQUENCEBARVIEWITEM_H

#include "sequencemodel.h"
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QVector>
#include <QPair>
#include <QString>

QT_BEGIN_NAMESPACE
class QStyleOptionGraphicsItem;
class QWidget;
QT_END_NAMESPACE

class SequenceBarViewItem : public QGraphicsObject
{
    Q_OBJECT
public:
    SequenceBarViewItem(SequenceModel *model, QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

signals:

public slots:
    void changeCurrentYear(int year);
    void changeCurrentT(qreal t);
    void selectCurve(QString curve);

private:
    void drawBackground(QPainter *painter);
    void drawYearLabel(QPainter *painter);
    void drawVolumeLabel(QPainter *painter);
    void drawCurves(QPainter *painter);
    void drawSelectedCurve(QPainter *painter, QString curvename);

    SequenceModel *m_model;

    int m_startYear;
    int m_endYear;
    int m_currentYear;
    qreal m_currentT;

    double m_width;
    double m_height;

    double m_plotX1;
    double m_plotX2;
    double m_plotY1;
    double m_plotY2;

    double m_labelMax;
    double m_labelMin;
    int m_ticks;

    QVector<QPair<double, QString> > m_order;
    QString m_selectedCurve;
};

#endif // SEQUENCEBARVIEWITEM_H
