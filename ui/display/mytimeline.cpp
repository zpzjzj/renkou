#include "mytimeline.h"

MyTimeLine::MyTimeLine(QObject *parent) :
    QObject(parent)
{
    m_timeLine = new QTimeLine;
    connect(m_timeLine, SIGNAL(finished()), this, SLOT(updateTimeLine()));
    connect(m_timeLine, SIGNAL(valueChanged(qreal)), this, SIGNAL(timeChanged(qreal)));
}

MyTimeLine::~MyTimeLine()
{
    delete m_timeLine;
}

void MyTimeLine::setFrameRange(int sf, int ef)
{
    m_sFrame = sf;
    m_eFrame = ef;
}

void MyTimeLine::setInterval(int t)
{
    m_interval = t;
}

void MyTimeLine::start()
{
    m_cFrame = m_sFrame;
    m_timeLine->setFrameRange(0, 1);
    m_timeLine->setDuration(m_interval);
    m_timeLine->start();
}

void MyTimeLine::stop()
{
    m_timeLine->stop();
}

void MyTimeLine::pause()
{
    m_timeLine->setPaused(true);
}

void MyTimeLine::resume()
{
    m_timeLine->resume();
}

void MyTimeLine::updateTimeLine()
{
    m_cFrame++;
    emit frameChanged(m_cFrame);
    if(m_cFrame==m_eFrame){
        emit finished();
    }
    else{
        m_timeLine->start();
    }
}

int MyTimeLine::getFrame() const
{
    return m_cFrame;
}

void MyTimeLine::setFrame(int f)
{
    QTimeLine::State s = m_timeLine->state();
    m_timeLine->stop();
    if(f >= m_eFrame){
        m_cFrame = m_eFrame;
        emit frameChanged(m_cFrame);
        emit finished();
    }else{
        if(f <= m_sFrame)
            m_cFrame = m_sFrame;
        else
            m_cFrame = f;
        emit frameChanged(m_cFrame);
        if(s == QTimeLine::Running)
            m_timeLine->start();
    }
}
