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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QTranslator>
#include "newfiledlg.h"
#include "AboutDlg.h"
#include "FindDlg.h"
#include "settingsdlg.h"
#include "newprojectdlg.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    syntaxHighlighter = new LuaHighlighter(this);
    currentTranslation = new QTranslator();
    currentTranslation->load("lua-editor_en", ":/translations");

    app->installTranslator(currentTranslation);

    ui->setupUi(this);

    ui->actionEnglish->setChecked(true);

    numOpenFiles = 0;
    currentTranslation = NULL;

    luaState = luaL_newstate();
    luaopen_base(luaState);

    connect(&luaInterpreter, SIGNAL(readyReadStandardOutput()),this,SLOT(readStdOutput()));
    connect(&luaInterpreter, SIGNAL(error(QProcess::ProcessError)),this,SLOT(readError()));

    luaInterpreter.setProcessChannelMode(QProcess::MergedChannels);
}

MainWindow::~MainWindow()
{
    lua_close(luaState);
    delete syntaxHighlighter;
    delete ui;    
}


void MainWindow::readStdOutput()
{
    ui->outputEdit->append(luaInterpreter.readAllStandardOutput());
}

void MainWindow::readError()
{

}

void MainWindow::onTabClose(int idx)
{
    QString title = ui->sourceTabs->tabText(idx);
    // qDebug() << "Closing: " << title;

    openFiles.erase(title);
    ui->sourceTabs->removeTab(idx);
}

void MainWindow::changeSelectedFile()
{
    syntaxHighlighter->setDocument(currentTab()->document());
}

QTextEdit* MainWindow::addTab(QString name)
{
    QTextEdit* editor = new QTextEdit();
    editor->setFont(QFont("Courier", 10));

    connect(editor, SIGNAL(cursorPositionChanged()),this,SLOT(cursorPositionChanged()));
    connect(editor, SIGNAL(textChanged()),this,SLOT(updateEditorText()));

    ui->sourceTabs->addTab(editor, name);

    return editor;
}

QTextEdit* MainWindow::currentTab()
{
    return (QTextEdit*) ui->sourceTabs->currentWidget();
}

void MainWindow::newFile()
{
    NewFileDlg dlg(this);
    int result = dlg.exec();

    if(result == QDialog::Rejected)
    {
        return;
    }

    QString name = dlg.path.toStdString().substr(dlg.path.lastIndexOf("/") + 1).c_str();

    QTextEdit* editor = addTab(name);
    editor->setText("");

    openFiles[name] = dlg.path;

    numOpenFiles++;
}

void MainWindow::showConfigurationDialog()
{
    SettingsDlg dlg(this, this->settings);
    if(dlg.exec() == QDialog::Rejected)
        return;

    this->settings.setLuaInterpreter(dlg.path);
    this->settings.setLuaArgs(dlg.arguments);
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*)"));

    if(fileName.isEmpty())
        return;

    openFile(fileName);
}

void MainWindow::saveFile()
{
    if(numOpenFiles == 0)
        return;

    QString name = ui->sourceTabs->tabText(ui->sourceTabs->currentIndex());
    QString path = openFiles[name];

    if(path.isEmpty())
        return;

    // qDebug(QString("Saving to " + path).toAscii());
    saveFile(path, currentTab()->toPlainText());
}

void MainWindow::saveFile(QString path, QString content)
{
    QFile file(path);

    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(NULL, tr("Error"), file.errorString());
        return;
    }

    QTextStream stream(&file);
    stream << content;

    file.close();
}

void MainWindow::openFile(QString path)
{
    QFile file(path);

    // Funktioniert trotz '/' auch für Windows
    QString name = path.toStdString().substr(path.lastIndexOf("/") + 1).c_str();

    if(openFiles[name] != "")
    {
        QMessageBox::information(NULL, tr("Error"), tr("A file with this name is already open!"));
        return;
    }

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(NULL, tr("Error"), file.errorString());
        return;
    }

    QTextEdit* editor = addTab(name);
    ui->sourceTabs->setCurrentWidget(editor);

    QTextStream in(&file);
    QString content;

    while(!in.atEnd())
    {
        QString line = in.readLine();
        content.append(line + "\n");
    }

    file.close();
    editor->setText(content);

    openFiles[name] = path;
    // qDebug(QString("Opening file in tab: " + ui->sourceTabs->tabText(ui->sourceTabs->currentIndex())).toAscii());

    numOpenFiles++;
}

