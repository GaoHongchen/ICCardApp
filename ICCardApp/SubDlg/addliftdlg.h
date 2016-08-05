#ifndef ADDLIFTDLG_H
#define ADDLIFTDLG_H

#include <QDialog>

namespace Ui {
class AddLiftDlg;
}

class AddLiftDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddLiftDlg(QWidget *parent = 0);
    ~AddLiftDlg();

public:
    //nLiftID strLiftName nTotalFloorNum nStartFloor strLiftType
    //0 nLiftNum strComment
    std::vector<QString> arrValues;
    void ModifyLiftInfo(std::vector<QString> arrValues);

public:
    Ui::AddLiftDlg *ui;

private slots:
    void on_pushBtnOK_clicked();
    void on_pushBtnCancel_clicked();
};

#endif // ADDLIFTDLG_H
