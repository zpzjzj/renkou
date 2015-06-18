#include <QApplication>
#include <QTextCodec>
#include <QTranslator>

#include "mainwindow.h"
#include "uimanager.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));

    //load the translator
    QTranslator translator;
    bool b= translator.load(":/ui_zh_CN.qm");
    QTranslator trans2;
    bool b2 = trans2.load(":/qt_zh_CN.qm");
    if (b&&b2) {
        app.installTranslator(&translator);
        app.installTranslator(&trans2);
    } else {

    }

    MainWindow mainWindow;
    UiManager uiManager;
    mainWindow.setUiManager(&uiManager);
    mainWindow.show();
    return app.exec();
}
