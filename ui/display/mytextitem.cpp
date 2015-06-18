#include "mytextitem.h"
#include <QtGui>
#include <QtCore>

MyTextItem::MyTextItem(QString str)
{
    m_str = str;
    m_px = 0.0;
    m_py = 0.0;
}

QRectF MyTextItem::boundingRect() const
{
    return QRectF(0, 0, 8*m_str.length(), 12);
}

void MyTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    const QRectF rect = boundingRect();

    painter->setPen(Qt::black);
    painter->drawRect(rect);

    painter->setOpacity(0.5);
    painter->fillRect(rect, Qt::white);

    painter->setOpacity(1.0);
    painter->setFont(QFont("Arial", 10 ,1));
    painter->setPen(m_color);
    painter->drawText(rect, Qt::AlignCenter, m_str);

    QPointF p = rect.topLeft();
    qreal d1 = (p.x()-m_px)*(p.x()-m_px) + (p.y()-m_py)*(p.y()-m_py);

    p = rect.topRight();
    qreal d2 = (p.x()-m_px)*(p.x()-m_px) + (p.y()-m_py)*(p.y()-m_py);

    p = rect.bottomLeft();
    qreal d3 = (p.x()-m_px)*(p.x()-m_px) + (p.y()-m_py)*(p.y()-m_py);

    p = rect.bottomRight();
    qreal d4 = (p.x()-m_px)*(p.x()-m_px) + (p.y()-m_py)*(p.y()-m_py);

//    painter->setPen(Qt::black);
    if(d1<=d2 && d1<=d3 && d1<=d4){
        painter->drawLine(QPointF(m_px, m_py), rect.topLeft());
    }else if(d2<=d1 && d2<=d3 && d2<=d4){
        painter->drawLine(QPointF(m_px, m_py), rect.topRight());
    }else if(d3<=d1 && d3<=d2 && d3<=d4){
        painter->drawLine(QPointF(m_px, m_py), rect.bottomLeft());
    }else if(d4<=d1 && d4<=d2 && d4<=d3){
        painter->drawLine(QPointF(m_px, m_py), rect.bottomRight());
    }
}

void MyTextItem::setColor(const QColor &color)
{
    m_color = color;
}

void MyTextItem::setExtraPoint(const QPointF &pos)
{
    m_px = pos.x();
    m_py = pos.y();
}

int MyTextItem::type() const
{
    return Type;
}
