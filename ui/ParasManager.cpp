#include "ParasManager.hpp"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

const QString ParasManager::PARA_PATH = "E:\\lab\\mine\\para.json";

ParasManager::ParasManager()
{
}

void ParasManager::read() {
    QFile file(PARA_PATH);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open para file");
        return;
    }
    QString val = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(val.toUtf8()));
    mParaSet = scheme::Para::readParas(doc.object()["paras"].toArray());
}
