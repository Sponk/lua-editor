#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QTranslator>
#include "newfiledlg.h"
#include "AboutDlg.h"

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
    delete currentTranslation;
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
    QFile file(fileName);
    int index = numOpenFiles;

#ifndef WIN32
    QString name = fileName.toStdString().substr(fileName.lastIndexOf("/") + 1).c_str();
#else
    QString name = fileName.toStdString().substr(fileName.lastIndexOf("\\") + 1).c_str();
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

    fileContents[fileName] = content;
    item->setData(1002, fileName);

    ui->openFilesList->addItem(item);
    ui->openFilesList->setCurrentRow(index);
    ui->sourceEdit->setText(content);

    numOpenFiles++;
    updateEditorText();
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

    QFile file(path);

    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(NULL, tr("Error"), file.errorString());
        return;
    }

    QTextStream stream(&file);
    stream << fileContents[item->data(1002).toString()];

    file.close();
}

void MainWindow::saveFileAs()
{
    QMessageBox::information(NULL, tr("Sorry"), tr("Sorry, 'Save file as...'' is not implemented yet"));
}

void MainWindow::changeSelectedFile(int idx)
{
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

        app->installTranslator(currentTranslation);
        ui->retranslateUi(this);
    }
}

void MainWindow::about()
{
    AboutDlg dlg;
    dlg.exec();
}
