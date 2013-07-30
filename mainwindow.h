#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "LuaHighlighter.h"
#include <map>

extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void changeSelectedFile(int idx);
    void updateEditorText();

private:
    Ui::MainWindow *ui;
    LuaHighlighter syntaxHighlighter;
    int numOpenFiles;

    std::map<QString, QString> fileContents;

    lua_State* luaState;

    void updateCache();
};

#endif // MAINWINDOW_H
