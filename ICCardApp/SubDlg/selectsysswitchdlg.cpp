#include "selectsysswitchdlg.h"
#include "ui_selectsysswitchdlg.h"

#include "QtSql/QSqlTableModel"

SelectSysSwitchDlg::SelectSysSwitchDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectSysSwitchDlg)
{
    ui->setupUi(this);

    QSqlTableModel *modelTable = new QSqlTableModel(this);
    modelTable->setTable("tableSysSwitchCard");
    modelTable->select();

    ui->tableView->setModel(modelTable);
}

SelectSysSwitchDlg::~SelectSysSwitchDlg()
{
    delete ui;
}

void SelectSysSwitchDlg::on_pushBtnSel_clicked()
{
    accept();
}

void SelectSysSwitchDlg::on_pushBtnCancel_clicked()
{
    reject();
}
