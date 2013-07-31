#-------------------------------------------------
#
# Project created by QtCreator 2013-07-22T21:19:36
#
#-------------------------------------------------

QT       += core gui

TARGET = LuaEditor
TEMPLATE = app

TRANSLATIONS = lua-editor_de.ts lua-editor_en.ts

SOURCES += main.cpp\
        mainwindow.cpp \
    LuaHighlighter.cpp \
    newfiledlg.cpp \
    AboutDlg.cpp

HEADERS  += mainwindow.h \
    LuaHighlighter.h \
    newfiledlg.h \
    AboutDlg.h

FORMS    += mainwindow.ui \
    newfiledlg.ui \
    aboutdlg.ui

RESOURCES += \
    Icons.qrc

INCLUDEPATH += $$PWD/lua/lua-5.2.2/install/include

LIBS += -L$$PWD/lua/lua-5.2.2/install/lib -llua
