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
    datamanager.cpp \
    xmlmanager.cpp \
    dataitem.cpp

HEADERS  += \
    newprojectionwizard.hpp \
    datamanager.hpp \
    xmlmanager.hpp \
    dataitem.hpp
CONFIG += c++11

RESOURCES += \
    translator.qrc \
    resources.qrc

FORMS += \
    newprojectionwizard.ui
