#include "tabwidget_systemsetting.h"
#include "ui_tabwidget_systemsetting.h"

TabWidget_SystemSetting::TabWidget_SystemSetting(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TabWidget_SystemSetting)
{
    ui->setupUi(this);

    std::vector<QString> arrTableFields;
    arrTableFields.push_back("用户名");
    arrTableFields.push_back("密码");
    arrTableFields.push_back("充值上限");
    arrTableFields.push_back("密码问题");
    arrTableFields.push_back("密码问题答案");
    modelUsrInfo = new SqlDBModel("tableUserInfo",arrTableFields);
    UpdateTableViewUserInfo();
}

TabWidget_SystemSetting::~TabWidget_SystemSetting()
{
    delete ui;
    delete modelUsrInfo;
}

void TabWidget_SystemSetting::UpdateTableViewUserInfo()
{
    QSqlQueryModel *modelQuery=new QSqlQueryModel;
    modelQuery->setQuery("select 用户名,用户级别,充值上限 from tableUserInfo");
    ui->tableViewUserInfo->setModel(modelQuery);
    //delete modelQuery;
}


void TabWidget_SystemSetting::on_usrPushBtnAddUsr_clicked()
{
    AddUsrDlg dlgAddUsr;
    dlgAddUsr.show();
    if(dlgAddUsr.exec() == QDialog::Accepted)
    {
        modelUsrInfo->addData(dlgAddUsr.arrValues);
        UpdateTableViewUserInfo();
    }
}

void TabWidget_SystemSetting::on_usrPushBtnChange_clicked()
{
    int curRow = ui->tableViewUserInfo->currentIndex().row();
    if(curRow<0)
    {
        QMessageBox::warning(this,"警告","请先选择用户！",QMessageBox::Yes);
        return;
    }
    std::vector<QString> arrValuesUsrInfo;
    modelUsrInfo->queryRecordData(curRow,arrValuesUsrInfo);

    AddUsrDlg dlgAddUsr;
    dlgAddUsr.ModifyUsrInfos(arrValuesUsrInfo);
    dlgAddUsr.show();
    if(dlgAddUsr.exec()==QDialog::Accepted)
    {
        modelUsrInfo->changeRecordData(curRow,dlgAddUsr.arrValues);
        UpdateTableViewUserInfo();
    }

}

void TabWidget_SystemSetting::on_usrPushBtnDel_clicked()
{
    int btnStandard=QMessageBox::warning(this,tr("删除数据"),tr("确定删除数据吗？"),tr("Yes"),tr("No"));
    if(btnStandard==0)
    {
        int curRow = ui->tableViewUserInfo->currentIndex().row();
        modelUsrInfo->delData(curRow);

        UpdateTableViewUserInfo();
    }
}
