#-------------------------------------------------
#
# Project created by QtCreator 2013-10-19T16:17:43
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=c++1y

QT       += core gui xml opengl
CONFIG += c++14

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
    SelDispCombo.cpp \
    SchemeSel.cpp \
    Scheme.cpp \
    paraUtil.cpp \
    SchemeListManager.cpp \
    IndicatorSel.cpp \
    schemeDisplayWizard.cpp \
    IndicatorSelTabWidget.cpp \
    display/mapgraphbase.cpp \
    display/mapinformation.cpp \
    display/maptype1.cpp \
    display/pyramidbarview.cpp \
    display/pyramidcontroller.cpp \
    display/pyramidmodel.cpp \
    display/pyramidstripview.cpp \
    display/pyramidviewbaritem.cpp \
    display/pyramidviewstripitem.cpp \
    display/sequencebarview.cpp \
    display/sequencebarview3d.cpp \
    display/sequencebarview3ditem.cpp \
    display/sequencebarviewitem.cpp \
    display/sequencecontroller.cpp \
    display/sequencemodel.cpp \
    display/sequencestriplineview.cpp \
    display/sequencestripviewitem.cpp \
    display/dataprovider.cpp \
    display/heightmap.cpp \
    display/glfont.cpp \
    display/abstractpyramidview.cpp \
    display/abstractsequenceview.cpp \
    display/coloriconengine.cpp \
    display/mytimeline.cpp \
    display/myellipseitem.cpp \
    display/mylineitem.cpp \
    display/mytextitem.cpp \
    display/graphview.cpp \
    display/labels.cpp

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
    Singleton.hpp \
    SchemeSel.hpp \
    Scheme.hpp \
    Select.hpp \
    iterate.hpp \
    paraUtil.hpp \
    SchemeListManager.hpp \
    IndicatorSel.hpp \
    schemeDisplayWizard.hpp \
    IndicatorSelTabWidget.hpp \
    display/mapgraphbase.h \
    display/mapinformation.h \
    display/maptype1.h \
    display/pyramidbarview.h \
    display/pyramidcontroller.h \
    display/pyramidmodel.h \
    display/pyramidstripview.h \
    display/pyramidviewbaritem.h \
    display/pyramidviewstripitem.h \
    display/sequencebarview.h \
    display/sequencebarview3d.h \
    display/sequencebarview3ditem.h \
    display/sequencebarviewitem.h \
    display/sequencecontroller.h \
    display/sequencemodel.h \
    display/sequencestriplineview.h \
    display/sequencestripviewitem.h \
    display/Constants.h \
    display/dataprovider.h \
    display/FileInfo.h \
    display/heightmap.h \
    display/glfont.h \
    display/abstractpyramidview.h \
    display/abstractsequenceview.h \
    display/coloriconengine.h \
    display/mytimeline.h \
    display/Objectcounter.h \
    display/myellipseitem.h \
    display/mylineitem.h \
    display/mytextitem.h \
    display/graphview.h \
    display/MyUtility.h

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
    SchemeSel.ui \
    IndicatorSel.ui \
    selSchemeWizardPage.ui \
    selIndicatorWizardPage.ui \
    schemeDisplaywizard.ui \
    display/maptype1.ui \
    display/pyramidcontroller.ui \
    display/sequencecontroller.ui

OTHER_FILES += \
    qt_zh_CN.qm \
    .gitignore \
    newprojection.pro.user \
    ui.pro.user

SUBDIRS += \
    newprojection.pro

RESOURCES += \
    translator.qrc \
    image.qrc \
    resource.qrc

include(external.pri)

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib
LIBS += -L../lib -lScheme
DEPENDPATH += ..\Scheme
PRE_TARGETDEPS += ..\lib\libscheme.a
