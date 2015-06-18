#include <QApplication>
#include <QStyleFactory>
#include <QTextCodec>
#include <QTranslator>
#include <QLibraryInfo>
#include <QDebug>
#include <QDialogButtonBox>

#include "mainwindow.h"
#include "uimanager.h"
#include "../Scheme/ConfigMan.hpp"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    MainWindow mainWindow;
    mainWindow.setWindowTitle(MainWindow::tr("人口仿真模拟系统"));
    UiManager uiManager;
    mainWindow.setUiManager(&uiManager);
    mainWindow.show();

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
            QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    return app.exec();
}
