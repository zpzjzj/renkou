#include "pyramidviewbaritem.h"
#include "MyUtility.h"
#include "Constants.h"
#include <vector>
#include <algorithm>
#include <QPainter>
#include <QMapIterator>
#include <QPair>
#include <QTextCodec>
#include <QPainterPath>
#include <QDebug>
using namespace std;

PyramidViewBarItem::PyramidViewBarItem(PyramidModel *model, QGraphicsItem * parent) :
    QGraphicsObject(parent)
{
    m_model = model;
    m_startYear = model->m_startYear;
    m_endYear = model->m_endYear;
    m_currentYear = m_startYear;
    m_currentT = 0.0;

    m_width = 720;
    m_height = 600;

    m_maleX1 = m_width/2 - 10;
    m_maleX2 = 50;
    m_femaleX1 = m_width/2 + 10;
    m_femaleX2 = m_width-50;
    m_plotY1 = m_height - 60;
    m_plotY2 = 60;

    m_order.clear();
    QMapIterator<QString, vector<double> > it(m_model->m_totalPopulation);
    while(it.hasNext()){
        it.next();
        double sum = 0;
        for(int i=0; i<(int)it.value().size(); ++i){
            sum += it.value().at(i);
        }
        m_order.push_back(qMakePair(-sum, it.key()));
    }
    qSort(m_order.begin(), m_order.end());

    m_selectedCurve = "";

    double d[3];
    loose_label(5, 0.0, m_model->m_maxValue, d);
    m_labelMin = d[0];
    m_labelMax = d[1];
    m_ticks = (d[1]-d[0]) / d[2];

    this->setFlag(ItemSendsGeometryChanges);
    this->setZValue(0);
}

QRectF PyramidViewBarItem::boundingRect() const
{
    return QRectF(0, 0, m_width, m_height);
}

void PyramidViewBarItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    drawRects(painter);

    drawAgeLabel(painter);

    drawYearLabel(painter);

    drawPopulationLabel(painter);

    drawBars(painter);

    drawSelectedCurve(painter, m_selectedCurve);
}

void PyramidViewBarItem::drawRects(QPainter *painter)
{
    painter->save();

    painter->fillRect(this->boundingRect(), BGCOLOR);
    painter->fillRect(QRectF(m_maleX2, m_plotY2, m_maleX1-m_maleX2, m_plotY1-m_plotY2),
                      Qt::white);
    painter->fillRect(QRectF(m_femaleX1, m_plotY2, m_femaleX2-m_femaleX1, m_plotY1-m_plotY2),
                      Qt::white);

    QPen pen(BGCOLOR);
    pen.setWidth(1);
    painter->drawRect(m_maleX2, m_plotY2, m_maleX1-m_maleX2, m_plotY1-m_plotY2);
    painter->drawRect(m_femaleX1, m_plotY2, m_femaleX2-m_femaleX1, m_plotY1-m_plotY2);

    painter->restore();
}

void PyramidViewBarItem::drawAgeLabel(QPainter *painter)
{
    QPen oldpen = painter->pen();

    QPen pen(DASHCOLOR);
    pen.setWidth(1);
    painter->setPen(pen);
    double dy = (m_plotY2 - m_plotY1) / 110;
    double y = m_plotY1;
    for(int i=0; i<=110; ++i){
        painter->drawLine(m_maleX1-2, y, m_maleX1, y);
        painter->drawLine(m_femaleX1, y, m_femaleX1+2, y);
        y += dy;
    }
    pen.setColor(Qt::black);
    painter->setPen(pen);
    y = m_plotY1;
    for(int i=0; i<=110; i+=5){
        painter->drawText(QRectF(m_maleX1-5, y-5, m_femaleX1-m_maleX1+10, 10),
                          Qt::AlignCenter,
                          QString::number(i));
        y += 5 * dy;
    }
    painter->drawText(QRectF(m_maleX1-5, y-5, m_femaleX1-m_maleX1+10, 10),
                      Qt::AlignCenter,
                      tr("年龄"));

    painter->drawText(QRectF(m_maleX1-50, y-5, 50, 10),
                      Qt::AlignLeft | Qt::AlignVCenter,
                      tr("男"));

    painter->drawText(QRectF(m_femaleX1, y-5, 50, 10),
                      Qt::AlignRight | Qt::AlignVCenter,
                      tr("女"));

    painter->setPen(oldpen);
}

