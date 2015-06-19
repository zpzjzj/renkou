#ifndef OBJECTLISTMODEL_H
#define OBJECTLISTMODEL_H

#include "listviewmodel.h"

class ObjectListManager;
class DemoObject;

class ObjectListModel : public ListViewModel
{
public:
    ObjectListModel();

    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;

    const DemoObject & backObject();
    int testRowCount() const;
private:
    ObjectListManager *objManager;
};

#endif // OBJECTLISTMODEL_H
