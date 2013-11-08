#include "settingsdlg.h"
#include "ui_settingsdlg.h"
#include <QFileDialog>

SettingsDlg::SettingsDlg(QWidget *parent, Settings settings) :
    QDialog(parent),
    ui(new Ui::SettingsDlg)
{
    ui->setupUi(this);

    ui->pathEdit->setText(settings.getLuaInterpreter());

    path = settings.getLuaInterpreter();
    arguments = settings.getLuaArgs();

    ui->argsEdit->setText(arguments);
}

SettingsDlg::~SettingsDlg()
{
    delete ui;
}

void SettingsDlg::pathButtonClick()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open File"), "", tr("Files (*.*)"));
    ui->pathEdit->setText(fileName);

    path = fileName;
}

void SettingsDlg::pathChanged()
{
    path = ui->pathEdit->displayText();
}

void SettingsDlg::argsChanged()
{
    arguments = ui->argsEdit->displayText();
}
