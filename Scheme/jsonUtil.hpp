#ifndef JSONUTIL_HPP
#define JSONUTIL_HPP

#include <QJsonDocument>

namespace jsonUtil{
    QJsonDocument readFile(const QString& fileName);
}

#endif // JSONUTIL_HPP
