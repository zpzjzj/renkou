#include <QApplication>
#include <QStyleFactory>
#include <QTextCodec>
#include <QDebug>
#include "mainwindow.h"
#include "uimanager.h"
#include "../Scheme/ConfigMan.hpp"

int main(int argc, char *argv[]){
//    QApplication::setStyle(QStyleFactory::create("Windows"));
    QApplication app(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    if(!Config::config.read()) {
        qCritical() << "Failed to init config file";
    }
    MainWindow mainWindow;
    UiManager uiManager;
    mainWindow.setUiManager(&uiManager);
    mainWindow.show();
    return app.exec();
}
