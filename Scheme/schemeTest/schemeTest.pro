#-------------------------------------------------
#
# Project created by QtCreator 2014-04-09T21:06:42
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_SchemeParaTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_SchemeParaTest.cpp \
    ../SchemeParameter.cpp \
    ../schememetadata.cpp \
    ../SchemeInstance.cpp \
    ../SchemeBuffer.cpp \
    ../Scheme.cpp \
    ../parasetter.cpp \
    ../paraholder.cpp \
    ../metadataItem.cpp \
    ../ConfigMan.cpp \
    ../AbstractScheme.cpp
SOURCES +=  ../para.cpp \
            ../transfromPara.cpp
HEADERS +=  ../para.h \
            ../transfromPara.h \
    ../transfromPara.hpp \
    ../TestPara.hpp \
    ../SchemeParameter.hpp \
    ../schememetadata.h \
    ../SchemeItem.hpp \
    ../SchemeInstance.hpp \
    ../SchemeIndicator.hpp \
    ../SchemeExceptionBag.hpp \
    ../SchemeDef.hpp \
    ../SchemeBuffer.hpp \
    ../Scheme.hpp \
    ../parasetter.hpp \
    ../paraRule.hpp \
    ../paraholder.hpp \
    ../metadataItem.h \
    ../ConfigMan.hpp \
    ../AbstractScheme.hpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
QMAKE_CXXFLAGS += "-std=c++0x -Wall -O0"