void MainWindow::saveFileAs()
{
    if(numOpenFiles <= 0)
        return;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Files (*)"));

    if(fileName == "")
        return;

    saveFile(fileName, currentTab()->toPlainText());
    openFile(fileName);
}

void MainWindow::updateEditorText()
{
    if(numOpenFiles == 0)
        return;

    QString content = ((QTextEdit*)ui->sourceTabs->currentWidget())->toPlainText();

    int error = luaL_loadbuffer(luaState, content.toLatin1(), content.length(), "line");

    if(error)
    {
        ui->errorEdit->setText(lua_tostring(luaState, -1));
        lua_pop(luaState, 1);
    }
    else
    {
        ui->errorEdit->clear();
    }
}

void MainWindow::cursorPositionChanged()
{
    QTextEdit* editor = currentTab();

    int pos = editor->textCursor().blockNumber() + 1;
    QString message = tr("Line: ") + QString("%1").arg(pos);

    pos = editor->textCursor().columnNumber() + 1;
    message += " " + tr("Column: ") + QString("%1").arg(pos);

    ui->statusBar->showMessage(message);
}

void MainWindow::germanSelected(bool status)
{
    ui->actionEnglish->setChecked(!status);

    if(status)
    {
        app->removeTranslator(currentTranslation);

        if(currentTranslation != NULL)
            delete currentTranslation;

        currentTranslation = new QTranslator();
        currentTranslation->load("lua-editor_de", ":/translations");

        settings.setLanguage("lua-editor_de");

        app->installTranslator(currentTranslation);
        ui->retranslateUi(this);
    }
}

void MainWindow::englishSelected(bool status)
{
    ui->actionGerman->setChecked(!status);

    if(status)
    {
        if(currentTranslation != NULL)
            delete currentTranslation;

        currentTranslation = new QTranslator();
        currentTranslation->load("lua-editor_en", ":/translations");

        settings.setLanguage("lua-editor_en");

        app->installTranslator(currentTranslation);
        ui->retranslateUi(this);
    }
}

void MainWindow::about()
{
    AboutDlg dlg(this);
    dlg.exec();
}

void MainWindow::find()
{
    if(numOpenFiles == 0)
        return;

    FindDlg dlg(this);

    if(dlg.exec())
    {
        QTextEdit* editor = currentTab();
        editor->find(dlg.searchTerm, QTextDocument::FindCaseSensitively);
    }
}

void MainWindow::quit()
{
    settings.save();
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
    quit();
    exit(0);
}

void MainWindow::loadSettings()
{
    QString path;

#ifndef WIN32
    path = QDir::homePath() + "/.lua-editor.conf";
#else
    path = QDir::homePath() + "\\.lua-editor.conf";
#endif

    if(!settings.load(path))
    {
        settings.save();
        return;
    }

    if(settings.getLanguage() == "lua-editor_en")
        englishSelected(true);
    else if(settings.getLanguage() == "lua-editor_de")
        germanSelected(true);
}

void MainWindow::runScript()
{
    if(settings.getLuaInterpreter() == "")
    {
        QMessageBox::information(NULL, tr("Error"), tr("No LUA interpreter set!"));
        return;
    }

    QStringList args;

    args.append(settings.getLuaArgs().split(" "));

    luaInterpreter.setWorkingDirectory(QDir::currentPath());
    luaInterpreter.start(settings.getLuaInterpreter(), args);

    ui->outputTabs->setCurrentIndex(1);
    ui->outputEdit->setText("");
}

void MainWindow::newProject()
{
    NewProjectDlg dlg(this);
    if(dlg.exec() != QDialog::Accepted)
    {
        return;
    }

    project.setName(dlg.name);
    project.setPath(dlg.path);

    // TODO: Gesondert eingeben?
    project.setWorkingDir(".");

    project.save();

#ifdef WIN32
    QDir::setCurrent(dlg.path.left(dlg.path.lastIndexOf("\\")));
#else
    QDir::setCurrent(dlg.path.left(dlg.path.lastIndexOf("/")));
#endif
}

void MainWindow::openProject()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.luap)"));
    project.load(fileName);

    // Funktioniert auch auf Windows trotz '/'
    QDir::setCurrent(fileName.left(fileName.lastIndexOf("/")));
}
