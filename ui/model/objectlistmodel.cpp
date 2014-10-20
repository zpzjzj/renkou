#include "demoobject.h"
#include "objectlistmodel.h"
#include "controller/objectlistmanager.h"

ObjectListModel::ObjectListModel()
{
    this->objManager = ObjectListManager::getInstance();
//    listData.append("testObj");
//    listData.append("1900 beijing");

//    for (int index=0; index<objManager->objectCount(); ++index){
//        DemoObject object = DemoObject(objManager->at(index));

//        listData.append(object.toVariant());
//    }
}

QVariant ObjectListModel::data(const QModelIndex &index, int role) const{
    if (role == Qt::DisplayRole){
        DemoObject object = DemoObject(objManager->at(index.row()));
        return object.toVariant();
    }

    return QVariant();
}

int ObjectListModel::rowCount(const QModelIndex &parent) const{
    return objManager->objectCount();
}

int ObjectListModel::testRowCount()const {
    return objManager->objectCount();
}

