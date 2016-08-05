#ifndef SQLDB_H
#define SQLDB_H

#include <windows.h>
#include <QString>
#include <QMessageBox>

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>

#include <QStandardItem>
#include <QStandardItemModel>

class SqlDB
{
public:
    SqlDB();
    ~SqlDB();

public:
    void connectAccessDB(QString strDBPath);
    void connectMySqlDB(QString strHost, QString strUser, QString strPwd, QString strDBName);
};

#endif // SQLDB_H
