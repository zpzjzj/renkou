#include "yearitemmodel.h"

YearItemModel::YearItemModel(QObject *parent) :
    QStringListModel(parent)
{
    QStringList list;
    for (int i=_MIN_YEAR; i<=_MAX_YEAR; ++i){
        list << QVariant(i).toString();
    }
    this->setStringList(list);
}

