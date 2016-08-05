#include "sqldb.h"

SqlDB::SqlDB()
{

}

void SqlDB::connectAccessDB(QString strDBPath)
{
    QString strDSN=QString("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=%1;UID=;PWD=").arg(strDBPath);
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(strDSN);
    if(db.open())
    {
        OutputDebugStringW(L"Access sucess");
    }
    else
    {
        OutputDebugStringW(L"Access failed");
        QMessageBox::critical(0,QObject::tr("Database Error"),db.lastError().text());
    }
}

void SqlDB::connectMySqlDB(QString strHost,QString strUser,QString strPwd,QString strDBName)
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(strHost);
    db.setUserName(strUser);
    db.setPassword(strPwd);
    db.setDatabaseName(strDBName);

    if(db.open())
    {
        OutputDebugStringW(L"MySql sucess");
    }
    else
    {
        OutputDebugStringW(L"MySql failed");
        QMessageBox::critical(0,QObject::tr("Database Error"),db.lastError().text());
    }
}

SqlDB::~SqlDB()
{

}
