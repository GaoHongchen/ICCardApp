#include "addusrdlg.h"
#include "ui_addusrdlg.h"

AddUsrDlg::AddUsrDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUsrDlg)
{
    ui->setupUi(this);
}

AddUsrDlg::~AddUsrDlg()
{
    delete ui;
}

void AddUsrDlg::ModifyUsrInfos(std::vector<QString> arrValues)
{
    ui->lineEditUsrName->setText(arrValues[0]);

    ui->lineEditChargeUpLimit->setText(arrValues[2]);
}

void AddUsrDlg::on_pushBtnOK_clicked()
{
    //用户名
    QString strUsrName = ui->lineEditUsrName->text();
    if(strUsrName.isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入用户名！",QMessageBox::Yes);
        return;
    }
    arrValues.push_back(strUsrName);

    //用户级别
    QString strUsrLevel = ui->comboBoxUsrLevel->currentText();
    if(strUsrLevel.isEmpty())
    {
        QMessageBox::warning(this,"警告","请选择用户级别！",QMessageBox::Yes);
        return;
    }
    arrValues.push_back(strUsrLevel);

    //密码
    QString strPwd = ui->lineEditPassWord->text();
    if(strPwd.isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入密码！",QMessageBox::Yes);
        return;
    }
    QString strPwdRe = ui->lineEditPassWordRepeat->text();
    if(strPwd == strPwdRe)
    {
        arrValues.push_back(strPwd);
    }
    else
    {
        QMessageBox::warning(this,"警告","两次密码输入不一致！",QMessageBox::Yes);
        return;
    }

    //充值上限
    QString strChargeUpLimit = ui->lineEditChargeUpLimit->text();
    arrValues.push_back(strChargeUpLimit);
    if(strChargeUpLimit.isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入充值上限！",QMessageBox::Yes);
        return;
    }

    //密码问题
    QString strPWQuestion = ui->comboBoxPassWordProblem->currentText();
    arrValues.push_back(strPWQuestion);

    //密码问题答案
    QString strPWQuestionAnswer = ui->lineEditPassWordAnswer->text();
    arrValues.push_back(strPWQuestionAnswer);

    accept();
}

void AddUsrDlg::on_pushBtnCancel_clicked()
{
    reject();
}
