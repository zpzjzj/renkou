#include <iostream>
#include <cstdlib>
#include <QTextStream>
#include <QFile>
#include "ConfigMan.hpp"
#include "exceptions/ValueNotExist.hpp"
#include <QTextCodec>
#include <QDebug>

using namespace Config;

ConfigMan Config::config;

ConfigMan::ConfigMan() :
    QSettings("Demography Group", "scheme") {
    qDebug() << "settings path:" << QSettings::fileName();
    if(!QFile(QSettings::fileName()).exists()) {
        init();
        QSettings::sync();
        qDebug() << "sync done";
    }
}

void ConfigMan::init() {
    const static QMap<QString, QString> strMap = {
        std::make_pair("DATA_STRUCT_PATH", "E:\\demography\\data\\sim\\0816\\"),
        std::make_pair("DATA_PATH", "E:\\demography\\data\\sim\\0926\\"),
        std::make_pair("RenKouGaiYao", "人口概要类字段名和对应指标名.txt"),
        std::make_pair("ShengYuHaiCi", "生育孩次类字段名和对应指标名.txt"),
        std::make_pair("ZhengCeShengYu", "政策生育类字段名和对应指标名.txt"),
        std::make_pair("FuFuZiNv", "夫妇子女类字段名和对应指标名.txt"),
        std::make_pair("FenLingTeFu", "分龄特扶类字段名和对应指标名.txt"),
        std::make_pair("FenLingJiangFu", "分龄父母类字段名和对应指标名.txt"),
        std::make_pair("FenLingHeJi", "分龄合计类字段名和对应指标名.txt"),
        std::make_pair("FenLingNongYe", "分龄农业类字段名和对应指标名.txt"),
        std::make_pair("FenLingFeiNong", "分龄非农类字段名和对应指标名.txt")
    };
    for(auto key : strMap.keys()) {
        QSettings::setValue(key, strMap.value(key));
    }
}
