#include "tabwidget_elevatormanage.h"
#include "ui_tabwidget_elevatormanage.h"

TabWidget_ElevatorManage::TabWidget_ElevatorManage(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TabWidget_ElevatorManage)
{
    ui->setupUi(this);

    std::vector<QString> arrFiledsLiftInfos;
    arrFiledsLiftInfos.push_back("电梯编号");
    arrFiledsLiftInfos.push_back("电梯名称");
    arrFiledsLiftInfos.push_back("电梯类型");
    arrFiledsLiftInfos.push_back("总楼层数");
    arrFiledsLiftInfos.push_back("起始楼层");
    arrFiledsLiftInfos.push_back("公用楼层");
    arrFiledsLiftInfos.push_back("电梯数量");
    arrFiledsLiftInfos.push_back("备注");
    modelDBLift = new SqlDBModel("tableLift",arrFiledsLiftInfos);
    UpdateTableViewLiftInfos();

    std::vector<QString> arrFiledsChargeStd;
    arrFiledsChargeStd.push_back("楼层下限");
    arrFiledsChargeStd.push_back("楼层上限");
    arrFiledsChargeStd.push_back("单次收费");
    modelDBChargeStd = new SqlDBModel("tableChargeStd",arrFiledsChargeStd);
    UpdateTableViewChargeStd();

    removeTab(1);
}

TabWidget_ElevatorManage::~TabWidget_ElevatorManage()
{
    delete ui;
    delete modelDBChargeStd;
    delete modelDBLift;
}

void TabWidget_ElevatorManage::UpdateTableViewLiftInfos()
{
    modelDBLift->queryTableData();
    ui->liftsetTableView->setModel(modelDBLift->modelTable);
}

void TabWidget_ElevatorManage::UpdateTableViewChargeStd()
{
    modelDBChargeStd->queryTableData();
    //利用setModel()方法将数据模型与QTableView绑定
    ui->chargestdTableView->setModel(modelDBChargeStd->modelTable);
}

void TabWidget_ElevatorManage::on_liftsetPushBtnAdd_clicked()
{
    AddLiftDlg dlgAddLift;
    dlgAddLift.show();
    if(dlgAddLift.exec()==QDialog::Accepted)
    {
        modelDBLift->addData(dlgAddLift.arrValues);
        UpdateTableViewLiftInfos();
    }
}

void TabWidget_ElevatorManage::on_liftsetPushBtnDelete_clicked()
{
    int btnStandard=QMessageBox::warning(this,tr("删除数据"),tr("确定删除数据吗？"),tr("Yes"),tr("No"));
    if(btnStandard==0)
    {
        int curRow = ui->liftsetTableView->currentIndex().row();
        modelDBLift->delData(curRow);
        UpdateTableViewLiftInfos();
    }
}

void TabWidget_ElevatorManage::on_liftsetPushBtnModify_clicked()
{
    int curRow = ui->liftsetTableView->currentIndex().row();
    if(curRow<0)
    {
        QMessageBox::warning(this,"警告","请先选择电梯！",QMessageBox::Yes);
        return;
    }
    std::vector<QString> arrValuesLiftInfos;
    modelDBLift->queryRecordData(curRow,arrValuesLiftInfos);

    AddLiftDlg dlgAddLift;
    dlgAddLift.ModifyLiftInfo(arrValuesLiftInfos);
    dlgAddLift.show();
    if(dlgAddLift.exec()==QDialog::Accepted)
    {
        modelDBLift->changeRecordData(curRow,dlgAddLift.arrValues);
        UpdateTableViewLiftInfos();
    }
}

void TabWidget_ElevatorManage::on_chargestdPushBtnAdd_clicked()
{
    AddChargeStdDlg dlgAddChargeStd;
    dlgAddChargeStd.show();
    if(dlgAddChargeStd.exec()==QDialog::Accepted)
    {
        modelDBChargeStd->addData(dlgAddChargeStd.arrValues);
        UpdateTableViewChargeStd();
    }
}

void TabWidget_ElevatorManage::on_chargestdPushBtnModify_clicked()
{
    int curRow = ui->chargestdTableView->currentIndex().row();
    if(curRow<0)
    {
        QMessageBox::warning(this,"警告","请先选择收费标准！",QMessageBox::Yes);
        return;
    }
    std::vector<QString> arrValuesChargeStd;
    modelDBChargeStd->queryRecordData(curRow,arrValuesChargeStd);

    AddChargeStdDlg dlgAddChargeStd;
    dlgAddChargeStd.ModifyChargeStd(arrValuesChargeStd);
    dlgAddChargeStd.show();
    if(dlgAddChargeStd.exec()==QDialog::Accepted)
    {
        modelDBChargeStd->changeRecordData(curRow,dlgAddChargeStd.arrValues);
        UpdateTableViewChargeStd();
    }
}

void TabWidget_ElevatorManage::on_chargestdPushBtnDelete_clicked()
{
    int btnStandard=QMessageBox::warning(this,tr("删除数据"),tr("确定删除数据吗？"),tr("Yes"),tr("No"));
    if(btnStandard==0)
    {       
        int curRow = ui->chargestdTableView->currentIndex().row();
        modelDBChargeStd->delData(curRow);

        UpdateTableViewChargeStd();
    }
}

void TabWidget_ElevatorManage::on_liftsetPushBtnPrint_clicked()
{
//    QSqlTableModel *modelTable = new QSqlTableModel(this);
//    modelTable->setTable("tableUserInfo");
//    modelTable->select();
//    for(int i=0;i<modelTable->rowCount();i++)
//    {
//        QModelIndex indexModelUsrName = modelTable->index(i,0);
//        QModelIndex indexModelPassWord = modelTable->index(i,2);
//        QString strUsrName = modelTable->data(indexModelUsrName).toString();
//        QString strPass = modelTable->data(indexModelPassWord).toString();
////        ui->comboBoxUsrName->addItem(strUsrName);
//        mapUsrInfo.insert(strUsrName,strPass);
//    }

    QString strDatas="";
    strDatas += ("电梯编号\t");
    strDatas += ("电梯名称\t");
    strDatas += ("电梯类型\t");
    strDatas += ("总楼层数\t");
    strDatas += ("起始楼层\t");
    strDatas += ("公用楼层\t");
    strDatas += ("电梯数量\t");
    strDatas += ("备注\n");
    for(int i=0;i<modelDBLift->modelTable->rowCount();i++)
    {
        for(int j=0;j<8;j++)
        {
            QModelIndex indexModel = modelDBLift->modelTable->index(i,j);
            QString strData = modelDBLift->modelTable->data(indexModel).toString();
            strDatas += strData;
            if(i==modelDBLift->modelTable->rowCount()-1&&j==7)
            {
                continue;
            }
            if(j==7)
            {
                strDatas += "\n";
                continue;
            }
            strDatas += "\t";
        }
    }

    QString html = strDatas.toHtmlEscaped();
    html.replace("\t", "</td><td height=30 align=\"center\">");
    html.replace("\n", "</td></tr><tr><td height=30 align=\"center\">");

    html.prepend("<tr><td height=30 align=\"center\">");
    html.prepend("<table width=\"100%\" cellspacing=0 border=1 align=\"center\">\n");

    html.prepend("<hr><br>");
    html.prepend("<h2 align=\"center\"><font color=\"red\">电梯信息记录表</font></h2>");

    html.append("</td></tr>\n</table>");

    QPrinter  printer;
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec())
    {
        QTextDocument textDocument;
        textDocument.setHtml(html);
        textDocument.print(&printer);
    }
}
