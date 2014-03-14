#include "newprojectionwizard.hpp"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
//    Q_INIT_RESOURCE(newprojection);
    QTranslator oTranslator;
    oTranslator.load("://qt_zh_CN.qm");

    QApplication app(argc, argv);
    app.installTranslator(&oTranslator);

    NewProjectionWizard w;
    w.show();

    return app.exec();
}
