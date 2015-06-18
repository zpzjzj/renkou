#-------------------------------------------------
#
# Project created by QtCreator 2013-10-19T16:17:43
#
#-------------------------------------------------

QT       += core gui xml
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ui
TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    uimanager.cpp \
    newproject.cpp \
    openproject.cpp \
    searchobject.cpp \
    entercalculate.cpp \
    evaluate.cpp \
    display.cpp \
    uiitem.cpp \
    objectlist.cpp \
    studyobject.cpp \
    controller/objectlistmanager.cpp \
    model/areaitemmodel.cpp \
    model/demoobject.cpp \
    model/listviewmodel.cpp \
    model/newobjectlistmodel.cpp \
    model/objectlistmodel.cpp \
    model/projectionlistmodel.cpp \
    model/yearitemmodel.cpp \
    view/projectionmanagement.cpp \
    view/paramselectwidget.cpp \
    view/projectionbodywidget.cpp \
    model/paramvaluejsonobject.cpp \
    model/paramitemjsonobject.cpp

HEADERS  += \
    mainwindow.h \
    uimanager.h \
    newproject.h \
    openproject.h \
    searchobject.h \
    entercalculate.h \
    evaluate.h \
    display.h \
    uiitem.h \
    EnumClass.h \
    objectlist.h \
    studyobject.h \
    controller/objectlistmanager.h \
    model/areaitemmodel.h \
    model/demoobject.h \
    model/listviewmodel.h \
    model/newobjectlistmodel.h \
    model/objectlistmodel.h \
    model/projectionlistmodel.h \
    model/yearitemmodel.h \
    view/projectionmanagement.h \
    view/paramselectwidget.h \
    view/projectionbodywidget.h \
    model/paramvaluejsonobject.h \
    model/paramitemjsonobject.h

FORMS += \
    dia_accu_linetype1.ui \
    dia_accu_linetype2.ui \
    display.ui \
    entercalculate.ui \
    evaluate.ui \
    linetype1.ui \
    linetype2.ui \
    mainwindow.ui \
    newproject.ui \
    openProject.ui \
    progress_bar.ui \
    searchobject.ui \
    paramselectiontabwidget.ui \
    projectionmanagement.ui \
    fileButtonGroupWidget.ui \
    view/projectionbodywidget.ui

OTHER_FILES += \
    qt_zh_CN.qm \
    .gitignore \
    newprojection.pro.user \
    ui.pro.user

SUBDIRS += \
    newprojection.pro

TRANSLATIONS += ui_zh_CN.ts

RESOURCES += \
    translator.qrc \
    resource.qrc

DISTFILES +=
