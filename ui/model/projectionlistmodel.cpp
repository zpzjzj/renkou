#include "projectionlistmodel.h"

ProjectionListModel::ProjectionListModel(QObject *parent) :
     ListViewModel(parent)
{
    listData.append(QString("预测工程"));
//    listData.append(QString("工程类型2"));
}
