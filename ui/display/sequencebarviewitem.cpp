#include "Constants.h"
#include "MyUtility.h"
#include "sequencebarviewitem.h"
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QTextCodec>
#include <QMapIterator>
#include <cmath>
#include <vector>
using namespace std;

SequenceBarViewItem::SequenceBarViewItem(SequenceModel *model, QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    m_model = model;
    m_startYear = model->m_startYear;
    m_endYear = model->m_endYear;
    m_currentYear = m_startYear;
    m_currentT = 0;

    m_width = 720;
    m_height = 600;
    m_plotX1 = 50;
    m_plotX2 = m_width - 50;
    m_plotY1 = m_height - 60;
    m_plotY2 = 60;

    double d[3];
    loose_label(10, model->m_minValue, model->m_maxValue, d);
    m_labelMin = d[0];
    m_labelMax = d[1];
    m_ticks = (d[1]-d[0]) / d[2];

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

    this->setFlag(ItemSendsGeometryChanges);
    this->setZValue(0);
}

QRectF SequenceBarViewItem::boundingRect() const
{
    return QRectF(0, 0, m_width, m_height);
}

void SequenceBarViewItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    drawBackground(painter);

    drawCurves(painter);

    drawSelectedCurve(painter, m_selectedCurve);

    drawYearLabel(painter);

    drawVolumeLabel(painter);
}

void SequenceBarViewItem::drawBackground(QPainter *painter)
{
    painter->save();

    painter->fillRect(QRectF(0, 0, m_width, m_height), BGCOLOR);
    painter->fillRect(QRectF(m_plotX1, m_plotY2, m_plotX2-m_plotX1, m_plotY1-m_plotY2), Qt::white);

    painter->restore();
}

void SequenceBarViewItem::drawYearLabel(QPainter *painter)
{
//    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    painter->save();

    QPen pen(Qt::black);
    pen.setWidth(1);
    painter->setPen(pen);

    double dx = (m_plotX2-m_plotX1) / (m_endYear-m_startYear);
    double x = m_plotX1;
    for(int i=m_startYear; i<=m_endYear; ++i){
        if(i % 10 == 0){
            painter->drawText(QRectF(x-20, m_plotY1, 40, 20),
                              Qt::AlignVCenter | Qt::AlignHCenter,
                              QString::number(i));
        }
        x += dx;
    }

    painter->drawText(QRectF(m_plotX2+20, m_plotY1, 40, 20),
                      Qt::AlignLeft | Qt::AlignVCenter,
                      tr("年份"));
    pen.setColor(QColor(224, 224, 224));    // BGCOLOR
    painter->setPen(pen);
    x = m_plotX1;
    for(int i=m_startYear; i<=m_endYear; ++i){
        if(i % 10 == 0){
            painter->drawLine(QPointF(x, m_plotY1), QPointF(x, m_plotY2));
        }
        x += dx;
    }

    painter->restore();
}

void SequenceBarViewItem::drawVolumeLabel(QPainter *painter)
{
//    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    painter->save();

    QPen pen(DASHCOLOR);
    pen.setWidth(1);
    painter->setPen(pen);

    double dy = (m_plotY2-m_plotY1) / m_ticks;
    double y = m_plotY1;
    double dv = (m_labelMax - m_labelMin) / m_ticks;
    char format[32];
    if((int)dv == dv){
        strcpy(format, "%.0f");
    }
    else{
        strcpy(format, "%3f");
    }
    for(int i=0; i<=m_ticks; ++i){
        double v = m_labelMin + i*dv;
        QString str;
        painter->drawText(QRectF(m_plotX1-50, y-10, 40, 20),
                          Qt::AlignRight | Qt::AlignVCenter,
                          str.sprintf(format, v));
        if(fabs(v) < 0.00001)
            painter->drawLine(QPointF(m_plotX1-4, y), QPointF(m_plotX2, y));
        else
            painter->drawLine(QPointF(m_plotX1-4, y), QPointF(m_plotX1, y));

        y += dy;
    }

    painter->drawText(QRectF(m_plotX1-30, m_plotY2-40, 60, 20),
                      Qt::AlignCenter,
                      tr("单位：未知"));

    painter->restore();
}

void SequenceBarViewItem::drawCurves(QPainter *painter)
{
    painter->save();

    QPen pen(GRAY);
    painter->setPen(pen);

    for(int i=0; i<m_order.size(); ++i){
        QString curvename = m_order[i].second;
        if(curvename == m_selectedCurve)
            continue;

        vector<double> v = m_model->m_datas[curvename].m_data;
        double dx = (m_plotX2-m_plotX1) / (m_endYear-m_startYear);
        double x = m_plotX1;
        double dy = (m_plotY2 - m_plotY1) / (m_labelMax - m_labelMin);
        double y = (0 - m_labelMin) * dy + m_plotY1;
        QPainterPath path;
        path.moveTo(x, y);
        int j;
        for(j=0; j<=m_currentYear-m_startYear; ++j){
            y = (v[j]-m_labelMin) * dy + m_plotY1;
            x = j*dx + m_plotX1;
            path.lineTo(x, y);
        }
        if(m_currentYear < m_endYear){
            y = (v[j-1]*(1-m_currentT) + v[j]*m_currentT - m_labelMin) * dy + m_plotY1;
            x = (j-1+m_currentT) * dx + m_plotX1;
            path.lineTo(x, y);
        }
        y = (0 - m_labelMin) * dy + m_plotY1;
        path.lineTo(x, y);
        path.lineTo(m_plotX1, y);

        painter->drawPath(path);
        painter->fillPath(path, m_model->m_datas[curvename].m_color);
    }

    painter->restore();
}

void SequenceBarViewItem::drawSelectedCurve(QPainter *painter, QString curvename)
{
    if(!m_model->m_datas.contains(curvename))
        return ;

    painter->save();

    vector<double> v = m_model->m_datas[curvename].m_data;
    double dx = (m_plotX2-m_plotX1) / (m_endYear-m_startYear);
    double x = m_plotX1;
    double dy = (m_plotY2 - m_plotY1) / (m_labelMax - m_labelMin);
    double y = (0 - m_labelMin) * dy + m_plotY1;
    QPainterPath path;
    path.moveTo(x, y);
    int j;
    for(j=0; j<=m_currentYear-m_startYear; ++j){
        y = (v[j]-m_labelMin) * dy + m_plotY1;
        x = j*dx + m_plotX1;
        path.lineTo(x, y);
    }
    if(m_currentYear < m_endYear){
        y = (v[j-1]*(1-m_currentT) + v[j]*m_currentT - m_labelMin) * dy + m_plotY1;
        x = (j-1+m_currentT) * dx + m_plotX1;
        path.lineTo(x, y);
    }
    y = (0 - m_labelMin) * dy + m_plotY1;
    path.lineTo(x, y);
    path.lineTo(m_plotX1, y);

    painter->drawPath(path);
    painter->fillPath(path, m_model->m_datas[curvename].m_color);

    painter->restore();
}

void SequenceBarViewItem::changeCurrentYear(int year)
{
    m_currentYear = year;
    m_currentT = 0.0;
}

void SequenceBarViewItem::changeCurrentT(qreal t)
{
    m_currentT = t;
}

void SequenceBarViewItem::selectCurve(QString curve)
{
    m_selectedCurve = curve;
    update();
}
