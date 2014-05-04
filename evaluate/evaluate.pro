#---------------------------------------
# 
#  PROJECT CREATED BY OWENSSS 2013/03/03
#
#---------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = evaluate
TMEPLATE = app
QMAKE_CXXFLAGS += "-std=c++0x"
# config += exceptions
INCLUDEPATH += D:\renkou\Scheme
INCLUDEPATH += D:\boost_1_55_0\
DEPENDPATH += ..\Scheme
PRE_TARGETDEPS += ..\lib\libscheme.a

LIBS += -LD:\renkou\lib -LD:\boost_1_55_0\stage\lib
# LIBS += -lScheme -lboost_filesystem-mgw48-mt-1_55 -lboost_system-mgw48-mt-1_55
LIBS += "D:\boost_1_55_0\stage\lib\libboost_filesystem-mgw47-mt-1_55.a"
LIBS += "D:\boost_1_55_0\stage\lib\libboost_system-mgw47-mt-1_55.a"
LIBS += -lScheme

SOURCES += evaluate.cpp \
		method_add.cpp \
    add_multi.cpp
HEADERS += method_add.h \
                evaluate.h \
		method_add_impl.h \
    add_multi.h
