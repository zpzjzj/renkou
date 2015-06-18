#ifndef PYRAMIDVIEWBARITEM_H
#define PYRAMIDVIEWBARITEM_H

#include <QGraphicsObject>
#include "pyramidmodel.h"
#include <QVector>
#include <QMap>
#include <QPair>

QT_BEGIN_NAMESPACE
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
QT_END_NAMESPACE

class PyramidViewBarItem : public QGraphicsObject
{
    Q_OBJECT
public:
    PyramidViewBarItem(PyramidModel *model, QGraphicsItem * parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

public slots:
    void changeCurrentYear(int year);
    void changeCurrentT(qreal t);
    void selectCurve(QString curvename);

private:
    void drawRects(QPainter *painter);
    void drawAgeLabel(QPainter *painter);
    void drawYearLabel(QPainter *painter);
    void drawPopulationLabel(QPainter *painter);
    void drawBars(QPainter *painter);
    void drawSelectedCurve(QPainter *painter, QString curve);

    PyramidModel *m_model;
    int m_startYear;
    int m_endYear;
    int m_currentYear;
    qreal m_currentT;    // a value between 0 and 1

    QVector<QPair<double, QString> > m_order;
    QString m_selectedCurve;

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
};

#endif // PYRAMIDVIEWBARITEM_H
