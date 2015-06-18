#include "sequencebarview3d.h"

SequenceBarView3D::SequenceBarView3D(SequenceModel *model, QObject *parent) :
    AbstractSequenceView(model, parent)
{
    initScene();
}

void SequenceBarView3D::showPoints(bool flag)
{
    Q_UNUSED(flag);
}

void SequenceBarView3D::initScene()
{
    m_mainItem = new SequenceBarView3DItem(m_model);
    this->addItem(m_mainItem);
}

void SequenceBarView3D::changeCurrentYear(int year)
{
    if(year == m_currentYear)
        return ;

    if(year >= m_endYear){
        m_currentYear = m_endYear;
        emit yearChanged(m_currentYear);
        emit animationOver();
    }
    else{
        if(year < m_startYear){
            year = m_startYear;
        }
        m_currentYear = year;
        emit yearChanged(m_currentYear);
    }
    m_mainItem->changeCurrentYear(year);
    update();
}

void SequenceBarView3D::changeTime(qreal value)
{
    if(value <= 0.0)
        value = 0.0;
    else if(value >= 1.0)
        value = 1.0;
    m_mainItem->changeCurrentT(value);
    update();
}

void SequenceBarView3D::selectCurve(QString curve)
{
    m_mainItem->selectCurve(curve);
}
