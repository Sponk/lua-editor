#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    syntaxHighlighter.setDocument(ui->sourceEdit->document());
    numOpenFiles = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile()
{
    QMessageBox::information(NULL, tr("Sorry"), tr("Sorry, 'New' is not implemented yet"));
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)"));
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
    item->setData(1001, content);
    item->setData(1002, fileName);

    ui->openFilesList->addItem(item);
    ui->sourceEdit->setText(content);
    ui->openFilesList->setCurrentRow(index);

    numOpenFiles++;
}

void MainWindow::saveFile()
{
    QMessageBox::information(NULL, tr("Sorry"), tr("Sorry, 'Save' is not implemented yet"));
}

void MainWindow::saveFileAs()
{
    QMessageBox::information(NULL, tr("Sorry"), tr("Sorry, 'Save file as...'' is not implemented yet"));
}

void MainWindow::changeSelectedFile(int idx)
{
    QListWidgetItem* item = ui->openFilesList->item(idx);
    ui->sourceEdit->setText(item->data(1001).toString());
    this->setWindowTitle(item->data(1002).toString());
}
