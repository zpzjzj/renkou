#include "pyramidstripview.h"
#include "MyUtility.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QMapIterator>
#include <QList>
#include <vector>
using namespace std;

PyramidStripView::PyramidStripView(PyramidModel *model, QObject *parent) :
    AbstractPyramidView(model, parent)
{
    m_width = 720;
    m_height = 600;

    m_maleX1 = m_width/2 - 10;
    m_maleX2 = 50;
    m_femaleX1 = m_width/2 + 10;
    m_femaleX2 = m_width - 50;
    m_plotY1 = m_height - 60;
    m_plotY2 = 60;

    m_pointRadius = 2.0;

    double d[3];
    loose_label(5, 0.0, m_model->m_maxValue, d);
    m_labelMin = d[0];
    m_labelMax = d[1];
    m_ticks = (d[1] - d[0]) / d[2];

    m_points.clear();

    m_showPoint = false;
    m_lastText = 0;
    m_verticalLine = 0;
    m_horizonLine = 0;

    m_currentTime = 0.0;

    initScene();
}

void PyramidStripView::initScene()
{
//    this->setSceneRect(0, 0, m_width, m_height);

    m_mainItem = new PyramidViewStripItem(m_model);
    this->addItem(m_mainItem);
    m_mainItem->setPos(0, 0);

    QList<QString> l = m_model->m_color.keys();
    foreach(QString curve, l){
//        QBrush brush(m_model->m_color[curve]);
//        QPen pen(m_model->m_color[curve]);
        QVector<MyEllipseItem*> ve;
        ve.clear();

        vector<double> v = m_model->m_maleData
                           .value(curve)
                           .front();
        double x, y;
        double dy = (m_plotY2-m_plotY1) / 110;
        y = m_plotY1;
        for(int j=0; j<(int)v.size(); ++j){
            MyEllipseItem *item = new MyEllipseItem(QPointF(0, 0), m_pointRadius, m_pointRadius);
            item->setColor(m_model->m_color[curve]);
            this->addItem(item);
            x = v[j]/m_labelMax * (m_maleX2-m_maleX1) + m_maleX1;
            item->setPos(x-m_pointRadius, y-m_pointRadius);
            item->setZValue(10);
            item->setData(1, m_startYear);
            item->setData(2, v[j]);
            item->setShow(m_showPoint);
            item->setZValue(this->kPointLayerLow);
            ve.append(item);
            y += dy;
        }

        v = m_model->m_femaleData
            .value(curve)
            .front();
        y = m_plotY1;
        for(int j=0; j<(int)v.size(); ++j){
            MyEllipseItem *item = new MyEllipseItem(QPointF(0, 0), m_pointRadius, m_pointRadius);
            item->setColor(m_model->m_color[curve]);
            this->addItem(item);
            x = v[j]/m_labelMax * (m_femaleX2-m_femaleX1) + m_femaleX1;
            item->setPos(x-m_pointRadius, y-m_pointRadius);
            item->setZValue(10);
            item->setData(1, m_startYear);
            item->setData(2, v[j]);
            item->setShow(m_showPoint);
            ve.append(item);
            y += dy;
        }

        m_points[curve] = ve;
    }

    m_verticalLine = this->addLine(0, m_plotY1, 0, m_plotY2, QPen(Qt::black));
    m_verticalLine->setVisible(false);
    m_horizonLine = this->addLine(m_maleX2, 0, m_femaleX2, 0, QPen(Qt::black));
    m_horizonLine->setVisible(false);
}

void PyramidStripView::showPoints(bool flag)
{
    m_showPoint = flag;
    if(flag){
        m_mainItem->setLineWidth(0.5);
    }
    else{
        m_mainItem->setLineWidth(2.0);
    }
    QMapIterator<QString, QVector<MyEllipseItem*> > it(m_points);
    while(it.hasNext()){
        it.next();
        QVector<MyEllipseItem*> v = it.value();
        for(int i=0; i<v.size(); ++i){
            v[i]->setShow(m_showPoint);
        }
    }

    update();
}

