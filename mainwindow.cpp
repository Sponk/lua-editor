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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    currentTranslation = new QTranslator();
    currentTranslation->load("lua-editor_en", ":/translations");

    app->installTranslator(currentTranslation);

    ui->setupUi(this);

    ui->actionEnglish->setChecked(true);

    syntaxHighlighter.setDocument(ui->sourceEdit->document());
    numOpenFiles = 0;
    currentTranslation = NULL;

    luaState = luaL_newstate();
    luaopen_base(luaState);
}

MainWindow::~MainWindow()
{
    lua_close(luaState);
    delete ui;    
}

void MainWindow::newFile()
{
    NewFileDlg dlg;
    int result = dlg.exec();

    if(!result)
        return;

#ifndef WIN32
    QString name = dlg.path.toStdString().substr(dlg.path.lastIndexOf("/") + 1).c_str();
#else
    QString name = dlg.path.toStdString().substr(dlg.path.lastIndexOf("\\") + 1).c_str();
#endif

    ui->sourceEdit->setEnabled(true);

    QListWidgetItem* item = new QListWidgetItem();
    item->setText(name);
    item->setData(1002, dlg.path);

    ui->openFilesList->addItem(item);
    ui->openFilesList->setCurrentRow(numOpenFiles);
    ui->sourceEdit->setText("");

    numOpenFiles++;
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*)"));

    openFile(fileName);
}

void MainWindow::saveFile()
{
    if(numOpenFiles == 0)
        return;

    updateCache();

    QListWidgetItem* item = ui->openFilesList->selectedItems()[0];
    QString path = item->data(1002).toString();

    if(path.isEmpty())
        return;

    saveFile(path, fileContents[item->data(1002).toString()]);
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
    int index = numOpenFiles;

#ifndef WIN32
    QString name = path.toStdString().substr(path.lastIndexOf("/") + 1).c_str();
#else
    QString name = path.toStdString().substr(path.lastIndexOf("\\") + 1).c_str();
#endif

    if(ui->openFilesList->findItems(name, Qt::MatchCaseSensitive).size() != 0)
    {
        QMessageBox::information(NULL, tr("Error"), tr("A file with this name is already open!"));
        return;
    }

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(NULL, tr("Error"), file.errorString());
        return;
    }

    ui->sourceEdit->setEnabled(true);

    QTextStream in(&file);
    QString content;

    while(!in.atEnd())
    {
        QString line = in.readLine();
        content.append(line + "\n");
    }

    file.close();

    QListWidgetItem* item = new QListWidgetItem();
    item->setText(name);

    fileContents[path] = content;
    item->setData(1002, path);

    ui->openFilesList->addItem(item);
    ui->openFilesList->setCurrentRow(index);
    ui->sourceEdit->setText(content);

    numOpenFiles++;
    updateEditorText();
}

void MainWindow::saveFileAs()
{
    if(numOpenFiles <= 0)
        return;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Files (*)"));
    QListWidgetItem* item = ui->openFilesList->selectedItems()[0];

    if(fileName == "")
        return;

    saveFile(fileName, fileContents[item->data(1002).toString()]);
    openFile(fileName);
}

void MainWindow::changeSelectedFile(int idx)
{
    if(numOpenFiles > 1)
        updateCache();

    QListWidgetItem* item = ui->openFilesList->item(idx);
    QString file = item->data(1002).toString();
    QString content = fileContents[file];

    ui->sourceEdit->setText(content);
    this->setWindowTitle(file);
}

void MainWindow::updateCache()
{
    QListWidgetItem* item = ui->openFilesList->selectedItems()[0];
    fileContents[item->data(1002).toString()] = ui->sourceEdit->toPlainText();
}

void MainWindow::updateEditorText()
{
    if(numOpenFiles == 0)
        return;

    QString content = ui->sourceEdit->toPlainText();

    int error = luaL_loadbuffer(luaState, content.toAscii(), content.length(), "line");

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
    int pos = ui->sourceEdit->textCursor().blockNumber() + 1;
    QString message = tr("Line: ") + QString("%1").arg(pos);

    pos = ui->sourceEdit->textCursor().columnNumber() + 1;
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
    AboutDlg dlg;
    dlg.exec();
}

void MainWindow::find()
{
    if(numOpenFiles == 0)
        return;

    FindDlg dlg;

    if(dlg.exec())
    {
        ui->sourceEdit->find(dlg.searchTerm, QTextDocument::FindCaseSensitively);
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
