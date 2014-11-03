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
    xmlmanager.cpp \
    controller/objectlistmanager.cpp \
    model/areaitemmodel.cpp \
    model/demoobject.cpp \
    model/listviewmodel.cpp \
    model/newobjectlistmodel.cpp \
    model/objectlistmodel.cpp \
    model/projectionlistmodel.cpp \
    model/yearitemmodel.cpp \
    view/newfilewizard.cpp \
    view/newobjectwizardpage.cpp \
    view/newprojectionwizardpage.cpp \
    view/selectwizardpage.cpp \
    view/mainwindowrightwidget.cpp \
    ParasManager.cpp \
    UiGenerator.cpp \
    SelDispCombo.cpp

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
    xmlmanager.hpp \
    controller/objectlistmanager.h \
    model/areaitemmodel.h \
    model/demoobject.h \
    model/listviewmodel.h \
    model/newobjectlistmodel.h \
    model/objectlistmodel.h \
    model/projectionlistmodel.h \
    model/yearitemmodel.h \
    view/newfilewizard.h \
    view/newobjectwizardpage.h \
    view/newprojectionwizardpage.h \
    view/selectwizardpage.h \
    view/wizardpages.h \
    view/mainwindowrightwidget.h \
    ParasManager.hpp \
    UiGenerator.hpp \
    SelDispCombo.hpp \
    Singleton.hpp

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
    newprojectionwizard.ui \
    ui_wizard/newfilewizard.ui \
    ui_wizard/newobjectwizardpage.ui \
    ui_wizard/newprojectionwizardpage.ui \
    ui_wizard/selectwizardpage.ui \
    openProject.ui \
    SelDispCombo.ui

OTHER_FILES += \
    qt_zh_CN.qm \
    .gitignore \
    newprojection.pro.user \
    ui.pro.user

SUBDIRS += \
    newprojection.pro

RESOURCES += \
    translator.qrc \
    resource.qrc \
    image.qrc

INCLUDEPATH += E:\code\renkou\Scheme
LIBS += -LE:\code\renkou\lib -lScheme
DEPENDPATH += ..\Scheme
PRE_TARGETDEPS += ..\lib\libscheme.a
