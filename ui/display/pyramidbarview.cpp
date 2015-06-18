#include "pyramidbarview.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

PyramidBarView::PyramidBarView(PyramidModel *model, QObject *parent):
        AbstractPyramidView(model, parent)
{
    initScene();
}

void PyramidBarView::initScene()
{
    m_mainItem = new PyramidViewBarItem(m_model);
    this->addItem(m_mainItem);
}

void PyramidBarView::showPoints(bool flag)
{
    m_showPoint = flag;
}

void PyramidBarView::mouseMoveEvent(QGraphicsSceneMouseEvent *)
{
//    qDebug()<<event->pos();
}

void PyramidBarView::changeCurrentYear(int year)
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
    update();
}

void PyramidBarView::changeTime(qreal value)
{
    if(value >= 1.0)
        value = 1.0;
    else if(value <= 0.0)
        value = 0.0;
    m_mainItem->changeCurrentT(value);
    update();
}

void PyramidBarView::selectCurve(QString curvename)
{
    m_mainItem->selectCurve(curvename);
}
