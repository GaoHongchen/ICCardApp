#ifndef ADDCHARGESTDDLG_H
#define ADDCHARGESTDDLG_H

#include <QDialog>

namespace Ui {
class AddChargeStdDlg;
}

class AddChargeStdDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddChargeStdDlg(QWidget *parent = 0);
    ~AddChargeStdDlg();

public:
    std::vector<QString> arrValues;//nFloorDown nFloorUp nFeePerTime
    void ModifyChargeStd(std::vector<QString> arrValues);

private slots:
    void on_pushBtnOK_clicked();

    void on_pushBtnCancel_clicked();

private:
    Ui::AddChargeStdDlg *ui;
};

#endif // ADDCHARGESTDDLG_H
