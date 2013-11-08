#-------------------------------------------------
#
# Project created by QtCreator 2013-07-22T21:19:36
#
#-------------------------------------------------

QT       += core gui xml

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

INCLUDEPATH += $$PWD/lua/lua-5.2.2/install/include

LIBS += -L$$PWD/lua/lua-5.2.2/install/lib -llua
