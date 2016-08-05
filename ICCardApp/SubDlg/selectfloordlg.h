#ifndef SELECTFLOORDLG_H
#define SELECTFLOORDLG_H

#include <utility>

#include <QDialog>
#include <QPushButton>
#include <QButtonGroup>
#include <QGridLayout>

namespace Ui {
class SelectFloorDlg;
}

class SelectFloorDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SelectFloorDlg(QWidget *parent = 0);
    ~SelectFloorDlg();

public:
    void ModifyFloorInfo(std::vector<QString> arrValues);

public:
    std::map<int,QString> mapFloorsA;

private slots:
    void on_pushBtnOK_clicked();
    void on_pushBtnCancel_clicked();
    void pushBtnsA_clicked(int index);

    void on_checkBoxSelectAllA_clicked();

private:
    bool isClicked[48];
    int nTotalFloorNum;

private:
    QButtonGroup *grpBtnsA;
    QPushButton *pushBtnsA;
    QPushButton *pushBtnsB;

private:
    Ui::SelectFloorDlg *ui;
};

#endif // SELECTFLOORDLG_H
