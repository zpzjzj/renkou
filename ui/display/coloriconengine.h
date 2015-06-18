#ifndef COLORICONENGINE_H
#define COLORICONENGINE_H

#include <QIconEngine>

//绘制单色的图标
class ColorIconEngine : public QIconEngine
{
public:
    ColorIconEngine(QColor color);
    void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) override;
    void setColor(QColor color);
    ColorIconEngine *clone() const override {return new ColorIconEngine(m_Color);}

private:
    QColor m_Color;
};

#endif // COLORICONENGINE_H
