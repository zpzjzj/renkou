#include "Category.hpp"
#include <QObject>
#include <QMap>
namespace {
using Category = scheme::Category;
const static QMap<Category, QString> map = {
    std::make_pair(Category::RenKouGaiYao, QObject::tr("人口概要")),
    std::make_pair(Category::ShengYuHaiCi, QObject::tr("生育孩次")),
    std::make_pair(Category::ZhengCeShengYu, QObject::tr("政策生育")),
    std::make_pair(Category::FuFuZiNv, QObject::tr("夫妇子女")),
    std::make_pair(Category::FenLingTeFu, QObject::tr("分龄特扶")),
    std::make_pair(Category::FenLingJiangFu, QObject::tr("分龄父母")),
    std::make_pair(Category::FenLingHeJi, QObject::tr("分龄合计"))
};
}

QString scheme::toString(Category category) {
    return map.value(category);
}

Category scheme::fromString(const QString& str) {
    return map.key(str);
}

bool scheme::isFenLing(Category category) {
    switch (category) {
        case Category::FenLingHeJi:
        case Category::FenLingJiangFu:
        case Category::FenLingTeFu:
            return true;
        default:
            return false;
    }
}
