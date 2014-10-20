#ifndef YEARITEMMODEL_H
#define YEARITEMMODEL_H

#include <QStringListModel>

#define _MAX_YEAR 2050
#define _MIN_YEAR 1900

class YearItemModel : public QStringListModel
{
    Q_OBJECT
public:
    explicit YearItemModel(QObject *parent = 0);



signals:

public slots:

};

#endif // YEARITEMMODEL_H
