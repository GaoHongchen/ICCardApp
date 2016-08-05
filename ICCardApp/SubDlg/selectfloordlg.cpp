#include "selectfloordlg.h"
#include "ui_selectfloordlg.h"

SelectFloorDlg::SelectFloorDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectFloorDlg)
{
    ui->setupUi(this);

    //A门
    grpBtnsA = new QButtonGroup;
    connect(grpBtnsA,SIGNAL(buttonClicked(int)),this,SLOT(pushBtnsA_clicked(int)));
    pushBtnsA = new QPushButton[48];
    QGridLayout *layoutGridFloorsA = new QGridLayout;
    for(int i=0;i<48;i++)
    {
        pushBtnsA[i].setText(QString::number(1+i));
        layoutGridFloorsA->addWidget(&pushBtnsA[i],i/12,i%12);

        grpBtnsA->addButton(&pushBtnsA[i],i);
    }
    ui->groupBoxFloorsA->setLayout(layoutGridFloorsA);

    //B门
    pushBtnsB=new QPushButton[48];
    QGridLayout *layoutGridFloorsB = new QGridLayout;
    for(int i=0;i<48;i++)
    {
        pushBtnsB[i].setText(QString::number(1+i));
        layoutGridFloorsB->addWidget(&pushBtnsB[i],i/12,i%12);
    }
    ui->groupBoxFloorsB->setLayout(layoutGridFloorsB);
}

SelectFloorDlg::~SelectFloorDlg()
{
    delete ui;
    delete[] pushBtnsA;
    delete[] pushBtnsB;
    delete grpBtnsA;

    mapFloorsA.clear();
}

void SelectFloorDlg::ModifyFloorInfo(std::vector<QString> arrValues)
{
    ui->labelLiftName->setText(QString(arrValues[0]));
    ui->labelLiftType->setText(QString(arrValues[1]));
    ui->labelTotalFloorNum->setText(QString(arrValues[2]));
    ui->labelStartFloor->setText(QString(arrValues[3]));

    nTotalFloorNum = QString(arrValues[2]).toInt();
    int nStartFloor = QString(arrValues[3]).toInt();

    for(int i=0;i<48;i++)
    {
        if(i < nTotalFloorNum)
        {
            pushBtnsA[i].show();

            pushBtnsA[i].setText(QString::number(nStartFloor+i));
        }
        else
        {
            pushBtnsA[i].hide();
        }
    }
}

void SelectFloorDlg::pushBtnsA_clicked(int index)
{
    if(!isClicked[index])
    {
        pushBtnsA[index].setStyleSheet("background-color:#FFFF00");
        isClicked[index] = true;
        mapFloorsA.insert(std::make_pair(index,pushBtnsA[index].text()));
    }
    else
    {
        pushBtnsA[index].setStyleSheet("");//恢复按钮原色
        isClicked[index] = false;
        mapFloorsA.erase(index);
    }

    bool isClickedAll = true;
    for(int i=0;i<nTotalFloorNum;i++)
    {
        if(isClicked[i] == false)
        {
            isClickedAll = false;
        }
    }
    ui->checkBoxSelectAllA->setChecked(isClickedAll);
}

void SelectFloorDlg::on_pushBtnOK_clicked()
{
    accept();
}

void SelectFloorDlg::on_pushBtnCancel_clicked()
{
    reject();
}

void SelectFloorDlg::on_checkBoxSelectAllA_clicked()
{
    if(ui->checkBoxSelectAllA->isChecked())
    {
        for(int i=0;i<nTotalFloorNum;i++)
        {
            pushBtnsA[i].setStyleSheet("background-color:#FFFF00");
            isClicked[i] = true;
            mapFloorsA.insert(std::make_pair(i,pushBtnsA[i].text()));
        }
    }
    else
    {
        for(int i=0;i<nTotalFloorNum;i++)
        {
            pushBtnsA[i].setStyleSheet("");
            isClicked[i] = false;
        }
        mapFloorsA.clear();
    }

}
