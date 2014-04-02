#ifndef STUDYOBJECT_H
#define STUDYOBJECT_H

#include <QObject>

class StudyObject : public QObject
{
    Q_OBJECT
public:
    explicit StudyObject(QObject *parent = 0);

signals:

public slots:

};

#endif // STUDYOBJECT_H
