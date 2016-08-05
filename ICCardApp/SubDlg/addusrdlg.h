#ifndef ADDUSRDLG_H
#define ADDUSRDLG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class AddUsrDlg;
}

class AddUsrDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddUsrDlg(QWidget *parent = 0);
    ~AddUsrDlg();

public:
    std::vector<QString> arrValues;
    void ModifyUsrInfos(std::vector<QString> arrValues);

private slots:
    void on_pushBtnOK_clicked();

    void on_pushBtnCancel_clicked();

private:
    Ui::AddUsrDlg *ui;
};

#endif // ADDUSRDLG_H
