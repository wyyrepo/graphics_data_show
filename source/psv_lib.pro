
DEFINES += _PSVLIB_DLL
NAME = psv_lib
TEMPLATE = lib
TARGET = $${NAME}$${QT_MAJOR_VERSION}
message(当前版本:$$QT_VERSION)
message(TARGET:$$TARGET)

CONFIG	+= qt
#CONFIG	+=  warn_on
#CONFIG	+=  debug_and_release
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += gui
QT += core
INCLUDEPATH += ./include


win32 {
    CONFIG(debug, debug|release){
        OBJECTS_DIR = ./TEMP/$${TARGET}/debug
    }
    CONFIG(release, debug|release){
        OBJECTS_DIR = ./TEMP/$${TARGET}/release
    }
    DESTDIR = ./bin
} else {
    DESTDIR  = ./release/bin
    OBJECTS_DIR = ./TEMP/$${TARGET}
}

UI_DIR      = $${OBJECTS_DIR}/uic
MOC_DIR     = $${OBJECTS_DIR}/moc
RCC_DIR     = $${OBJECTS_DIR}/rcc
INCLUDEPATH += $${OBJECTS_DIR}/uic

SOURCES += source/psv_graphicsview.cpp
SOURCES += source/psv_singleitem_ellipse.cpp
SOURCES += source/psv_cfgdlg_curve.cpp
SOURCES += source/psv_item_p.cpp
SOURCES += source/psv_cfgdlg_item.cpp
SOURCES += source/psv_buttonitem.cpp
SOURCES += source/psv_treeitem.cpp
SOURCES += source/psv_graphicsscene.cpp
SOURCES += source/psv_histogramitem.cpp
SOURCES += source/psv_define.cpp
SOURCES += source/psv_public.cpp
SOURCES += source/psv_circularindicatoritem.cpp
SOURCES += source/psv_axisitem.cpp
SOURCES += source/psv_tableitem.cpp
SOURCES += source/psv_pie3item.cpp
SOURCES += source/psv_sectoritem.cpp
SOURCES += source/psv_chartitem.cpp
SOURCES += source/psv_charttimeitem.cpp
SOURCES += source/psv_axisleftitem.cpp
SOURCES += source/psv_axisrightitem.cpp
SOURCES += source/psv_axisdownitem.cpp
SOURCES += source/psv_axisupitem.cpp
SOURCES += source/psv_item.cpp
SOURCES += source/psv_chartdatetimeitem.cpp
SOURCES += source/psv_chartrealitem.cpp
SOURCES += source/psv_charthistogramitem.cpp
SOURCES += source/psv_chartareaitem.cpp
SOURCES += source/psv_tablewidgetitem.cpp
SOURCES += source/psv_painterpathitem.cpp
SOURCES += source/psv_verticalindicatoritem.cpp
SOURCES += source/psv_chartbaritem.cpp
SOURCES += source/psv_levelitem.cpp

HEADERS += include/psv_graphicsview.h
HEADERS += include/psv_singleitem_ellipse.h
HEADERS += include/psv_cfgdlg_curve.h
HEADERS += include/psv_item_p.h
HEADERS += include/psv_cfgdlg_item.h
HEADERS += include/psv_buttonitem.h
HEADERS += include/psv_treeitem.h
HEADERS += include/psv_graphicsscene.h
HEADERS += include/psv_histogramitem.h
HEADERS += include/psv_public.h
HEADERS += include/psv_define.h
HEADERS += include/psv_circularindicatoritem.h
HEADERS += include/psv_axisitem.h
HEADERS += include/psv_tableitem.h
HEADERS += include/psv_pie3item.h
HEADERS += include/psv_sectoritem.h
HEADERS += include/psv_chartitem.h
HEADERS += include/psv_charttimeitem.h
HEADERS += include/psv_axisleftitem.h
HEADERS += include/psv_axisrightitem.h
HEADERS += include/psv_axisdownitem.h
HEADERS += include/psv_axisupitem.h
HEADERS += include/psv_item.h
HEADERS += include/psv_chartdatetimeitem.h
HEADERS += include/psv_chartrealitem.h
HEADERS += include/psv_charthistogramitem.h
HEADERS += include/psv_chartareaitem.h
HEADERS += include/psv_tablewidgetitem.h
HEADERS += include/psv_painterpathitem.h
HEADERS += include/psv_verticalindicatoritem.h
HEADERS += include/psv_chartbaritem.h
HEADERS += include/psv_levelitem.h
HEADERS += include/psvlib.h

##============================
FORMS += ui/psv_cfgdlg_curve.ui
FORMS += ui/psv_cfgdlg_item.ui
