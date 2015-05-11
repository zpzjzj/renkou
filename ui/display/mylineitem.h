#ifndef MYLINEITEM_H
#define MYLINEITEM_H

#include <QGraphicsObject>
#include <QPen>
#include <QLineF>
#include <QColor>

class MyLineItem : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(QPointF startPoint READ getStartPoint WRITE setStartPoint)
    Q_PROPERTY(QPointF endPoint READ getEndPoint WRITE setEndPoint)

public:
    enum {Type = UserType+1};
    MyLineItem(const QLineF line);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setPen(const QPen &pen);
    QRectF boundingRect() const;
    void setStartPoint(const QPointF &pos);
    QPointF getStartPoint() const;
    void setEndPoint(const QPointF &pos);
    QPointF getEndPoint() const;
    void setColor(const QColor& color);
    void setWidthF(double w);
    int type() const;

private:
    QLineF m_line;
    QPen m_pen;
};

#endif // MYLINEITEM_H
