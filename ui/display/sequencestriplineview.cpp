#include "sequencestriplineview.h"
#include "MyUtility.h"
#include "Constants.h"
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QMapIterator>
#include <QBrush>
#include <QPen>
#include <QRectF>
#include <QFont>
#include <QColor>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QDebug>
#include <cstring>
#include <vector>
using namespace std;

SequenceStripLineView::SequenceStripLineView(SequenceModel *model, QObject *parent) :
        AbstractSequenceView(model, parent)
{
    m_width = 720;
    m_height = 600;
    m_plotX1 = 50;
    m_plotX2 = m_width - m_plotX1;
    m_plotY2 = 60;
    m_plotY1 = m_height - m_plotY2;

    double d[3];
    loose_label(10, model->m_minValue, model->m_maxValue, d);
    m_labelMin = d[0];
    m_labelMax = d[1];
    m_ticks = (d[1]-d[0]) / d[2];

    m_pointRadius = 2.5;
    m_showPoints = false;

    m_textItem = 0;
    m_verticalLine = 0;
    m_horizonLine = 0;

    this->setSceneRect(0, 0, m_width, m_height);
    initScene();
}

void SequenceStripLineView::initScene()
{
    m_mainItem = new SequenceStripViewItem(m_model);
    m_mainItem->setZValue(0);
    this->addItem(m_mainItem);
    m_mainItem->setLineWidth(2.0);

    m_points.clear();
    QMapIterator<QString, DataBlock> it(m_model->m_datas);
    while(it.hasNext()){
        it.next();

//        QPen pen(it.value().m_color);
//        QBrush brush(it.value().m_color);

        vector<double> v = it.value().m_data;
        QVector<MyEllipseItem*> ve;

        double dx = (m_plotX2-m_plotX1) / (m_endYear-m_startYear);
        double dy = (m_plotY2-m_plotY1) / (m_labelMax-m_labelMin);
        for(int i=0; i<(int)v.size(); ++i){
            double x = m_plotX1 + i*dx;
            double y = m_plotY1 + (v[i]-m_labelMin)*dy;
            MyEllipseItem* item = new MyEllipseItem(QPointF(0,0), m_pointRadius, m_pointRadius);
            item->setColor(it.value().m_color);
            this->addItem(item);
            item->setPos(x-m_pointRadius, y-m_pointRadius);
            item->setShow(m_showPoints);
            item->setData(1, i+m_startYear);
            item->setData(2, v[i]);
            item->setZValue(10);
            ve.append(item);
        }
        m_points[it.key()] = ve;
    }

    m_verticalLine = this->addLine(0, m_plotY1, 0, m_plotY2, QPen(Qt::black));
    m_verticalLine->setVisible(false);
    m_horizonLine = this->addLine(m_plotX1, 0, m_plotX2, 0, QPen(Qt::black));
    m_horizonLine->setVisible(false);
}

void SequenceStripLineView::changeCurrentYear(int year)
{
//    qDebug()<<"SequenceStripLineView::changeCurrentYear"<<year;
    if(year >= m_endYear){
        year = m_endYear;
        emit animationOver();
    }
    m_currentYear = year;
    emit yearChanged(m_currentYear);

    m_mainItem->changeCurrentYear(m_currentYear);

    foreach(QString str, m_points.keys()){
        QVector<MyEllipseItem*> v = m_points.value(str);
        int i;
        for(i=0; i<=m_currentYear-m_startYear; ++i){
            v[i]->setShow(m_showPoints);
        }
        for(; i<=m_endYear-m_startYear; ++i){
            v[i]->setShow(false);
        }
    }

    update();
}

void SequenceStripLineView::changeTime(qreal value)
{
    if(value <= 0.0)
        value = 0.0;
    if(value >= 1.0)
        value = 1.0;
    m_mainItem->changeCurrentT(value);
    update();
}

void SequenceStripLineView::showPoints(bool flag)
{
    if(flag != m_showPoints){
        m_showPoints = flag;
        if(m_showPoints){
            m_mainItem->setLineWidth(0.5);
        }
        else{
            m_mainItem->setLineWidth(2.0);
        }

        foreach(QString str, m_points.keys()){
            QVector<MyEllipseItem*> v = m_points.value(str);
            int i;
            for(int i=0; i<=m_currentYear-m_startYear; ++i){
                v[i]->setShow(m_showPoints);
            }
            for(; i<=m_endYear-m_startYear; ++i){
                v[i]->setShow(false);
            }
        }

        update();
    }
}