void PyramidViewBarItem::drawYearLabel(QPainter *painter)
{
    QPen oldpen = painter->pen();

    QPen pen(DASHCOLOR);
    pen.setWidth(1);
    painter->setPen(pen);

    double dy = (m_plotY2 - m_plotY1) / 110;
    double y = m_plotY1;
    for(int i=0; i<=110; i+=10){
        painter->drawLine(m_maleX2, y, m_maleX2+4, y);
        painter->drawLine(m_femaleX2-4, y, m_femaleX2, y);
        y += 10 * dy;
    }

    pen.setColor(Qt::black);
    painter->setPen(pen);
    y = m_plotY1;
    for(int i=0; i<=110; i+=10){
        QString str = QString::number(m_currentYear - i);
        painter->drawText(QRectF(m_maleX2-30, y-5, 30, 10),
                          Qt::AlignLeft | Qt::AlignVCenter ,
                          str);
        painter->drawText(QRectF(m_femaleX2, y-5, 30, 10),
                          Qt::AlignRight | Qt::AlignVCenter,
                          str);
        y += 10 * dy;
    }

    y = m_plotY2 + 5*dy;
    painter->drawText(QRectF(m_maleX2-30, y-5, 100, 10),
                      Qt::AlignLeft | Qt::AlignVCenter,
                      tr("出生年份"));
    painter->drawText(QRectF(m_femaleX2-70, y-5, 100, 10),
                      Qt::AlignRight | Qt::AlignVCenter,
                      tr("出生年份"));

    painter->setPen(oldpen);
}

void PyramidViewBarItem::drawPopulationLabel(QPainter *painter)
{
    painter->save();

    QPen pen;
    pen.setWidth(1);
    double dx = (m_maleX2 - m_maleX1) / m_ticks;
    double dv = m_labelMax / m_ticks;
    double v = 0.0;
    double x = m_maleX1;
    QString str;
    for(int i=0; i<=m_ticks; ++i){
        if(i != 0 && i!=m_ticks){
            pen.setColor(DASHCOLOR);
            painter->setPen(pen);
            painter->drawLine(x, m_plotY1, x, m_plotY2);
        }
        pen.setColor(Qt::black);
        painter->setPen(pen);
        painter->drawText(QRectF(x-20, m_plotY1+10, 40, 10),
                          Qt::AlignBottom|Qt::AlignHCenter,
                          str.sprintf("%.0f", v));
        v += dv;
        x += dx;
    }

    v = 0.0;
    x = m_femaleX1;
    dx = (m_femaleX2 - m_femaleX1) / m_ticks;
    for(int i=0; i<=m_ticks; ++i){
        if(i != 0 && i!=m_ticks){
            pen.setColor(DASHCOLOR);
            painter->setPen(pen);
            painter->drawLine(x, m_plotY1, x, m_plotY2);
        }
        pen.setColor(Qt::black);
        painter->setPen(pen);
        painter->drawText(QRectF(x-20, m_plotY1+10, 40, 10),
                          Qt::AlignBottom|Qt::AlignHCenter,
                          str.sprintf("%.0f", v));
        v += dv;
        x += dx;
    }

    painter->drawText(QRectF(m_maleX2, m_plotY1+25, m_femaleX2-m_maleX2, 10),
                      Qt::AlignCenter,
                      tr("人口数量(单位：万人)"));

    painter->restore();
}

