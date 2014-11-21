CONFIG += staticlib
TEMPLATE  = lib
TARGET = Scheme
QMAKE_CXXFLAGS += "-arch x86_64 -x c++ -std=c++1y -stdlib=libc++ -Wall -O0"
QT += core
DESTDIR = ..\lib

HEADERS += \
    SchemeParameter.hpp \
    schememetadata.h \
    SchemeInstance.hpp \
    SchemeIndicator.hpp \
    SchemeExceptionBag.hpp \
    SchemeDef.hpp \
    SchemeBuffer.hpp \
    Scheme.hpp \
    parasetter.hpp \
    paraRule.hpp \
    paraholder.hpp \
    metadataItem.h \
    ConfigMan.hpp \
    AbstractScheme.hpp \
    exceptions/ValueNotExist.hpp \
    exceptions/RecordNotExist.hpp \
    exceptions/InstanceIndexOutOfRange.hpp \
    exceptions/IndicatorIndexOutOfRange.hpp \
    exceptions/ExceptionNoParaName.hpp \
    exceptions/ColumnNotExist.hpp \
    transfromPara.hpp \
    Para.hpp

SOURCES += \
    SchemeParameter.cpp \
    schememetadata.cpp \
    SchemeInstance.cpp \
    SchemeBuffer.cpp \
    Scheme.cpp \
    parasetter.cpp \
    paraholder.cpp \
    metadataItem.cpp \
    ConfigMan.cpp \
    transfromPara.cpp \
    Para.cpp
