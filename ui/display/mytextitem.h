#ifndef MYTEXTITEM_H
#define MYTEXTITEM_H

#include <QGraphicsObject>
#include <QPointF>
#include <QColor>

class MyTextItem : public QGraphicsObject
{
    Q_OBJECT
public:
    enum{ Type = UserType + 3 };
    MyTextItem(QString str);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setColor(const QColor& color);
    void setExtraPoint(const QPointF &pos);
    int type() const;

private:
    QColor m_color;
    QString m_str;
    qreal m_px;
    qreal m_py;
};

#endif // MYTEXTITEM_H
