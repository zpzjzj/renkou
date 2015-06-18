#include "sequencebarview3ditem.h"
#include "Constants.h"
#include "MyUtility.h"
#include <QMapIterator>
#include <QPainter>
#include <QList>
#include <QDebug>
#include <vector>
#include <cassert>
#include <cmath>
using namespace std;

SequenceBarView3DItem::SequenceBarView3DItem(SequenceModel *model, QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    m_model = model;
    m_startYear = model->m_startYear;
    m_endYear = model->m_endYear;
    m_currentYear = m_startYear;
    m_currentT = 0.0;

    m_width = 720;
    m_height = 600;

    m_order.clear();
    QMapIterator<QString, DataBlock> it(m_model->m_datas);
    while(it.hasNext()){
        it.next();
        vector<double> v = it.value().m_averageValue;
        double sum = 0;
        for(int i=0; i<(int)v.size(); ++i){
            sum += v[i];
        }
        m_order.append(qMakePair(-sum, it.key()));
    }
    qSort(m_order.begin(), m_order.end());
    m_selectedCurve = m_order.last().second;

    double d[3];
    loose_label(10, m_model->m_minValue, m_model->m_maxValue, d);
    m_labelMin = d[0];
    m_labelMax = d[1];
    m_ticks = (d[1] - d[0]) / d[2];

    m_plotX1 = 50;
    m_plotY1 = m_height-60;
    m_xLen = 550;
    m_yLen = 400;
    m_zLen = 100;
    m_margin = 20;

    m_xBase = QPointF(1, 0);
    m_yBase = QPointF(0, 1);
    m_zBase = QPointF(cos(Pi/4), -sin(Pi/4));
    m_leftDownPoint = QPointF(m_plotX1, m_plotY1);
    if(m_labelMin >= 0.0)
        m_zeroPoint = m_leftDownPoint;
    else
        m_zeroPoint = m_leftDownPoint - (0-m_labelMin)/(m_labelMax-m_labelMin)*m_yLen*m_yBase;

    this->setFlag(ItemSendsGeometryChanges);
    this->setZValue(0);
}

QRectF SequenceBarView3DItem::boundingRect() const
{
    return QRectF(0, 0, m_width, m_height);
}

void SequenceBarView3DItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    drawBackground(painter);

    draw3DBars(painter);

    drawSelectedBar(painter ,m_selectedCurve);

    drawYearLabel(painter);

    drawVolumeLabel(painter);
}

void SequenceBarView3DItem::drawBackground(QPainter *painter)
{
    painter->fillRect(boundingRect(), BGCOLOR);
}

void SequenceBarView3DItem::drawYearLabel(QPainter *painter)
{
    painter->save();

    QPen pen(DASHCOLOR);
    painter->setPen(pen);

    painter->drawLine(m_zeroPoint, m_zeroPoint+m_xLen*m_xBase);

    double dx = m_xLen / (m_endYear-m_startYear);
    double x = 0;
    for(int i=m_startYear; i<=m_endYear; ++i){
        if(i % 10 == 0){
            QPointF p1 = m_zeroPoint + x*m_xBase;
            QPointF p2 = p1 + m_zLen*m_zBase;
            painter->drawLine(p1, p2);
            painter->drawText(QRectF(p1.x()-20, p1.y(), 40, 20),
                              Qt::AlignCenter,
                              QString::number(i));
        }
        x += dx;
    }

    painter->drawText(QRectF(m_zeroPoint+m_xLen*m_xBase+QPointF(20,0), QSizeF(40, 20)),
                      Qt::AlignCenter,
                      tr("年份"));

    painter->restore();
}

void SequenceBarView3DItem::drawVolumeLabel(QPainter *painter)
{
    painter->save();

    QPen pen(DASHCOLOR);
    painter->setPen(pen);

    painter->drawLine(m_leftDownPoint, m_leftDownPoint-m_yLen*m_yBase);

    QPointF zVector = m_zLen * m_zBase;
    double dy = m_yLen / m_ticks;
    double y = 0.0;
    double dv = (m_labelMax-m_labelMin) / m_ticks;
    QString label;
    char format[32];
    if(int(dv) == dv){
        strcpy(format, "%.0f");
    }
    else{
        strcpy(format, "%3f");
    }

    for(int i=0; i<=m_ticks; ++i){
        QPointF p1 = m_leftDownPoint + y * m_yBase;
        QPointF p2 = p1 + zVector;
        painter->drawLine(p1, p2);
        painter->drawLine(p1, p1 + QPointF(-4, 0));
        painter->drawLine(p2, p2 + m_xLen*m_xBase);
        double v = i * dv + m_labelMin;
        painter->drawText(QRectF(p1.x()-50, p1.y()-10, 40, 20),
                          Qt::AlignRight | Qt::AlignVCenter,
                          label.sprintf(format, v));
        y -= dy;
    }
    painter->drawText(QRectF(m_leftDownPoint-m_yLen*m_yBase-QPointF(30, 60), QSizeF(60, 20)),
                      Qt::AlignHCenter | Qt::AlignTop ,
                      tr("单位：未知"));

    painter->restore();
}

