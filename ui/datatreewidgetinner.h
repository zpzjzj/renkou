#ifndef DATATREEWIDGETINNER_H
#define DATATREEWIDGETINNER_H

#include "datatreewidgetitem.h"
#include <QList>

class DataTreeWidgetInner:public DataTreeWidgetItem
{
public:
    DataTreeWidgetInner();
    ~DataTreeWidgetInner();
private:
    QList<DataTreeWidgetItem*> *m_children;
};

#endif // DATATREEWIDGETINNER_H
