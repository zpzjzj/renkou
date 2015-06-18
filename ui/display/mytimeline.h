#ifndef MYTIMELINE_H
#define MYTIMELINE_H

#include <QObject>
#include <QTimeLine>

class MyTimeLine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int frame READ getFrame WRITE setFrame)

public:
    explicit MyTimeLine(QObject *parent = 0);
    ~MyTimeLine();

    void setFrameRange(int sf, int ef);
    void setInterval(int t);
    int getFrame() const;
    void setFrame(int f);

signals:
    void frameChanged(int);
    void timeChanged(qreal);
    void finished();

public slots:
    void start();
    void stop();
    void resume();
    void pause();
    void updateTimeLine();

private:
    int m_sFrame;
    int m_eFrame;
    int m_interval;
    int m_cFrame;

    QTimeLine* m_timeLine;
};

#endif // MYTIMELINE_H
