#include "dialogsignin.h"
#include "ui_dialogsignin.h"

DialogSignin::DialogSignin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSignin)
{
    ui->setupUi(this);

    //连接数据库
    SqlDB db;
    db.connectAccessDB(".\\ICCardDB.accdb");
    //db.connectMySqlDB("localhost","root","","iccarddb");

    QSqlTableModel *modelTable = new QSqlTableModel(this);
    modelTable->setTable("tableUserInfo");
    modelTable->select();
    for(int i=0;i<modelTable->rowCount();i++)
    {
        QModelIndex indexModelUsrName = modelTable->index(i,0);
        QModelIndex indexModelPassWord = modelTable->index(i,2);
        QString strUsrName = modelTable->data(indexModelUsrName).toString();
        QString strPass = modelTable->data(indexModelPassWord).toString();
//        ui->comboBoxUsrName->addItem(strUsrName);
        mapUsrInfo.insert(strUsrName,strPass);
    }

    ui->comboBoxUsrLevel->addItem("系统管理员");
    ui->comboBoxUsrLevel->addItem("普通用户");

    ui->pwdLineEditUsrName->setFocus();
    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);

    //加密狗检测
    //QMessageBox::critical(this,tr("加密狗错误"),tr("没有插入加密狗或插入的加密狗有误，请插入正确的加密狗，并重新启动软件!"),QMessageBox::Yes);
    //读卡器检测
    //检查读卡器是否连接上
    if(!rw.OpenDevice())
    {
        //QMessageBox::critical(this,tr("读卡器错误"),tr("请插入读卡器!"),QMessageBox::Yes);
    }
    else
    {
        //CH375CloseDevice(0);//关闭设备
    }
}

DialogSignin::~DialogSignin()
{
    delete ui;
}

void DialogSignin::on_loginBtn_clicked()
{
    strUsrLevel = ui->comboBoxUsrLevel->currentText();
    strUsrName = ui->pwdLineEditUsrName->text();
    if(ui->pwdLineEdit->text()==mapUsrInfo.value(strUsrName) && !strUsrName.isEmpty())
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this,tr("用户名或密码错误"),tr("用户名或密码错误，请重新输入！"),QMessageBox::Yes);
        //ui->pwdLineEditUsrName->clear();
        ui->pwdLineEdit->clear();
        ui->pwdLineEditUsrName->setFocus();
    }
}

void DialogSignin::on_exitBtn_clicked()
{
    exit(0);
}
