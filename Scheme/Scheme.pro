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
    Para.hpp \
    Singleton.hpp \
    jsonUtil.hpp \
    paraUtil.hpp \
    stlUtil.hpp \
    Select.hpp \
    add.hpp \
    has_mem.hpp \
    has_xxx.hpp \
    is_container.hpp \
    Category.hpp

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
    Para.cpp \
    jsonUtil.cpp \
    paraUtil.cpp \
    Category.cpp

RESOURCES += \
    config.qrc

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib
