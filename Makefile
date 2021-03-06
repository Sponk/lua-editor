#############################################################################
# Makefile for building: lua-editor
# Generated by qmake (2.01a) (Qt 4.8.6) on: Fr. Mai 2 17:42:59 2014
# Project:  LuaEditor.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -o Makefile LuaEditor.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_XML_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtXml -I/usr/include/qt4 -Ilua/lua-5.2.2/install/include -I. -I.
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -L/home/yannick/Projekte/lua-editor-debian/lua-editor/lua/lua-5.2.2/install/lib -llua -lQtXml -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		mainwindow.cpp \
		LuaHighlighter.cpp \
		newfiledlg.cpp \
		AboutDlg.cpp \
		FindDlg.cpp \
		settings.cpp \
		settingsdlg.cpp \
		newprojectdlg.cpp \
		project.cpp moc_mainwindow.cpp \
		moc_LuaHighlighter.cpp \
		moc_newfiledlg.cpp \
		moc_AboutDlg.cpp \
		moc_FindDlg.cpp \
		moc_settingsdlg.cpp \
		moc_newprojectdlg.cpp \
		qrc_Icons.cpp
OBJECTS       = main.o \
		mainwindow.o \
		LuaHighlighter.o \
		newfiledlg.o \
		AboutDlg.o \
		FindDlg.o \
		settings.o \
		settingsdlg.o \
		newprojectdlg.o \
		project.o \
		moc_mainwindow.o \
		moc_LuaHighlighter.o \
		moc_newfiledlg.o \
		moc_AboutDlg.o \
		moc_FindDlg.o \
		moc_settingsdlg.o \
		moc_newprojectdlg.o \
		qrc_Icons.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		LuaEditor.pro
QMAKE_TARGET  = lua-editor
DESTDIR       = 
TARGET        = lua-editor

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mainwindow.h ui_newfiledlg.h ui_aboutdlg.h ui_finddlg.h ui_settingsdlg.h ui_newprojectdlg.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: LuaEditor.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtXml.prl \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile LuaEditor.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtXml.prl:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile LuaEditor.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/lua-editor1.0.0 || $(MKDIR) .tmp/lua-editor1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/lua-editor1.0.0/ && $(COPY_FILE) --parents mainwindow.h LuaHighlighter.h newfiledlg.h AboutDlg.h FindDlg.h settings.h settingsdlg.h newprojectdlg.h project.h .tmp/lua-editor1.0.0/ && $(COPY_FILE) --parents Icons.qrc .tmp/lua-editor1.0.0/ && $(COPY_FILE) --parents main.cpp mainwindow.cpp LuaHighlighter.cpp newfiledlg.cpp AboutDlg.cpp FindDlg.cpp settings.cpp settingsdlg.cpp newprojectdlg.cpp project.cpp .tmp/lua-editor1.0.0/ && $(COPY_FILE) --parents mainwindow.ui newfiledlg.ui aboutdlg.ui finddlg.ui settingsdlg.ui newprojectdlg.ui .tmp/lua-editor1.0.0/ && $(COPY_FILE) --parents lua-editor_de.ts lua-editor_en.ts .tmp/lua-editor1.0.0/ && (cd `dirname .tmp/lua-editor1.0.0` && $(TAR) lua-editor1.0.0.tar lua-editor1.0.0 && $(COMPRESS) lua-editor1.0.0.tar) && $(MOVE) `dirname .tmp/lua-editor1.0.0`/lua-editor1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/lua-editor1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_LuaHighlighter.cpp moc_newfiledlg.cpp moc_AboutDlg.cpp moc_FindDlg.cpp moc_settingsdlg.cpp moc_newprojectdlg.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_LuaHighlighter.cpp moc_newfiledlg.cpp moc_AboutDlg.cpp moc_FindDlg.cpp moc_settingsdlg.cpp moc_newprojectdlg.cpp
moc_mainwindow.cpp: LuaHighlighter.h \
		settings.h \
		project.h \
		mainwindow.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_LuaHighlighter.cpp: LuaHighlighter.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) LuaHighlighter.h -o moc_LuaHighlighter.cpp

moc_newfiledlg.cpp: newfiledlg.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) newfiledlg.h -o moc_newfiledlg.cpp

moc_AboutDlg.cpp: AboutDlg.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) AboutDlg.h -o moc_AboutDlg.cpp

moc_FindDlg.cpp: FindDlg.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) FindDlg.h -o moc_FindDlg.cpp

moc_settingsdlg.cpp: settings.h \
		settingsdlg.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) settingsdlg.h -o moc_settingsdlg.cpp

moc_newprojectdlg.cpp: newprojectdlg.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) newprojectdlg.h -o moc_newprojectdlg.cpp

compiler_rcc_make_all: qrc_Icons.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_Icons.cpp
qrc_Icons.cpp: Icons.qrc \
		lua-editor_en.qm \
		lua-editor_de.qm \
		icons/document-open.svg \
		icons/document-new.svg \
		icons/media-playback-start.svg \
		icons/document-save.svg \
		icons/accessories-text-editor.svg
	/usr/lib/x86_64-linux-gnu/qt4/bin/rcc -name Icons Icons.qrc -o qrc_Icons.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h ui_newfiledlg.h ui_aboutdlg.h ui_finddlg.h ui_settingsdlg.h ui_newprojectdlg.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h ui_newfiledlg.h ui_aboutdlg.h ui_finddlg.h ui_settingsdlg.h ui_newprojectdlg.h
ui_mainwindow.h: mainwindow.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic mainwindow.ui -o ui_mainwindow.h

ui_newfiledlg.h: newfiledlg.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic newfiledlg.ui -o ui_newfiledlg.h

ui_aboutdlg.h: aboutdlg.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic aboutdlg.ui -o ui_aboutdlg.h

ui_finddlg.h: finddlg.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic finddlg.ui -o ui_finddlg.h

ui_settingsdlg.h: settingsdlg.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic settingsdlg.ui -o ui_settingsdlg.h

ui_newprojectdlg.h: newprojectdlg.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic newprojectdlg.ui -o ui_newprojectdlg.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

main.o: main.cpp mainwindow.h \
		LuaHighlighter.h \
		settings.h \
		project.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		LuaHighlighter.h \
		settings.h \
		project.h \
		ui_mainwindow.h \
		newfiledlg.h \
		AboutDlg.h \
		FindDlg.h \
		settingsdlg.h \
		newprojectdlg.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

LuaHighlighter.o: LuaHighlighter.cpp LuaHighlighter.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o LuaHighlighter.o LuaHighlighter.cpp

newfiledlg.o: newfiledlg.cpp newfiledlg.h \
		ui_newfiledlg.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o newfiledlg.o newfiledlg.cpp

AboutDlg.o: AboutDlg.cpp AboutDlg.h \
		ui_aboutdlg.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o AboutDlg.o AboutDlg.cpp

FindDlg.o: FindDlg.cpp FindDlg.h \
		ui_finddlg.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o FindDlg.o FindDlg.cpp

settings.o: settings.cpp settings.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o settings.o settings.cpp

settingsdlg.o: settingsdlg.cpp settingsdlg.h \
		settings.h \
		ui_settingsdlg.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o settingsdlg.o settingsdlg.cpp

newprojectdlg.o: newprojectdlg.cpp newprojectdlg.h \
		ui_newprojectdlg.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o newprojectdlg.o newprojectdlg.cpp

project.o: project.cpp project.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o project.o project.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_LuaHighlighter.o: moc_LuaHighlighter.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_LuaHighlighter.o moc_LuaHighlighter.cpp

moc_newfiledlg.o: moc_newfiledlg.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_newfiledlg.o moc_newfiledlg.cpp

moc_AboutDlg.o: moc_AboutDlg.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_AboutDlg.o moc_AboutDlg.cpp

moc_FindDlg.o: moc_FindDlg.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_FindDlg.o moc_FindDlg.cpp

moc_settingsdlg.o: moc_settingsdlg.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_settingsdlg.o moc_settingsdlg.cpp

moc_newprojectdlg.o: moc_newprojectdlg.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_newprojectdlg.o moc_newprojectdlg.cpp

qrc_Icons.o: qrc_Icons.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_Icons.o qrc_Icons.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

