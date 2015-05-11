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
    qDebug() << "ConfigMan::ConfigMan()";
    qDebug() << "settings path:" << QSettings::fileName();
    if(!QFile(QSettings::fileName()).exists()) {
        qDebug() << "file not exists";
        init();
    }
}

void ConfigMan::init() {
    const static QMap<QString, QString> strMap = {
        std::make_pair("DATA_STRUCT_PATH", "E:\\demography\\data\\sim\\0816"),
        std::make_pair("DATA_PATH", "E:\\demography\\data\\sim\\0926"),
        std::make_pair("RenKouGaiYao", "人口概要类字段名和对应指标名.txt"),
        std::make_pair("ShengYuHaiCi", "生育孩次类字段名和对应指标名.txt"),
        std::make_pair("ZhengCeShengYu", "政策生育类字段名和对应指标名.txt"),
        std::make_pair("FuFuZiNv", "夫妇子女类字段名和对应指标名.txt"),
        std::make_pair("FenLingTeFu", "分龄类字段名和对应指标名.txt"),
        std::make_pair("FenLingJiangFu", "分龄类字段名和对应指标名.txt"),
        std::make_pair("FenLingHeJi", "分龄类字段名和对应指标名.txt"),
        std::make_pair("START_YEAR", "2009"),
        std::make_pair("END_YEAR", "2130")
    };
    for(auto key : strMap.keys()) {
        QSettings::setValue(key, strMap.value(key));
    }
}
