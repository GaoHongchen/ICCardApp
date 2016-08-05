#ifndef SELECTSYSSWITCHDLG_H
#define SELECTSYSSWITCHDLG_H

#include <QDialog>

namespace Ui {
class SelectSysSwitchDlg;
}

class SelectSysSwitchDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SelectSysSwitchDlg(QWidget *parent = 0);
    ~SelectSysSwitchDlg();

private slots:
    void on_pushBtnSel_clicked();

    void on_pushBtnCancel_clicked();

private:
    Ui::SelectSysSwitchDlg *ui;
};

#endif // SELECTSYSSWITCHDLG_H
