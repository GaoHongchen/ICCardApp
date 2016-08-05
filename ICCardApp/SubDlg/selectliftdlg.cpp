#include "selectliftdlg.h"
#include "ui_selectliftdlg.h"

#include "QtSql/QSqlTableModel"
#include "QtSql/QSqlIndex"

SelectLiftDlg::SelectLiftDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectLiftDlg)
{
    ui->setupUi(this);

    QSqlTableModel *modelTable = new QSqlTableModel(this);
    modelTable->setTable("tableLift");
    modelTable->select();

    ui->tableView->setModel(modelTable);
}

SelectLiftDlg::~SelectLiftDlg()
{
    delete ui;
}

void SelectLiftDlg::on_pushBtnSel_clicked()
{
    int curRow = ui->tableView->currentIndex().row();
    if(curRow<0)
    {
        QMessageBox::warning(this,"警告","请先选择电梯！",QMessageBox::Yes);
        return;
    }
    QSqlTableModel *modelTable = new QSqlTableModel(this);
    modelTable->setTable("tableLift");
    modelTable->select();

    for(int i=0;i<modelTable->columnCount();i++)
    {
        QModelIndex index = modelTable->index(curRow,i);
        arrValues.push_back(modelTable->data(index).toString());
    }

    accept();
}

void SelectLiftDlg::on_pushBtnCancel_clicked()
{
    reject();
}