void SequenceBarView3DItem::draw3DBars(QPainter *painter)
{
    painter->save();

    QPointF dx = m_xLen / (m_endYear - m_startYear) * m_xBase;
    QPointF dy = m_yLen / (m_labelMax - m_labelMin) * m_yBase;
    QPointF dz = m_zLen / m_order.size() * m_zBase;
    QPointF z = m_zLen * m_zBase - dz;
    for(int i=0; i<m_order.size(); ++i){
        QString curvename = m_order[i].second;
        if(curvename == m_selectedCurve)
            continue;

        QBrush brush(m_model->m_datas[curvename].m_color);
        painter->setPen(GRAY);
        painter->setOpacity(0.75);

        QVector<QPointF> points;
        QPointF basepoint(m_zeroPoint + z);
        QPointF p;
        QPointF offset = 0.6 * dz;
        vector<double> data = m_model->m_datas[curvename].m_data;

        points.clear();
        points.append(basepoint);
        for(int j=0; j<m_currentYear-m_startYear; ++j){
            p = basepoint - data[j]*dy + j*dx;
            points.append(p);
            points.append(p + dx);
        }
        // 计算当前时间的位置的点
        p = basepoint - data[m_currentYear-m_startYear] * dy
            + (m_currentYear-m_startYear) * dx;
        points.append(p);
        points.append(p + m_currentT * dx);
        p = basepoint + (m_currentYear-m_startYear+m_currentT) * dx;
        points.append(p);

        // 画正面
        QPainterPath frontface(points[0]);
        for(int j=0; j<points.size(); ++j){
            frontface.lineTo(points[j]);
        }
        frontface.closeSubpath();
        painter->drawPath(frontface);
        painter->fillPath(frontface, brush);

        // 画背面
        QPainterPath backface(points[0]+offset);
        for(int j=0; j<points.size(); ++j){
            backface.lineTo(points[j] + offset);
        }
        backface.closeSubpath();
        painter->drawPath(backface);
        painter->fillPath(backface, brush);

        // 画其他面
        QPainterPath otherface;
        otherface.setFillRule(Qt::WindingFill);
        for(int j=0; j<points.size()-1; ++j){
            otherface.moveTo(points[j]);
            otherface.lineTo(points[j]+offset);
            otherface.lineTo(points[j+1]+offset);
            otherface.lineTo(points[j+1]);
            otherface.closeSubpath();
        }
        otherface.moveTo(points.first());
        otherface.lineTo(points.first()+offset);
        otherface.lineTo(points.last()+offset);
        otherface.lineTo(points.last());
        otherface.closeSubpath();
        painter->drawPath(otherface);
        painter->fillPath(otherface, brush);

        z -= dz;
    }

    painter->restore();
}

void SequenceBarView3DItem::drawSelectedBar(QPainter *painter, QString curvename)
{
    if(!m_model->m_datas.contains(curvename))
        return ;
    painter->save();

    QPointF dx = m_xLen / (m_endYear - m_startYear) * m_xBase;
    QPointF dy = m_yLen / (m_labelMax - m_labelMin) * m_yBase;
    QPointF dz = m_zLen / m_order.size() * m_zBase;
    QPointF z = QPointF(0, 0);

    QBrush brush(m_model->m_datas[curvename].m_color);
    painter->setPen(GRAY);
    painter->setOpacity(0.75);

    QVector<QPointF> points;
    QPointF basepoint(m_zeroPoint + z);
    QPointF p;
    QPointF offset = 0.6 * dz;
    vector<double> data = m_model->m_datas[curvename].m_data;

    points.clear();
    points.append(basepoint);
    for(int j=0; j<m_currentYear-m_startYear; ++j){
        p = basepoint - data[j]*dy + j*dx;
        points.append(p);
        points.append(p + dx);
    }
    // 计算当前时间的位置的点
    p = basepoint - data[m_currentYear-m_startYear] * dy
        + (m_currentYear-m_startYear) * dx;
    points.append(p);
    points.append(p + m_currentT * dx);
    p = basepoint + (m_currentYear-m_startYear+m_currentT) * dx;
    points.append(p);

    // 画正面
    QPainterPath frontface(points[0]);
    for(int j=0; j<points.size(); ++j){
        frontface.lineTo(points[j]);
    }
    frontface.closeSubpath();
    painter->drawPath(frontface);
    painter->fillPath(frontface, brush);

    // 画背面
    QPainterPath backface(points[0]+offset);
    for(int j=0; j<points.size(); ++j){
        backface.lineTo(points[j] + offset);
    }
    backface.closeSubpath();
    painter->drawPath(backface);
    painter->fillPath(backface, brush);

    // 画其他面
    QPainterPath otherface;
    for(int j=0; j<points.size()-1; ++j){
        otherface.moveTo(points[j]);
        otherface.lineTo(points[j]+offset);
        otherface.lineTo(points[j+1]+offset);
        otherface.lineTo(points[j+1]);
        otherface.closeSubpath();
    }
    otherface.moveTo(points.first());
    otherface.lineTo(points.first()+offset);
    otherface.lineTo(points.last()+offset);
    otherface.lineTo(points.last());
    otherface.closeSubpath();
    painter->drawPath(otherface);
    otherface.setFillRule(Qt::WindingFill);
    painter->fillPath(otherface, brush);

//    qDebug()<<"SequenceBarView3DItem::drawSelectedBar"<<points<<otherface;

    painter->restore();
}

void SequenceBarView3DItem::changeCurrentYear(int year)
{
    assert(m_startYear<=year && year<=m_endYear);
    m_currentYear = year;
    m_currentT = 0.0;
}

void SequenceBarView3DItem::changeCurrentT(qreal t)
{
    assert(0.0<=t && t<=1.0);
    m_currentT = t;
}

void SequenceBarView3DItem::selectCurve(QString curvename)
{
    if(m_selectedCurve != curvename){
        m_selectedCurve = curvename;
        update();
    }
}