void PyramidStripView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug()<<"PyramidStripView::mouseMoveEvent"<<event->lastScenePos();

    // 处理显示数据点
    if(m_lastText != 0){
        this->removeItem(m_lastText);
        m_lastText = 0;
    }
    if(!m_verticalFlag && !m_horizonFlag && !m_crossFlag){
        auto view = dynamic_cast<QGraphicsView*>(event->widget());
        QGraphicsItem *item  = this->itemAt(event->scenePos(), view->transform());
        MyEllipseItem *i = qgraphicsitem_cast<MyEllipseItem*>(item);
        if(i != 0 && i->isShow()){
            int year = i->data(1).toInt();
            double v = i->data(2).toDouble();
            QString str;
            str.sprintf("%.0f(%d)", v, year);
            m_lastText = new MyTextItem(str);
            m_lastText->setPos(i->scenePos().x()+10, i->scenePos().y()-20);
            m_lastText->setExtraPoint(QPointF(-10, 20));
            m_lastText->setColor(i->color());
            this->addItem(m_lastText);

            // adjust position
            double px = i->scenePos().x();
            double py = i->scenePos().y();
            for(int i=1; i<=10; ++i){
                for(int dx = -1; dx<=1; ++dx){
                    for(int dy=-1; dy<=1; ++dy){
                        double nx = px + dx*i*5;
                        double ny = py + dy*i*5;
                        if(((m_maleX2<px && px<m_maleX1) || (m_femaleX1<px && px<m_femaleX2))
                           && m_plotY2<py && py<m_plotY1){
                            m_lastText->setPos(nx, ny);
                            QGraphicsItem* item = this->collidingItems(m_lastText).front();
                            if(qgraphicsitem_cast<MyEllipseItem*>(item) == 0){
                                m_lastText->setExtraPoint(QPointF(-dx*i*5, -dy*i*5));
                                goto label;
                            }
                        }
                    }
                }
            }
            label:;
        }
    }

    // 更新三条标尺的位置
    int px = m_verticalLine->x();
    int py = m_horizonLine->y();
    int nx = event->scenePos().x();
    int ny = event->scenePos().y();
    if((m_maleX2<=nx && nx<=m_maleX1)
        || (m_femaleX1<=nx && nx<=m_femaleX2)){
        px = nx;
    }
    if(m_plotY2<=ny && ny<=m_plotY1){
        py = ny;
    }

    m_horizonLine->setY(py);
    m_verticalLine->setX(px);

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

void PyramidStripView::changeCurrentYear(int year)
{
    if(year >= m_endYear){
        year = m_endYear;
        emit animationOver();
    }
    else if(year < m_startYear){
        year = m_startYear;
    }
    m_currentYear = year;
    m_mainItem->changeCurrentYear(m_currentYear);

    QList<QString> l = m_model->m_color.keys();
    foreach(QString curve, l){
        QVector<MyEllipseItem*> v = m_points.value(curve);
        vector<double> v1 = m_model->m_maleData
                            .value(curve)
                            .at(m_currentYear - m_startYear);
        int j=0;
        for(int i=0; i<(int)v1.size(); ++i,++j){
            double x = v1[i]/m_labelMax*(m_maleX2-m_maleX1) + m_maleX1;
            v[j]->setX(x-m_pointRadius);
            v[j]->setData(1, m_currentYear);
            v[j]->setData(2, v1[i]);
        }

        v1 = m_model->m_femaleData
             .value(curve)
             .at(m_currentYear - m_startYear);
        for(int i=0; i<(int)v1.size(); ++i,++j){
            double x = v1[i]/m_labelMax*(m_femaleX2-m_femaleX1) + m_femaleX1;
            v[j]->setX(x-m_pointRadius);
            v[j]->setData(1, m_currentYear);
            v[j]->setData(2, v1[i]);
        }
    }

    update();
}

