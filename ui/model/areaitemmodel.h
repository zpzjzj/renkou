#ifndef AREAITEMMODEL_H
#define AREAITEMMODEL_H

#include <QStringListModel>

#define _AREA_JSON_FILE_PATH ":/json/config/area.json"

class AreaItemModel : public QStringListModel
{
    Q_OBJECT
public:
    explicit AreaItemModel(QObject *parent = 0);

private:
    void init();
    bool loadJsonDocument(const char filename[]);
    QString read(const QJsonObject &json, const QString &key);
signals:

public slots:

private:
    QStringList list;

};

#endif // AREAITEMMODEL_H
