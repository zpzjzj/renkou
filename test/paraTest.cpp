#include <QtTest/QtTest>
#include <QTextCodec>
#include "../Scheme/Para.hpp"

class ParaTest : public QObject {
    Q_OBJECT
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testPara();
};

void ParaTest::initTestCase()
{
}

void ParaTest::cleanupTestCase()
{
}

void ParaTest::testPara()
{
    QFile file("E:\\lab\\mine\\para.json");

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open para file");
        return;
    }
    QString val = file.readAll();
    qDebug() << "val:" << val << "\n";
    QJsonDocument doc(QJsonDocument::fromJson(val.toUtf8()));
    QJsonObject obj = doc.object();
    qDebug() << "val:" << val << "\n";
    const auto paras = scheme::Para::readParas(doc.object()["paras"].toArray());
    for(const auto& paraPtr : paras) {
        qDebug() << *paraPtr;
    }
}

#include "paraTest.moc"