void SequenceStripLineView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug()<<"SequenceStripLineView::mouseMoveEvent";

    if(m_textItem != 0){
        this->removeItem(m_textItem);
        m_textItem = 0;
    }
    if(!m_horizonFlag && !m_verticalFlag && !m_crossFlag){
        auto view = dynamic_cast<QGraphicsView*>(event->widget());
        QGraphicsItem *item  = this->itemAt(event->scenePos(), view->transform());
        MyEllipseItem *ei = qgraphicsitem_cast<MyEllipseItem*>(item);
        if(ei != 0 && ei->isShow()){
            QString str;
            int year = ei->data(1).toInt();
            double v = ei->data(2).toDouble();
            if(v >= 1000000)
                str.sprintf("%.0f(%d)", v, year);
            else if(v >= 1000)
                str.sprintf("%.2f(%d)", v, year);
            else
                str.sprintf("%.3f(%d)", v, year);
            m_textItem = new MyTextItem(str);
            m_textItem->setPos(ei->scenePos().x()+10, ei->scenePos().y()-20);
            m_textItem->setExtraPoint(QPointF(-10, 20));
            m_textItem->setColor(ei->color());
            this->addItem(m_textItem);

            // adjust position
            double px = ei->scenePos().x();
            double py = ei->scenePos().y();
            for(int i=1; i<=10; ++i){
                for(int dx = -1; dx<=1; ++dx){
                    for(int dy=-1; dy<=1; ++dy){
                        double nx = px + dx*i*5;
                        double ny = py + dy*i*5;
                        if(m_plotX1<px && px<m_plotX2 && m_plotY2<py && py<m_plotY1){
                            m_textItem->setPos(nx, ny);
                            QGraphicsItem* item = this->collidingItems(m_textItem).front();
                            if(qgraphicsitem_cast<MyEllipseItem*>(item) == 0){
                                m_textItem->setExtraPoint(QPointF(-dx*i*5, -dy*i*5));
                                goto label;
                            }
                        }
                    }
                }
            }
            label:;
        }
    }

    // handle with ruler lines
    qreal nx = event->scenePos().x();
    qreal ny = event->scenePos().y();
    if(nx <= m_plotX1)  // m_plotX1 = 50
        nx = m_plotX1;
    else if(nx >= m_plotX2)
        nx = m_plotX2;
    if(ny <= m_plotY2)  // m_plotY2 = 60
        ny = m_plotY2;
    else if(ny >= m_plotY1)
        ny = m_plotY1;

    m_horizonLine->setY(ny);
    m_verticalLine->setX(nx);

    foreach(MyTextItem *i, m_texts){
        this->removeItem(i);
    }
    m_texts.clear();

    if(this->m_horizonFlag)
        handleHorizonLine();
    else if(this->m_verticalFlag)
        handleVerticalLine();
    else if(this->m_crossFlag)
        handleCrossLine();

    update();
}

void SequenceStripLineView::handleHorizonLine()
{
    QList<QGraphicsItem*> items = this->collidingItems(m_horizonLine);
    foreach(QGraphicsItem* i, items){
        MyEllipseItem* item = qgraphicsitem_cast<MyEllipseItem*>(i);
        if(item != 0){
            int year = item->data(1).toInt();
            double v = item->data(2).toDouble();
            item->showOnce();
            QString str;
            if(v > 1000000)
                str.sprintf("%6.0f(%d)", v, year);
            else if(v > 1000)
                str.sprintf("%6.2f(%d)", v, year);
            else
                str.sprintf("%6.3f(%d)", v, year);

            MyTextItem *text = new MyTextItem(str);
            text->setColor(item->color());
            this->addItem(text);
            text->setZValue(this->kTextLayer);
            m_texts.append(text);

            double px = item->pos().x();
            double py = item->pos().y();
            double dx = 10.0;
            if(px >= m_width / 2)
                dx = -10-text->boundingRect().width();
            text->setPos(px, py);
            double h = text->boundingRect().height()+1;
            for(int i=0; i<=20; ++i){
                text->setPos(px+dx, py+i*h);
                if(py+i*h < m_plotY1){
                    QGraphicsItem* item = this->collidingItems(text).first();
                    if(qgraphicsitem_cast<MyTextItem*>(item) == 0){
                        text->setExtraPoint(QPointF(-dx, -i*h));
                        break;
                    }
                }

                text->setPos(px+dx, py - i*h);
                if(py-i*h > m_plotY2){
                    QGraphicsItem* item = this->collidingItems(text).first();
                    if(qgraphicsitem_cast<MyTextItem*>(item) == 0){
                        text->setExtraPoint(QPointF(-dx, i*h));
                        break;
                    }
                }
            }
        }
    }
}

