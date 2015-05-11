#ifndef SEQUENCEBARVIEW3D_H
#define SEQUENCEBARVIEW3D_H

#include "sequencemodel.h"
#include "abstractsequenceview.h"
#include "sequencebarview3ditem.h"

class SequenceBarView3D : public AbstractSequenceView
{
    Q_OBJECT
public:
    SequenceBarView3D(SequenceModel *model, QObject *parent = 0);

    virtual void showPoints(bool flag);

signals:

public slots:
    void changeCurrentYear(int year);
    void changeTime(qreal value);
    void selectCurve(QString curve);

private:
    void initScene();

    SequenceBarView3DItem *m_mainItem;
};

#endif // SEQUENCEBARVIEW3D_H
