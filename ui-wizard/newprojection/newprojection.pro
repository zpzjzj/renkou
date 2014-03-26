#-------------------------------------------------
#
# Project created by QtCreator 2014-02-24T20:59:07
#
#-------------------------------------------------
QT += widgets
QT += xml

TARGET = newprojection
TEMPLATE = app


SOURCES += main.cpp \
    newprojectionwizard.cpp \
    xmlmanager.cpp \
    datatreewidget.cpp \
    datatreewidgetitem.cpp \
    datatreewidgetleaf.cpp \
    datatreewidgetinner.cpp \
    datapage.cpp

HEADERS  += \
    newprojectionwizard.hpp \
    xmlmanager.hpp \
    datatreewidget.h \
    datatreewidgetitem.h \
    datatreewidgetleaf.h \
    datatreewidgetinner.h \
    datapage.h \
    wizardpages.h
CONFIG += c++11

RESOURCES += \
    translator.qrc \
    resources.qrc

FORMS += \
    newprojectionwizard.ui
