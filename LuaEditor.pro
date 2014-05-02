#-------------------------------------------------
#
# Project created by QtCreator 2013-07-22T21:19:36
#
#-------------------------------------------------

QT       += core widgets xml gui

TARGET = lua-editor
TEMPLATE = app

TRANSLATIONS = lua-editor_de.ts lua-editor_en.ts

SOURCES += main.cpp\
        mainwindow.cpp \
    LuaHighlighter.cpp \
    newfiledlg.cpp \
    AboutDlg.cpp \
    FindDlg.cpp \
    settings.cpp \
    settingsdlg.cpp \
    newprojectdlg.cpp \
    project.cpp

HEADERS  += mainwindow.h \
    LuaHighlighter.h \
    newfiledlg.h \
    AboutDlg.h \
    FindDlg.h \
    settings.h \
    settingsdlg.h \
    newprojectdlg.h \
    project.h

FORMS    += mainwindow.ui \
    newfiledlg.ui \
    aboutdlg.ui \
    finddlg.ui \
    settingsdlg.ui \
    newprojectdlg.ui

RESOURCES += \
    Icons.qrc

unix: INCLUDEPATH += $$PWD/lua/lua-5.2.2/install/include
# unix: INCLUDEPATH += /usr/include/lua5.2/
win32: INCLUDEPATH += $$PWD/lua/lua-windows/include

unix: LIBS += -L$$PWD/lua/lua-5.2.2/install/lib -llua
# unix: LIBS += -llua5.2
win32: LIBS += -L$$PWD/lua/lua-windows -llua52

OTHER_FILES += \
    resources.rc

win32: RC_FILE += resources.rc