void SequenceStripLineView::handleVerticalLine()
{
    QList<QGraphicsItem*> items = this->collidingItems(m_verticalLine);
    foreach(QGraphicsItem* i, items){
        MyEllipseItem* item = qgraphicsitem_cast<MyEllipseItem*>(i);
        if(item != 0){
            int year = item->data(1).toInt();
            double v = item->data(2).toDouble();
            if(year > m_currentYear)
                continue;
            item->showOnce();
            QString str;
            if(v > 1000000)
                str.sprintf("%6.0f(%d)", v, year);
            else if(v > 1000)
                str.sprintf("%6.2f(%d)", v, year);
            else
                str.sprintf("%6.3f(%d)", v, year);

            MyTextItem *text = new MyTextItem(str);
            text->setColor(item->color());
            this->addItem(text);
            text->setZValue(this->kTextLayer);
            m_texts.append(text);

            double px = item->pos().x();
            double py = item->pos().y();
            double dx = 10.0;
            if(px >= m_width / 2)
                dx = -10-text->boundingRect().width();
            text->setPos(px, py);
            double h = text->boundingRect().height()+1;
            for(int i=0; i<=10; ++i){
                text->setPos(px+dx, py+i*h);
                if(py+i*h < m_plotY1){
                    QGraphicsItem* item = this->collidingItems(text).first();
                    if(qgraphicsitem_cast<MyTextItem*>(item) == 0){
                        text->setExtraPoint(QPointF(-dx, -i*h));
                        break;
                    }
                }

                text->setPos(px+dx, py - i*h);
                if(py-i*h > m_plotY2){
                    QGraphicsItem* item = this->collidingItems(text).first();
                    if(qgraphicsitem_cast<MyTextItem*>(item) == 0){
                        text->setExtraPoint(QPointF(-dx, i*h));
                        break;
                    }
                }
            }
        }
    }
}

void SequenceStripLineView::handleCrossLine()
{
    QString str;
    double py = m_horizonLine->pos().y();
    double px = m_verticalLine->pos().x();
    double year = (px-m_plotX1) / (m_plotX2-m_plotX1) * (m_endYear-m_startYear);
    double v = (py-m_plotY1) / (m_plotY2-m_plotY1) * (m_labelMax-m_labelMin) + m_labelMin;
    if(v >= 1000000)
        str.sprintf("%6.0f(%.2f)", v, year);
    else if(v >= 1000)
        str.sprintf("%6.2f(%.2f)", v, year);
    else
        str.sprintf("%6.3f(%.2f)", v, year);

    MyTextItem *text = new MyTextItem(str);
    this->addItem(text);
    text->setZValue(this->kTextLayer);
    m_texts.append(text);
    if(px <= m_width / 2){
        text->setPos(px+10, py-20);
        text->setExtraPoint(QPointF(-10, 20));
    }else{
        text->setPos(px-10-text->boundingRect().width(), py-20);
        text->setExtraPoint(QPointF(10+text->boundingRect().width(), 20));
    }
}

void SequenceStripLineView::selectCurve(QString curve)
{
    m_mainItem->selectCurve(curve);
    foreach(QString str, m_points.keys()){
        int z = this->kPointLayerLow;
        if(str == curve){
            z = this->kPointLayerHigh;
        }
        for(int i=0; i<m_points[str].size(); ++i)
            m_points[str][i]->setZValue(z);
    }
}

void SequenceStripLineView::enableHorizonLine(bool flag)
{
    AbstractSequenceView::enableHorizonLine(flag);
    m_horizonLine->setVisible(flag);
}

void SequenceStripLineView::enableVerticalLine(bool flag)
{
    AbstractSequenceView::enableVerticalLine(flag);
    m_verticalLine->setVisible(flag);
}

void SequenceStripLineView::enableCrossLine(bool flag)
{
    AbstractSequenceView::enableCrossLine(flag);
    m_horizonLine->setVisible(flag);
    m_verticalLine->setVisible(flag);
}
