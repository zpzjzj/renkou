#ifndef SEQUENCEBARVIEW_H
#define SEQUENCEBARVIEW_H

#include "sequencemodel.h"
#include "abstractsequenceview.h"
#include "sequencebarviewitem.h"

class SequenceBarView : public AbstractSequenceView
{
    Q_OBJECT
public:
    explicit SequenceBarView(SequenceModel *model, QObject *parent = 0);

    void showPoints(bool flag);

signals:

public slots:
    void changeCurrentYear(int year);
    void changeTime(qreal value);
    void selectCurve(QString curve);

private:
    void initScene();

    SequenceBarViewItem *m_mainItem;

    bool m_showPoints;
};

#endif // SEQUENCEBARVIEW_H
