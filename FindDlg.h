#ifndef FINDDLG_H
#define FINDDLG_H

#include <QDialog>

namespace Ui {
class FindDlg;
}

class FindDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit FindDlg(QWidget *parent = 0);
    ~FindDlg();

public slots:
    void accept();
    
private:
    Ui::FindDlg *ui;

public:
    QString searchTerm;
};

#endif // FINDDLG_H
