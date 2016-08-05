#ifndef SQLDBMODEL_H
#define SQLDBMODEL_H

#include "sqldb.h"

class SqlDBModel : public SqlDB
{
public:
    SqlDBModel(QString strTableName, std::vector<QString> arrTableFields);
    ~SqlDBModel();

public:
    void queryTableData(ushort nType=1);
    void queryRecordData(int row,std::vector<QString> &arrDataValues);
    void changeRecordData(int row,std::vector<QString> arrDataValues);
    void addData(std::vector<QString> arrDataValues);
    void delData(int row);

public:
    QStandardItemModel *modelStdItem;
    QSqlTableModel *modelTable;
    QSqlQueryModel *modelQuery;

private:
    QString strTable;
    std::vector<QString> arrFields;

};

#endif // SQLDBMODEL_H
