#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./TabWidgets/includetabs.h"

#include "./CH375/ch375rw.h"

#include "./DataBase/sqldbmodel.h"

#include "./DataStructure/ds_timesetting.h"
#include "./DataStructure/ds_enablecard.h"
#include "./DataStructure/ds_sysswitchcard.h"
#include "./DataStructure/ds_usercard.h"

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QAction>
#include <QActionGroup>
#include <QString>
#include <QToolButton>
#include <QLabel>
#include <QGroupBox>
#include <QTextBrowser>
#include <QPushButton>
#include <QFile>
#include <QMessageBox>
#include <QPalette>
#include <QDir>
#include <QAbstractNativeEventFilter>
#include <QSettings>
#include <QTextCodec>
#include <QDebug>

void CALLBACK CH375NOTIFYROUTINE(ULONG iEventStatus);

namespace Ui {
class MainWindow;
}

class MainWindow :
        public QMainWindow,
        public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual bool
    nativeEventFilter(const QByteArray &eventType, void *message, long *result);

private:
    QActionGroup *actionGroup;
    QAction *actionConnectCardReader;
    QAction *actionOwnerCard;
    QAction *actionManagerCard;
    QAction *actionFunctionCard;
    QAction *actionRemoteOperation;
    QAction *actionStatisticalAnalysis;
    QAction *actionElevatorManage;
    QAction *actionSystemSetting;
    QAction *actionHelpSupport;
    QAction *actionExitApp;

private slots:
    void slotConnectCardReader();
    void slotOwnerCard();
    void slotManagerCard();
    void slotFunctionCard();
    void slotRemoteOperation();
    void slotStatisticalAnalysis();
    void slotElevatorManage();
    void slotSystemSetting();
    void slotHelpSupport();

private:
    void InitToolBar();
    void InitTabs();
    void InitVBoxInfos();
    void TabWidgetDisplay(ushort);

public:
    QTextBrowser *txtbrwInfos;

private:
    QGroupBox *grpboxInfos;
    QVBoxLayout *layoutVBoxInfos;
    QPushButton *btnReadCard;
    QPushButton *btnInitCard;

private slots:
    void slotBtnReadCard();
    void slotBtnInitCard();

private:
    QVBoxLayout *layoutVBoxTabs;
    TabWidget_OwnerCard *tabOwnerCard;
    TabWidget_ManagerCard *tabManagerCard;
    TabWidget_FunctionCard *tabFunctionCard;
    TabWidget_RemoteOperation *tabRemoteOperation;
    TabWidget_StatisticalAnalysis *tabStatisticalAnalysis;
    TabWidget_ElevatorManage *tabElevatorManage;
    TabWidget_SystemSetting *tabSystemSetting;
    TabWidget_HelpSupport *tabHelpSupport;

private:
    QHBoxLayout *layoutHBoxMain;

private:
    const QString strIconApp;
    const QString strIconConnectCardReader;
    const QString strIconDisconnectCardReader;
    const QString strIconOwnerCard;
    const QString strIconManagerCard;
    const QString strIconFunctionCard;
    const QString strIconRemoteOperation;
    const QString strIconStatisticalAnalysis;
    const QString strIconElevatorManage;
    const QString strIconSystemSetting;
    const QString strIconHelpSupport;
    const QString strIconExitApp;
    const QString strPathQssFile;

public:
    CH375RW ch375rw;
    QString strUsrName;
    QString strUsrLevel;

private:
    const QColor clrBKApp;
    QSettings *setIniFile;
    DS_TimeSetting dsTimeSet;
    DS_EnableCard dsEnableCard;
    DS_SysSwitchCard dsSysSwitchCard;
    DS_UserCard dsUserCard;

private:
    Ui::MainWindow *ui;

public:
    static MainWindow *pMainWnd;

private:
    void ConnectedCardReader(bool);
};

#endif // MAINWINDOW_H
