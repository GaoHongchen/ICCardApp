#include "addliftdlg.h"
#include "ui_addliftdlg.h"

AddLiftDlg::AddLiftDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLiftDlg)
{
    ui->setupUi(this);

    ui->lineEditLiftID->setValidator(new QIntValidator(1,256));
}

AddLiftDlg::~AddLiftDlg()
{
    delete ui;
}

void AddLiftDlg::ModifyLiftInfo(std::vector<QString> arrValues)
{
    ui->lineEditLiftID->setText(QString(arrValues[0]));
    ui->lineEditLiftName->setText(QString(arrValues[1]));
    if(QString(arrValues[2]) == "普通电梯")
    {
        ui->radioButtonCommonLift->setChecked(true);
    }
    if(QString(arrValues[2]) == "贯通门电梯")
    {
        ui->radioButtonOppositeDoorLift->setChecked(true);
    }
    ui->lineEditTotalFloorNum->setText(QString(arrValues[3]));
    int nStartFloor = QString(arrValues[4]).toInt();
    ui->lineEditStartFloor->setText(QString::number(abs(nStartFloor)));
    if(nStartFloor > 0)
    {
        ui->comboBoxGndUD->setCurrentText("地上");
    }
    else
    {
        ui->comboBoxGndUD->setCurrentText("地下");
    }

    ui->comboBoxLiftNum->setCurrentText(QString(arrValues[6]));
    ui->lineEditComment->setText(QString(arrValues[7]));
}

void AddLiftDlg::on_pushBtnOK_clicked()
{
    std::vector<QString>(arrValues).swap(arrValues);

    arrValues.push_back(ui->lineEditLiftID->text());
    arrValues.push_back(ui->lineEditLiftName->text());
    if(ui->radioButtonCommonLift->isChecked())
    {
        arrValues.push_back("普通电梯");
    }
    if(ui->radioButtonOppositeDoorLift->isChecked())
    {
        arrValues.push_back("贯通门电梯");
    }
    arrValues.push_back(ui->lineEditTotalFloorNum->text());
    if(ui->comboBoxGndUD->currentIndex()==0)//地上
    {
        arrValues.push_back(ui->lineEditStartFloor->text());
    }
    if(ui->comboBoxGndUD->currentIndex()==1)//地下
    {
        int nStartFloor = 0 - ui->lineEditStartFloor->text().toInt();
        arrValues.push_back(QString::number(nStartFloor));

    }
    arrValues.push_back("0");
    arrValues.push_back(ui->comboBoxLiftNum->currentText());
    arrValues.push_back(ui->lineEditComment->text());

    accept();
}

void AddLiftDlg::on_pushBtnCancel_clicked()
{
    reject();
}
