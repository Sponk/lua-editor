#ifndef NEWPROJECTDLG_H
#define NEWPROJECTDLG_H

#include <QDialog>

namespace Ui {
class NewProjectDlg;
}

class NewProjectDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewProjectDlg(QWidget *parent = 0);
    ~NewProjectDlg();

public slots:
    void pathButtonClick();
    void accept();
    void pathChanged();
    
private:
    Ui::NewProjectDlg *ui;

public:
    QString path;
    QString name;
};

#endif // NEWPROJECTDLG_H
