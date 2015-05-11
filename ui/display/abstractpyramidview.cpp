#include "abstractpyramidview.h"

AbstractPyramidView::AbstractPyramidView(PyramidModel *model, QObject *parent) :
    QGraphicsScene(parent)
{
    this->setItemIndexMethod(QGraphicsScene::BspTreeIndex);
    m_model = model;
    m_startYear = model->m_startYear;
    m_endYear = model->m_endYear;
    m_currentYear = m_startYear;

    m_horizonFlag = false;
    m_verticalFlag = false;
    m_crossFlag = false;
}

int AbstractPyramidView::currentYear() const
{
    return m_currentYear;
}

void AbstractPyramidView::showPoints(bool flag)
{
    Q_UNUSED(flag)
}

void AbstractPyramidView::enableHorizonLine(bool flag)
{
    m_horizonFlag = flag;
}

void AbstractPyramidView::enableVerticalLine(bool flag)
{
    m_verticalFlag = flag;
}

void AbstractPyramidView::enableCrossLine(bool flag)
{
    m_crossFlag = flag;
}
