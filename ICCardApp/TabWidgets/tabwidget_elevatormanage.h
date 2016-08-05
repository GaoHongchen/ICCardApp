#ifndef TABWIDGET_ELEVATORMANAGE_H
#define TABWIDGET_ELEVATORMANAGE_H

#include <QTabWidget>
#include <QDebug>

#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QTableWidget>
#include <QPainter>

#include "../DataBase/sqldbmodel.h"
#include "../SubDlg/addliftdlg.h"
#include "../SubDlg/addchargestddlg.h"

namespace Ui {
class TabWidget_ElevatorManage;
}

class TabWidget_ElevatorManage : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabWidget_ElevatorManage(QWidget *parent = 0);
    ~TabWidget_ElevatorManage();

public:
    SqlDBModel *modelDBLift;
    SqlDBModel *modelDBChargeStd;

public:
    void UpdateTableViewLiftInfos();

    void UpdateTableViewChargeStd();

private slots:
    void on_liftsetPushBtnAdd_clicked();

    void on_liftsetPushBtnDelete_clicked();

    void on_liftsetPushBtnModify_clicked();

    void on_chargestdPushBtnAdd_clicked();

    void on_chargestdPushBtnModify_clicked();

    void on_chargestdPushBtnDelete_clicked();

    void on_liftsetPushBtnPrint_clicked();

private:
    Ui::TabWidget_ElevatorManage *ui;
};

#endif // TABWIDGET_ELEVATORMANAGE_H
