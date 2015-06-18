#-------------------------------------------------
#
# Project created by QtCreator 2013-06-09T10:06:56
#
#-------------------------------------------------

QT       += widgets sql testlib

TARGET = tst_testtest
CONFIG   += console
CONFIG   -= app_bundle
QMAKE_CXXFLAGS += "-std=c++0x"

TEMPLATE = app


SOURCES += tst_testtest.cpp \
    paraTest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
#INCLUDEPATH += E:\code\renkou\Scheme
LIBS += -L../lib -lScheme
DEPENDPATH += ..\Scheme
PRE_TARGETDEPS += ..\lib\libscheme.a