void PyramidViewBarItem::drawBars(QPainter *painter)
{
//    qDebug()<<"PyramidViewBarItem::drawBars";

    painter->save();

    QPen pen = QPen(QColor(224, 224, 224));
    painter->setPen(pen);
    painter->setOpacity(0.75);
    for(int i=0; i<m_order.size(); ++i){
        QString curvename = m_order[i].second;
        if(curvename == m_selectedCurve)
            continue;

        pen.setColor(m_model->m_color.value(curvename));
        painter->setPen(pen);

        // 类似d3.js的瀑布式代码写法
        vector<double> v1 = m_model->m_maleData
                           .value(curvename)
                           .at(m_currentYear-m_startYear);
        vector<double> v2;
        if(m_currentYear < m_endYear){
            v2 = m_model->m_maleData
                 .value(curvename)
                 .at(m_currentYear-m_startYear+1);
        }
        else{
            v2 = m_model->m_maleData
                 .value(curvename)
                 .at(m_endYear - m_startYear);
        }

        double x = m_maleX1;
        double y = m_plotY1;
        double dy = (m_plotY2-m_plotY1) / 110;

        QPainterPath path = QPainterPath(QPointF(x, y));
        for(int j=0; j<110 && j<(int)v1.size(); ++j){
            double v = (1-m_currentT)*v1[j] + m_currentT*v2[j];
            x = v/m_labelMax * (m_maleX2-m_maleX1) + m_maleX1;
            path.lineTo(x, y);
            y += dy;
            path.lineTo(x, y);
        }
        path.lineTo(m_maleX1, y);
        path.closeSubpath();

        v1 = m_model->m_femaleData
             .value(curvename)
             .at(m_currentYear-m_startYear);
        if(m_currentYear < m_endYear){
            v2 = m_model->m_femaleData
                 .value(curvename)
                 .at(m_currentYear-m_startYear+1);
        }
        else{
            v2 = m_model->m_femaleData
                 .value(curvename)
                 .at(m_endYear-m_startYear);
        }

        x = m_femaleX1;
        y = m_plotY1;
        path.moveTo(x, y);
        for(int j=0; j<110&&j<(int)v1.size(); ++j){
            double v = (1-m_currentT)*v1[j] + m_currentT*v2[j];
            x = v/m_labelMax * (m_femaleX2-m_femaleX1) + m_femaleX1;
            path.lineTo(x, y);
            y += dy;
            path.lineTo(x, y);
        }
        path.lineTo(m_femaleX1, y);
        path.closeSubpath();

        painter->fillPath(path, m_model->m_color[curvename]);
    }

    painter->restore();
}

void PyramidViewBarItem::drawSelectedCurve(QPainter *painter, QString curve)
{
    if(!m_model->m_color.contains(curve))
        return ;

//    qDebug()<<"PyramidViewBarItem::drawSelectedCurve"<<curve;

    painter->save();

    QPen pen = QPen(QColor(224, 224, 224));
    painter->setPen(pen);
    painter->setOpacity(0.95);

    pen.setColor(m_model->m_color.value(curve));
    painter->setPen(pen);

    // 类似d3.js的瀑布式代码写法
    vector<double> v1 = m_model->m_maleData
                       .value(curve)
                       .at(m_currentYear-m_startYear);
    vector<double> v2;
    if(m_currentYear < m_endYear){
        v2 = m_model->m_maleData
             .value(curve)
             .at(m_currentYear-m_startYear+1);
    }
    else{
        v2 = m_model->m_maleData
             .value(curve)
             .at(m_endYear - m_startYear);
    }

    double x = m_maleX1;
    double y = m_plotY1;
    double dy = (m_plotY2-m_plotY1) / 110;

    QPainterPath path = QPainterPath(QPointF(x, y));
    for(int j=0; j<110 && j<(int)v1.size(); ++j){
        double v = (1-m_currentT)*v1[j] + m_currentT*v2[j];
        x = v/m_labelMax * (m_maleX2-m_maleX1) + m_maleX1;
        path.lineTo(x, y);
        y += dy;
        path.lineTo(x, y);
    }
    path.lineTo(m_maleX1, y);
    path.closeSubpath();

    v1 = m_model->m_femaleData
         .value(curve)
         .at(m_currentYear-m_startYear);
    if(m_currentYear < m_endYear){
        v2 = m_model->m_femaleData
             .value(curve)
             .at(m_currentYear-m_startYear+1);
    }
    else{
        v2 = m_model->m_femaleData
             .value(curve)
             .at(m_endYear-m_startYear);
    }

    x = m_femaleX1;
    y = m_plotY1;
    path.moveTo(x, y);
    for(int j=0; j<110&&j<(int)v1.size(); ++j){
        double v = (1-m_currentT)*v1[j] + m_currentT*v2[j];
        x = v/m_labelMax * (m_femaleX2-m_femaleX1) + m_femaleX1;
        path.lineTo(x, y);
        y += dy;
        path.lineTo(x, y);
    }
    path.lineTo(m_femaleX1, y);
    path.closeSubpath();

    painter->fillPath(path, m_model->m_color[curve]);

    painter->restore();
}

void PyramidViewBarItem::changeCurrentYear(int year)
{
    m_currentYear = year;
    m_currentT = 0.0;
}

void PyramidViewBarItem::changeCurrentT(qreal t)
{
    m_currentT = t;
}

void PyramidViewBarItem::selectCurve(QString curvename)
{
    if(m_selectedCurve != curvename){
        m_selectedCurve = curvename;
        update();
    }
}
