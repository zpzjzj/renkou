#-------------------------------------------------
#
# Project created by QtCreator 2013-10-19T16:17:43
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=c++0x

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
    importbasicdata.cpp \
    importbasicpara.cpp \
    entercalculate.cpp \
    evaluate.cpp \
    display.cpp \
    uiitem.cpp \
    datapage.cpp \
    datatreewidget.cpp \
    datatreewidgetinner.cpp \
    datatreewidgetitem.cpp \
    datatreewidgetleaf.cpp \
    newprojectionwizard.cpp \
    objectlist.cpp \
    studyobject.cpp \
    xmlmanager.cpp

HEADERS  += \
    mainwindow.h \
    uimanager.h \
    newproject.h \
    openproject.h \
    searchobject.h \
    importbasicdata.h \
    importbasicpara.h \
    entercalculate.h \
    evaluate.h \
    display.h \
    uiitem.h \
    datapage.h \
    datatreewidget.h \
    datatreewidgetinner.h \
    datatreewidgetitem.h \
    datatreewidgetleaf.h \
    EnumClass.h \
    newprojectionwizard.hpp \
    objectlist.h \
    studyobject.h \
    wizardpages.h \
    xmlmanager.hpp

FORMS += \
    customMadeArea.ui \
    dia_accu_linetype1.ui \
    dia_accu_linetype2.ui \
    display.ui \
    doingCalcProgress.ui \
    entercalculate.ui \
    evaluate.ui \
    importBasicData.ui \
    importBasicPara.ui \
    linetype1.ui \
    linetype2.ui \
    mainwindow.ui \
    newproject.ui \
    openProject.ui \
    progress_bar.ui \
    searchobject.ui \
    custommadearea.ui \
    newprojectionwizard.ui

OTHER_FILES += \
    qt_zh_CN.qm \
    .gitignore \
    newprojection.pro.user \
    ui.pro.user

SUBDIRS += \
    newprojection.pro

RESOURCES += \
    resources.qrc \
    translator.qrc
