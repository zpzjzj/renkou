#include "newobjectlistmodel.h"

NewObjectListModel::NewObjectListModel(QObject *parent) :
    ListViewModel(parent)
{
    listData.append(QString("研究对象"));
//    listData.append(QString("预留2"));
}
