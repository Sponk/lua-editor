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
    newfiledlg.cpp

HEADERS  += mainwindow.h \
    LuaHighlighter.h \
    newfiledlg.h

FORMS    += mainwindow.ui \
    newfiledlg.ui

RESOURCES += \
    Icons.qrc
