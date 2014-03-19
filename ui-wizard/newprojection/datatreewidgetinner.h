#ifndef DATATREEWIDGETINNER_H
#define DATATREEWIDGETINNER_H

#include "datatreewidgetitem.h"

class QList;

class DataTreeWidgetInner:public DataTreeWidgetItem
{
public:
    DataTreeWidgetInner();
private:
    QList<DataTreeWidgetItem*> *m_children;
};

#endif // DATATREEWIDGETINNER_H
