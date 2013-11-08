#include "newprojectdlg.h"
#include "ui_newprojectdlg.h"
#include <QFileDialog>

NewProjectDlg::NewProjectDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectDlg)
{
    ui->setupUi(this);
}

NewProjectDlg::~NewProjectDlg()
{
    delete ui;
}

void NewProjectDlg::accept()
{
    name = ui->nameEdit->displayText();
    QDialog::accept();
}

void NewProjectDlg::pathButtonClick()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open File"), "", tr("Files (*.luap)"));

    if(!fileName.endsWith(".luap"))
        fileName += ".luap";

    ui->pathEdit->setText(fileName);
    path = fileName;
}

void NewProjectDlg::pathChanged()
{
    path = ui->pathEdit->displayText();

    if(!path.endsWith(".luap"))
        path += ".luap";
}
