#include "newfiledlg.h"
#include "ui_newfiledlg.h"
#include <QFileDialog>

NewFileDlg::NewFileDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFileDlg)
{
    ui->setupUi(this);
}

NewFileDlg::~NewFileDlg()
{
    delete ui;
}

void NewFileDlg::pathButtonClick()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open File"), "", tr("Files (*.*)"));
    ui->pathEdit->setText(fileName);

    path = fileName;
}
