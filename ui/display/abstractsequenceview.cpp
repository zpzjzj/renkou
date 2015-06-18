#include "abstractsequenceview.h"
#include <QDebug>

AbstractSequenceView::AbstractSequenceView(SequenceModel *model, QObject *parent) :
        QGraphicsScene(parent)
{
    this->setItemIndexMethod(QGraphicsScene::BspTreeIndex);
    QGraphicsScene::setBspTreeDepth(10);
    m_model = model;
    m_startYear = model->m_startYear;
    m_endYear = model->m_endYear;
    m_currentYear = m_startYear;

    m_horizonFlag = false;
    m_verticalFlag = false;
    m_crossFlag = false;
}

int AbstractSequenceView::currentYear() const
{
    return m_currentYear;
}

void AbstractSequenceView::showPoints(bool flag)
{
    Q_UNUSED(flag)
}

void AbstractSequenceView::enableHorizonLine(bool flag)
{
//    qDebug()<<"AbstractSequenceView::enableHorizonLine"<<flag;
    m_horizonFlag = flag;
}

void AbstractSequenceView::enableVerticalLine(bool flag)
{
//    qDebug()<<"AbstractSequenceView::enableVerticalLine"<<flag;
    m_verticalFlag = flag;
}

void AbstractSequenceView::enableCrossLine(bool flag)
{
//    qDebug()<<"AbstractSequenceView::enableCrossLine"<<flag;
    m_crossFlag = flag;
}
