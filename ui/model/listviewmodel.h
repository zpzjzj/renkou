#ifndef LISTVIEWMODEL_H
#define LISTVIEWMODEL_H

#include <QAbstractListModel>

#ifndef _DEBUG
#define _DEBUG 1
#endif

class ListViewModel :
        public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ListViewModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;

    void refrushModel();
    virtual QVariant data(const QModelIndex &index, int role) const;
//    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

protected:
    QList<QVariant> listData;
signals:

public slots:



};

#endif // LISTVIEWMODEL_H
