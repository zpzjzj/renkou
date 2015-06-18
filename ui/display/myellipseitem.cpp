#include <QtGui>
#include <QtCore>
#include "myellipseitem.h"

MyEllipseItem::MyEllipseItem(const QPointF &pos, qreal rx, qreal ry)
{
    m_center = pos;
    m_rx = rx;
    m_ry = ry;
    m_pen = QPen(Qt::black);
    m_pen.setBrush(QBrush(Qt::black));

    m_show = false;
    m_showOnce = false;
}

QRectF MyEllipseItem::boundingRect() const
{
    return QRectF(m_center.x()-m_rx, m_center.y()-m_ry, m_rx*2, m_ry*2);
}

QPainterPath MyEllipseItem::shape() const
{
    QPainterPath path;

    // 用标尺交互时可以减少选中的点数量
    if(m_showOnce)
        path.addEllipse(m_center.x()-m_rx/2, m_center.y()-m_ry/2, m_rx, m_ry);
    else
        path.addEllipse(m_center.x()-m_rx, m_center.y()-m_ry, m_rx*2, m_ry*2);

    return path;
}

void MyEllipseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(!m_show && !m_showOnce)
        return;

    QPen oldpen = painter->pen();
    painter->setPen(m_pen);
    painter->setBrush(QBrush(m_pen.color()));
    painter->drawEllipse(m_center, m_rx, m_ry);
    painter->setPen(oldpen);

    m_showOnce = false;
}

QPointF MyEllipseItem::getCenter() const
{
    return m_center;
}

void MyEllipseItem::setCenter(const QPointF &pos)
{
    m_center = pos;
}

void MyEllipseItem::setPen(const QPen &pen)
{
    m_pen = pen;
}

void MyEllipseItem::setColor(const QColor &color)
{
    m_pen.setColor(color);
}

int MyEllipseItem::type() const
{
    return Type;
}

void MyEllipseItem::setRadius(qreal r)
{
    m_rx = m_ry = r;
}

void MyEllipseItem::setShow(bool flag)
{
    m_show = flag;
}

void MyEllipseItem::showOnce()
{
    m_showOnce = true;
}
