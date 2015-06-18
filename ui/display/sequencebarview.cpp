#include "sequencebarview.h"

SequenceBarView::SequenceBarView(SequenceModel *model, QObject *parent) :
    AbstractSequenceView(model, parent)
{
    m_showPoints = false;

    initScene();
}

void SequenceBarView::initScene()
{
    m_mainItem = new SequenceBarViewItem(m_model);
    this->addItem(m_mainItem);
}

void SequenceBarView::changeCurrentYear(int year)
{
    if(year >= m_endYear){
        year = m_endYear;
    }
    else if(year <= m_startYear){
        year = m_startYear;
    }
    m_currentYear = year;
    m_mainItem->changeCurrentYear(year);
    update();

    emit yearChanged(m_currentYear);
    if(m_currentYear ==  m_endYear)
        emit animationOver();
}

void SequenceBarView::changeTime(qreal value)
{
    if(value >= 1.0)
        value = 1.0;
    else if(value <= 0.0)
        value = 0.0;
    m_mainItem->changeCurrentT(value);
    update();
}

void SequenceBarView::selectCurve(QString curve)
{
    m_mainItem->selectCurve(curve);
}

void SequenceBarView::showPoints(bool flag)
{
    m_showPoints = flag;
}
