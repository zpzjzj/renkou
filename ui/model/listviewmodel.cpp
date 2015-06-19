#include "listviewmodel.h"

ListViewModel::ListViewModel(QObject *)
{

}

int ListViewModel::rowCount(const QModelIndex &) const{
    return listData.count();
}

QVariant ListViewModel::data(const QModelIndex &index, int role) const{
    if (role == Qt::DisplayRole){
        return listData.at(index.row());
    }

    return QVariant();
}

void ListViewModel::refrushModel(){
    this->beginResetModel();
    this->endResetModel();

    emit(valueChanged());
}

//pubic slots
