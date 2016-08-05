#ifndef DIALOGSIGNIN_H
#define DIALOGSIGNIN_H

#include "./CH375/ch375rw.h"
#include "./DataBase/sqldb.h"

#include <QDialog>
#include <QMessageBox>
#include <QMap>

namespace Ui {
class DialogSignin;
}

class DialogSignin : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSignin(QWidget *parent = 0);
    ~DialogSignin();

public:
    CH375RW rw;
    QMap<QString,QString> mapUsrInfo;
    QString strUsrName;
    QString strUsrLevel;

private slots:
    void on_loginBtn_clicked();
    void on_exitBtn_clicked();

private:
    Ui::DialogSignin *ui;
};

#endif // DIALOGSIGNIN_H
