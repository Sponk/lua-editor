#ifndef NEWFILEDLG_H
#define NEWFILEDLG_H

#include <QDialog>

namespace Ui {
class NewFileDlg;
}

class NewFileDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewFileDlg(QWidget *parent = 0);
    ~NewFileDlg();
    
public slots:
    void pathButtonClick();

private:
    Ui::NewFileDlg *ui;

public:
    QString path;
};

#endif // NEWFILEDLG_H
