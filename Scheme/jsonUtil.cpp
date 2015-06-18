#include "jsonUtil.hpp"
#include <QFile>
#include <QDebug>

QJsonDocument jsonUtil::readFile(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open file" << fileName;
        qWarning() << "err: " << file.errorString();
        return QJsonDocument();
    }
    QString val = file.readAll();
    file.close();
    return QJsonDocument(QJsonDocument::fromJson(val.toUtf8()));
}
