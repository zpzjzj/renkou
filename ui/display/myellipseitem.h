#ifndef MYELLIPSEITEM_H
#define MYELLIPSEITEM_H

#include <QGraphicsObject>
#include <QPointF>
#include <QPen>
#include <QColor>
#include <QMap>
#include <QVariant>

class MyEllipseItem : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(QPointF center READ getCenter WRITE setCenter);
public:
    enum { Type = UserType+2 };
    MyEllipseItem(const QPointF &pos, qreal rx, qreal ry);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPointF getCenter() const;
    void setCenter(const QPointF &pos);
    void setPen(const QPen& pen);
    void setColor(const QColor& color);
    QColor color(){ return m_pen.color(); }
    int type() const;
    void setRadius(qreal r);
    void setShow(bool flag);        //设置是否绘制，不影响对鼠标等事件的响应
    void showOnce();
    bool isShow(){  return m_show;  }

private:
    QPen m_pen;
    QPointF m_center;
    qreal m_rx;
    qreal m_ry;

    bool m_show;
    bool m_showOnce;
};

#endif // MYELLIPSEITEM_H
