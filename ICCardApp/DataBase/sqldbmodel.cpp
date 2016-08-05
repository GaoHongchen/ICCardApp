#include "sqldbmodel.h"

SqlDBModel::SqlDBModel(QString strTableName, std::vector<QString> arrTableFields):
    strTable(strTableName),
    arrFields(arrTableFields)
{
    modelStdItem = new QStandardItemModel();

    modelQuery = new QSqlQueryModel();

    modelTable = new QSqlTableModel();
    modelTable->setTable(strTable);
}

void SqlDBModel::queryTableData(ushort nType)
{
    if(nType == 1)
    {
        modelTable->select();
    }
    if(nType == 2)
    {
        QString strQuery = "select * from " + strTable;
        modelQuery->setQuery(strQuery);
//        modelQuery->setHeaderData(0,Qt::Horizontal,tr("楼层下限"));
//        modelQuery->setHeaderData(1,Qt::Horizontal,tr("楼层上限"));
//        modelQuery->setHeaderData(2,Qt::Horizontal,tr("单次收费"));
    }
}

void SqlDBModel::queryRecordData(int row, std::vector<QString> &arrDataValues)
{
    std::vector<QString>(arrDataValues).swap(arrDataValues);

    size_t nSizeArrFields = arrFields.size();
    modelTable->select();
    QSqlRecord record=modelTable->record(row);
    for(int i=0;i<nSizeArrFields;i++)
    {
        arrDataValues.push_back(record.value(arrFields[i]).toString());
    }
}

void SqlDBModel::changeRecordData(int row, std::vector<QString> arrDataValues)
{
    size_t nSizeArr = arrDataValues.size();
    for(int i=0;i<nSizeArr;i++)
    {
        modelTable->setData(modelTable->index(row,i),arrDataValues[i]);
    }
    //modelTable->submitAll();
    modelTable->database().transaction(); //开始事务操作
    if(modelTable->submitAll()) // 提交所有被修改的数据到数据库中
    {
        modelTable->database().commit(); //提交成功，事务将真正修改数据库数据
    }
    else
    {
        modelTable->database().rollback(); //提交失败，事务回滚
    }
}

void SqlDBModel::addData(std::vector<QString> arrDataValues)
{
    modelTable->select();
    int row=modelTable->rowCount();
    modelTable->insertRows(row,1);
    size_t nSizeArr = arrDataValues.size();
    for(int i=0;i<nSizeArr;i++)
    {
        modelTable->setData(modelTable->index(row,i),arrDataValues[i]);
    }
    //modelTable->submitAll();
    modelTable->database().transaction(); //开始事务操作
    if(modelTable->submitAll()) // 提交所有被修改的数据到数据库中
    {
        modelTable->database().commit(); //提交成功，事务将真正修改数据库数据
    }
    else
    {
        modelTable->database().rollback(); //提交失败，事务回滚
    };
}

void SqlDBModel::delData(int row)
{
    modelTable->select();
    modelTable->removeRow(row);
    modelTable->submitAll();
}

SqlDBModel::~SqlDBModel()
{
    delete modelStdItem;
    modelStdItem = NULL;

    delete modelQuery;
    modelQuery = NULL;

    delete modelTable;
    modelTable = NULL;
}
