#ifndef TABWIDGET_SYSTEMSETTING_H
#define TABWIDGET_SYSTEMSETTING_H

#include <QTabWidget>

#include "../DataBase/sqldbmodel.h"
#include "../SubDlg/addusrdlg.h"

namespace Ui {
class TabWidget_SystemSetting;
}

class TabWidget_SystemSetting : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabWidget_SystemSetting(QWidget *parent = 0);
    ~TabWidget_SystemSetting();

public:
    SqlDBModel *modelUsrInfo;

public:
    void UpdateTableViewUserInfo();

private slots:
    void on_usrPushBtnAddUsr_clicked();

    void on_usrPushBtnChange_clicked();

    void on_usrPushBtnDel_clicked();

private:
    Ui::TabWidget_SystemSetting *ui;
};

#endif // TABWIDGET_SYSTEMSETTING_H
