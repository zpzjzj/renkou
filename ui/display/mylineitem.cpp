#include <QPen>
#include <QPointF>
#include <QPainter>
#include "mylineitem.h"

MyLineItem::MyLineItem(const QLineF line)
{
    m_line = line;
    m_pen = QPen(Qt::black);
}

QRectF MyLineItem::boundingRect() const
{
    return QRectF(0, 0, 0, 0);
}

void MyLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QPen oldpen = painter->pen();
    painter->setPen(m_pen);
    painter->drawLine(m_line);
    painter->setPen(oldpen);
}

void MyLineItem::setPen(const QPen &pen)
{
    m_pen = pen;
}

void MyLineItem::setStartPoint(const QPointF &pos)
{
    m_line.setP1(pos);
}

QPointF MyLineItem::getStartPoint() const
{
    return m_line.p1();
}

void MyLineItem::setEndPoint(const QPointF &pos)
{
    m_line.setP2(pos);
}

QPointF MyLineItem::getEndPoint() const
{
    return m_line.p2();
}

void MyLineItem::setColor(const QColor &color)
{
    m_pen.setColor(color);
}

void MyLineItem::setWidthF(double w)
{
    m_pen.setWidthF(w);
}

int MyLineItem::type() const
{
    return Type;
}
