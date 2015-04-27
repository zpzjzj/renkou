#ifndef _CONFIG_MAN_HPP
#define _CONFIG_MAN_HPP
#include <QMap>
#include <QString>
#include <QSettings>

/**
 * aim: I shall make the program run normally evenif config is not loaded
 * usage:
 * 1, Decalare:
 * 		ConfigMan config;
 * 2, read Configure file
 * 		config.read("config.txt");
 * 2.1, validate:
 * 		if (config.read())
 * 			or
 * 		config.read();
 * 		if (config.success());
 * 3, read value:
 * 		config.value("startYear")
 */
namespace Config {

    class ConfigMan : QSettings{
        public:
            ConfigMan();
            ~ConfigMan(void) {}
            QString value(const QString& key) const {return QSettings::value(key).toString();}
            QString operator [] (const QString& key) const {return value(key);}
            int Int(const QString& key) const {return QSettings::value(key).toInt();}
            double Double(const QString& key) const {return QSettings::value(key).toDouble();}
        private:
            /**
             * @brief init
             *      init the settings, when there's none
             */
            void init();
    } ;

    // the default instance
    // you can decalare your own configman
    extern ConfigMan config;
};

#endif
