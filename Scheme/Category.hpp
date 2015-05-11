#ifndef CATEGORY_HPP
#define CATEGORY_HPP

#include <QString>

namespace scheme {
    enum Category{
        RenKouGaiYao,
        FuFuZiNv,
        ShengYuHaiCi,
        ZhengCeShengYu,
        FenLingTeFu,
        FenLingJiangFu,
        FenLingHeJi
    };

    Category fromString(const QString& str);
    QString toString(Category category);
}

#endif // CATEGORY_HPP
