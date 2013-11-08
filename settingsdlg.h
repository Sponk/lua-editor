#ifndef SETTINGSDLG_H
#define SETTINGSDLG_H

#include <QDialog>
#include "settings.h"

namespace Ui {
class SettingsDlg;
}

class SettingsDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingsDlg(QWidget *parent, Settings settings);
    ~SettingsDlg();
    
public slots:
    void pathButtonClick();
    void pathChanged();
    void argsChanged();

private:
    Ui::SettingsDlg *ui;

public:
    QString path;
    QString arguments;
};

#endif // SETTINGSDLG_H