void PyramidStripView::changeTime(qreal value)
{
//    qDebug()<<"PyramidStripView::changeTime";

    if(value >= 1.0)
        value = 1.0;
    else if(value <= 0.0)
        value = 0.0;

    m_currentTime = value;
    m_mainItem->changeCurrentT(value);

    QList<QString> l = m_model->m_color.keys();
    foreach(QString curve, l){
        QVector<MyEllipseItem*> v = m_points.value(curve);
        vector<double> v1 = m_model->m_maleData
                            .value(curve)
                            .at(m_currentYear - m_startYear);
        vector<double> v2 = v1;
        if(m_currentYear < m_endYear){
            v2 = m_model->m_maleData
                 .value(curve)
                 .at(m_currentYear - m_startYear + 1);
        }
        int j=0;
        for(int i=0; i<(int)v1.size(); ++i,++j){
            double vv = (1-value)*v1[i] + value*v2[i];
            double x = vv/m_labelMax*(m_maleX2-m_maleX1) + m_maleX1;
            v[j]->setX(x-m_pointRadius);
        }

        v1 = m_model->m_femaleData
             .value(curve)
             .at(m_currentYear - m_startYear);
        if(m_currentYear < m_endYear){
            v2 = m_model->m_femaleData
                 .value(curve)
                 .at(m_currentYear - m_startYear + 1);
        }
        else{
            v2 = v1;
        }

        for(int i=0; i<(int)v1.size(); ++i,++j){
            double vv = (1-value)*v1[i] + value*v2[i];
            double x = vv/m_labelMax*(m_femaleX2-m_femaleX1) + m_femaleX1;
            v[j]->setX(x-m_pointRadius);
        }
    }

    update();
}

void PyramidStripView::handleHorizonLine()
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
            if(m_maleX2<=px && px<=m_maleX1){
                dx = 10;
            }else{
                dx = -10-text->boundingRect().width();
            }
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

void PyramidStripView::handleVerticalLine()
{
    QList<QGraphicsItem*> items = this->collidingItems(m_verticalLine);
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
            if(m_maleX2<=px && px<=m_maleX1){
                dx = 10;
            }else{
                dx = -10-text->boundingRect().width();
            }
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

void PyramidStripView::handleCrossLine()
{
    QString str;
    double py = m_horizonLine->pos().y();
    double px = m_verticalLine->pos().x();
    double year = (py-m_plotY1) / (m_plotY2-m_plotY1) * 110;
    double v;
    if(m_maleX2<=px && px <=m_maleX1){
        v = (px - m_maleX1)/(m_maleX2-m_maleX1) * (m_labelMax-m_labelMin) + m_labelMin;
    }else if(m_femaleX1<=px && px<=m_femaleX2){
        v = (px - m_femaleX1)/(m_femaleX2-m_femaleX1)*(m_labelMax-m_labelMin)+m_labelMin;
    }
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
    if(m_maleX2<=px && px <=m_maleX1){
        text->setPos(px+10, py-20);
        text->setExtraPoint(QPointF(-10, 20));
    }else if(m_femaleX1<=px && px<=m_femaleX2){
        text->setPos(px-10-text->boundingRect().width(), py-20);
        text->setExtraPoint(QPointF(10+text->boundingRect().width(), 20));
    }
}

void PyramidStripView::selectCurve(QString curvename)
{
    m_mainItem->selectCurve(curvename);
    foreach(QString str, m_points.keys()){
        int z = this->kPointLayerLow;
        if(str == curvename){
            z = this->kPointLayerHigh;
        }
        for(int i=0; i<m_points[str].size(); ++i)
            m_points[str][i]->setZValue(z);
    }
}

void PyramidStripView::enableHorizonLine(bool flag)
{
    AbstractPyramidView::enableHorizonLine(flag);
    m_horizonLine->setVisible(flag);
}

void PyramidStripView::enableVerticalLine(bool flag)
{
    AbstractPyramidView::enableVerticalLine(flag);
    m_verticalLine->setVisible(flag);
}

void PyramidStripView::enableCrossLine(bool flag)
{
    AbstractPyramidView::enableCrossLine(flag);
    m_horizonLine->setVisible(flag);
    m_verticalLine->setVisible(flag);
}
