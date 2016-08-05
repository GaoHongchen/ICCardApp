#include "addchargestddlg.h"
#include "ui_addchargestddlg.h"

AddChargeStdDlg::AddChargeStdDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddChargeStdDlg)
{
    ui->setupUi(this);
}

AddChargeStdDlg::~AddChargeStdDlg()
{
    delete ui;
}

void AddChargeStdDlg::ModifyChargeStd(std::vector<QString> arrValues)
{
    ui->lineEditFloorDown->setText(QString(arrValues[0]));
    ui->lineEditFloorUp->setText(QString(arrValues[1]));
    ui->lineEditFee->setText(QString(arrValues[2]));
}

void AddChargeStdDlg::on_pushBtnOK_clicked()
{
    std::vector<QString>(arrValues).swap(arrValues);
    //arrValues.swap(std::vector<QString>());
    arrValues.push_back(ui->lineEditFloorDown->text());
    arrValues.push_back(ui->lineEditFloorUp->text());
    arrValues.push_back(ui->lineEditFee->text());

    accept();
}

void AddChargeStdDlg::on_pushBtnCancel_clicked()
{
    reject();
}
