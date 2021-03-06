/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
 * der GNU General Public License, wie von der Free Software Foundation,
 * Version 3 der Lizenz oder (nach Ihrer Option) jeder späteren
 * veröffentlichten Version, weiterverbreiten und/oder modifizieren.
 *
 * Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
 * OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
 * Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
 * Siehe die GNU General Public License für weitere Details.
 *
 * Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
 * Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QCloseEvent>
#include "LuaHighlighter.h"
#include <map>
#include <QTranslator>
#include <QProcess>
#include <QTextEdit>
#include "settings.h"
#include "project.h"

extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

// #include <lua.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loadSettings();
    void openFile(QString path);

    QApplication* app;
    
public slots:
    void closeEvent(QCloseEvent* event);

    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void updateEditorText();
    void cursorPositionChanged();
    void germanSelected(bool status);
    void englishSelected(bool status);
    void about();
    void find();
    void quit();
    void showConfigurationDialog();
    void runScript();
    void newProject();
    void openProject();
    void changeSelectedFile();

    void readStdOutput();
    void readError();

    void onTabClose(int idx);

private:

    Ui::MainWindow *ui;
    LuaHighlighter* syntaxHighlighter;
    int numOpenFiles;

    std::map<QString, QString> openFiles;

    lua_State* luaState;

    QTranslator* currentTranslation;
    Settings settings;

    void saveFile(QString path, QString content);
    QTextEdit* addTab(QString name);
    QTextEdit* currentTab();

    QProcess luaInterpreter;
    Project project;
};

#endif // MAINWINDOW_H
