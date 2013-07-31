#include "FindDlg.h"
#include "ui_finddlg.h"

FindDlg::FindDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDlg)
{
    ui->setupUi(this);
}

FindDlg::~FindDlg()
{
    delete ui;
}

void FindDlg::accept()
{
    searchTerm = ui->searchEdit->displayText();

    this->done(1);
    this->close();
}
