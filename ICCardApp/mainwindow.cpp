#include "mainwindow.h"
#include "ui_mainwindow.h"

HWND hMainWnd=nullptr;

MainWindow *MainWindow::pMainWnd=NULL;

bool MainWindow::nativeEventFilter
(
    const QByteArray &eventType, void *message, long *result
)
{
    if
    (
        eventType == "windows_generic_MSG"
            ||
        eventType == "windows_dispatcher_MSG"
    )
    {
        bool isConnected=false;
        MSG *pMsg = reinterpret_cast<MSG*>(message);
        switch(pMsg->message)
        {
        case UM_EVENT_DEVICE_ARRIVAL:
            isConnected = true;
            ch375rw.OpenDevice();
            ch375rw.bIsOpened=true;
            break;
        case UM_EVENT_DEVICE_REMOVE:
            isConnected = false;
            ch375rw.bIsOpened=false;
            break;
        default:
            return false;
        }
        ConnectedCardReader(isConnected);
    }
    return false;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    strIconApp(":/AppIcon/Resources/AppIcon_ArchitectureBuilding_96px.ico"),
    strIconConnectCardReader(":/ToolbarIcons/Resources/connect_72px.ico"),
    strIconDisconnectCardReader(":/ToolbarIcons/Resources/disconnect_72px.ico"),
    strIconOwnerCard(":/ToolbarIcons/Resources/users_72px.ico"),
    strIconManagerCard(":/ToolbarIcons/Resources/administrator_72px.ico"),
    strIconFunctionCard(":/ToolbarIcons/Resources/FuncCard_72px.ico"),
    strIconRemoteOperation(":/ToolbarIcons/Resources/remote_72px.ico"),
    strIconStatisticalAnalysis(":/ToolbarIcons/Resources/Statistics_72px.ico"),
    strIconElevatorManage(":/ToolbarIcons/Resources/Management_72px.ico"),
    strIconSystemSetting(":/ToolbarIcons/Resources/setting_72px.ico"),
    strIconHelpSupport(":/ToolbarIcons/Resources/Help_72px.ico"),
    strIconExitApp(":/ToolbarIcons/Resources/exit_72px.ico"),
    strPathQssFile(":/CSS/StyleSheet.qss"),
    clrBKApp(QColor(100,200,200)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pMainWnd=this;

    //读取ini配置文件
    setIniFile=new QSettings("AppSetting.ini",QSettings::IniFormat);
    setIniFile->setIniCodec(QTextCodec::codecForName("GB2312"));
    //setIniFile->setValue("/SystemSetting/Company", "北京凯瑞通电子技术有限公司");
    setIniFile->beginGroup("SystemSetting");
    QString strCompanyName=setIniFile->value("Company").toString();
    setIniFile->endGroup();

    //加载CSS样式表文件并应用相应样式
    QFile qssFile(strPathQssFile);
    if(qssFile.exists())
    {
        qssFile.open(QFile::ReadOnly);
        if(qssFile.isOpen())
        {
            QString qss = QLatin1String(qssFile.readAll());
            qApp->setStyleSheet(qss);
            qssFile.close();
        }
    }
    else
    {
        QMessageBox::warning(NULL,"Qss文件错误",strPathQssFile+"找不到！");
        return;
    }

    //限制窗口大小
    this->setMaximumSize(1500,1000);

    //设置应用程序背景色
    QPalette *paletteApp=new QPalette();
    paletteApp->setColor(QPalette::Background,clrBKApp);
    this->setPalette(*paletteApp);
    delete paletteApp;

    //设置应用程序图标
    this->setWindowIcon(QIcon(strIconApp));

    //隐藏标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    //主窗体菜单栏初始化
    ui->menuBar->hide();
    //主窗体状态栏初始化
    strUsrName = "abc";
    strUsrLevel = "系统管理员";
    QString strLabelUsrInfo = "用户名："+strUsrName+" 用户级别："+strUsrLevel;
    QLabel *labelCompanyName=new QLabel;
    labelCompanyName->setText(strLabelUsrInfo);
    statusBar()->addWidget(labelCompanyName);
    //主窗体工具栏初始化
    InitToolBar();
    //主窗体Tabs初始化
    InitTabs();
    //主窗体信息窗口初始化
    InitVBoxInfos();
    //主窗体框架初始化
    layoutHBoxMain=new QHBoxLayout(ui->centralWidget);
    layoutHBoxMain->addLayout(layoutVBoxTabs);
    layoutHBoxMain->addWidget(grpboxInfos);
    TabWidgetDisplay(0);

    //获取MainWindows的句柄
    hMainWnd=(HWND)this->winId();
    //启动指定序号设备插拔监视
    ch375rw.SetDeviceNotify();

    //检查读卡器是否连接上
    bool isConnected;
    if(!ch375rw.OpenDevice())
    {
        isConnected=false;       
    }
    else
    {
        isConnected=true;
        ch375rw.Beep(1);
    }
    isConnected=true;
    ConnectedCardReader(isConnected);
}

void MainWindow::ConnectedCardReader(bool flag)
{
    if(flag)
    {
        actionConnectCardReader->setText("已连接读卡器");
        actionConnectCardReader->setIcon(QIcon(strIconConnectCardReader));
    }
    else
    {
        actionConnectCardReader->setText("请插入读卡器");
        actionConnectCardReader->setIcon(QIcon(strIconDisconnectCardReader));
    }
}

void MainWindow::slotConnectCardReader()
{

}

void MainWindow::slotOwnerCard()
{
    TabWidgetDisplay(0);
}
void MainWindow::slotManagerCard()
{
    TabWidgetDisplay(1);
}
void MainWindow::slotFunctionCard()
{
    TabWidgetDisplay(2);
}
void MainWindow::slotRemoteOperation()
{
    TabWidgetDisplay(3);
}
void MainWindow::slotStatisticalAnalysis()
{
    TabWidgetDisplay(4);
}
void MainWindow::slotElevatorManage()
{
    TabWidgetDisplay(5);
}
void MainWindow::slotSystemSetting()
{
    TabWidgetDisplay(6);
}
void MainWindow::slotHelpSupport()
{
    TabWidgetDisplay(7);
}

void MainWindow::slotBtnReadCard()
{  
    std::string strTxtbrwInfos = "";
    QString strQTxtbrwInfos;
#ifdef USE_CH375
    if(ch375rw.bIsOpened)
    {
        ch375rw.Read(0x00,48);
        Sleep(TIME_DELAY);
        UCHAR *chData = ch375rw.Read(0x00,48);
        if(chData==NULL)
        {
            return;
        }
        strTxtbrwInfos = "卡号："+ch375rw.strCardID+"\n";
        switch(int(chData[1]))//卡类型
        {
        case 0x01://用户卡
        {
            strTxtbrwInfos += "卡类型：用户卡\n";
            dsUserCard.chars2DS(chData);

            break;
        }
        case 0x2://普通管理人卡
            strTxtbrwInfos += "卡类型：普通管理人卡\n";
            break;
        case 0x3://高级管理人卡
            strTxtbrwInfos += "卡类型：高级管理人卡\n";
            break;
        case 0x04://黑名单（启禁用卡）
        {
            strTxtbrwInfos += "卡类型：启禁用卡\n";
            dsEnableCard.chars2DS(chData);
            if(dsEnableCard.structEnableCard.EnableType==0x01)//按卡号
            {
                strTxtbrwInfos += "启禁用类型：按卡号\n";
            }
            if(dsEnableCard.structEnableCard.EnableType==0x02)//按房号
            {
                strTxtbrwInfos += "启禁用类型：按房号\n";
            }
            std::string strLimitCardType="";
            if(dsEnableCard.structEnableCard.LimitCardType==0x01)
            {
                strLimitCardType="用户卡";
            }
            if(dsEnableCard.structEnableCard.LimitCardType==0x02)
            {
                strLimitCardType="管理人卡";
            }
            int nLiftNum = dsEnableCard.structEnableCard.LiftNum;
            strTxtbrwInfos +=
                "可用电梯："+TypeConvert::intNormal2stdstring(nLiftNum)+"\n";
            if(dsEnableCard.structEnableCard.Num1[0]==0x00)
            {
                std::string strIsEnable1="";
                if(dsEnableCard.structEnableCard.IsEnable1==0x01)
                {
                    strIsEnable1="启用";
                }
                if(dsEnableCard.structEnableCard.IsEnable1==0x02)
                {
                    strIsEnable1="禁用";
                }
                std::string strNum1="";
                for(int i=0;i<4;i++)
                {
                    int nNum1=dsEnableCard.structEnableCard.Num1[i];
                    strNum1 += TypeConvert::intDec2stdstring(nNum1);
                }
                if(dsEnableCard.structEnableCard.EnableType==0x01)
                {
                    strTxtbrwInfos +=
                            strLimitCardType+"卡号："+
                            strNum1.substr(3,5)+" "+strIsEnable1+"\n";
                }
                if(dsEnableCard.structEnableCard.EnableType==0x02)
                {
                    strTxtbrwInfos +=
                            "房号："+strNum1.substr(4,4)+" "+strIsEnable1+"\n";
                }
            }
            if(dsEnableCard.structEnableCard.Num2[0]==0x00)
            {
                std::string strIsEnable2="";
                if(dsEnableCard.structEnableCard.IsEnable2==0x01)
                {
                    strIsEnable2="启用";
                }
                if(dsEnableCard.structEnableCard.IsEnable2==0x02)
                {
                    strIsEnable2="禁用";
                }
                std::string strNum2="";
                for(int i=0;i<4;i++)
                {
                    int nNum2=dsEnableCard.structEnableCard.Num2[i];
                    strNum2 += TypeConvert::intDec2stdstring(nNum2);
                }
                if(dsEnableCard.structEnableCard.EnableType==0x01)
                {
                    strTxtbrwInfos +=
                            strLimitCardType+"卡号："+
                            strNum2.substr(3,5)+" "+strIsEnable2+"\n";
                }
                if(dsEnableCard.structEnableCard.EnableType==0x02)
                {
                    strTxtbrwInfos +=
                            "房号："+strNum2.substr(4,4)+" "+strIsEnable2+"\n";
                }
            }
            if(dsEnableCard.structEnableCard.Num3[0]==0x00)
            {
                std::string strIsEnable3="";
                if(dsEnableCard.structEnableCard.IsEnable3==0x01)
                {
                    strIsEnable3="启用";
                }
                if(dsEnableCard.structEnableCard.IsEnable3==0x02)
                {
                    strIsEnable3="禁用";
                }
                std::string strNum3="";
                for(int i=0;i<4;i++)
                {
                    int nNum3=dsEnableCard.structEnableCard.Num3[i];
                    strNum3 += TypeConvert::intDec2stdstring(nNum3);
                }
                if(dsEnableCard.structEnableCard.EnableType==0x01)
                {
                    strTxtbrwInfos +=
                            strLimitCardType+"卡号："+
                            strNum3.substr(3,5)+" "+strIsEnable3+"\n";
                }
                if(dsEnableCard.structEnableCard.EnableType==0x02)
                {
                    strTxtbrwInfos +=
                            "房号："+strNum3.substr(4,4)+" "+strIsEnable3+"\n";
                }
            }
            if(dsEnableCard.structEnableCard.Num4[0]==0x00)
            {
                std::string strIsEnable4="";
                if(dsEnableCard.structEnableCard.IsEnable4==0x01)
                {
                    strIsEnable4="启用";
                }
                if(dsEnableCard.structEnableCard.IsEnable4==0x02)
                {
                    strIsEnable4="禁用";
                }
                std::string strNum4="";
                for(int i=0;i<4;i++)
                {
                    int nNum4=dsEnableCard.structEnableCard.Num4[i];
                    strNum4 += TypeConvert::intDec2stdstring(nNum4);
                }
                if(dsEnableCard.structEnableCard.EnableType==0x01)
                {
                    strTxtbrwInfos +=
                            strLimitCardType+"卡号："+
                            strNum4.substr(3,5)+" "+strIsEnable4+"\n";
                }
                if(dsEnableCard.structEnableCard.EnableType==0x02)
                {
                    strTxtbrwInfos +=
                            "房号："+strNum4.substr(4,4)+" "+strIsEnable4+"\n";
                }
            }
            break;
        }
        case 0x06://时间矫正卡
        {
            strTxtbrwInfos += "卡类型：时间矫正卡\n";
            dsTimeSet.chars2DS(chData);
            switch(dsTimeSet.structTimeSet.TimeSetType)
            {
            case SetType::SetControlerTime:
            {
                strTxtbrwInfos += "时间卡功能：控制器时间设置\n";               
                std::vector<std::string> vectorDateTime;
                for(int i=0;i<6;i++)
                {
                    int nTemp=dsTimeSet.structTimeSet.ControlerTime[i];
                    vectorDateTime.push_back(TypeConvert::intHex2stdstring(nTemp));
                }
                std::string strDateTime =
                        vectorDateTime[0]+    vectorDateTime[1]+"-"+
                        vectorDateTime[2]+"-"+vectorDateTime[3]+" "+
                        vectorDateTime[4]+":"+vectorDateTime[5];
                strTxtbrwInfos += "控制器时间："+strDateTime+"\n";
                break;
            }
            case SetType::SetKeyResponseTime:
            {
                strTxtbrwInfos += "时间卡功能：按钮响应时间设置\n";
                float fTimeOne=
                        float(dsTimeSet.structTimeSet.SingleSelectTime)/10;
                short sTimeMul=dsTimeSet.structTimeSet.MultiSelectTime;
                std::string strTimeOne=TypeConvert::float2stdstring(fTimeOne);
                std::string strTimeMul=TypeConvert::intDec2stdstring(sTimeMul);
                strTxtbrwInfos +=
                        "单选按键响应时间："+strTimeOne+"秒\n"+
                        "多选按键响应时间："+strTimeMul+"秒\n";
                break;
            }
            case SetType::SetVisitorResponseTime:
            {
                strTxtbrwInfos += "时间卡功能：访客按钮响应时间设置\n";
                int nHI=dsTimeSet.structTimeSet.VisitorTime[0];
                int nLO=dsTimeSet.structTimeSet.VisitorTime[1];
                int nTimeVisit=nHI*256+nLO;
                std::string strTimeVisit =
                        TypeConvert::intNormal2stdstring(nTimeVisit);
                strTxtbrwInfos +=
                        "访客按键响应时间："+strTimeVisit+"秒\n";
                break;
            }
            }
            break;
        }
        case 0x7://电梯运行卡
        {
            strTxtbrwInfos += "卡类型：电梯运行卡\n";
            break;
        }
        case 0x08://系统开关卡
        {
            strTxtbrwInfos += "卡类型：系统开关卡\n";
            dsSysSwitchCard.chars2DS(chData);
            switch (dsSysSwitchCard.structSysSwitchCard.SwitchCardType)
            {
            case SWCardType::SysSwitch:
            {
                strTxtbrwInfos+="开关卡分类：系统开关卡\n";
                break;
            }
            case SWCardType::LayerSwitch:
            {
                strTxtbrwInfos+="开关卡分类：分层开关卡\n";
                if(dsSysSwitchCard.structSysSwitchCard.SwitchFlag==0x11)
                {
                    strTxtbrwInfos+="开关标识：开放\n";
                }
                if(dsSysSwitchCard.structSysSwitchCard.SwitchFlag==0x22)
                {
                    strTxtbrwInfos+="开关标识：关闭\n";
                }
                //电梯编号
                int nLiftNum=0;
                for(int i=0;i<32;i++)
                {
                    for(int j=0;j<8;j++)
                    {
                        if
                        (
                        (dsSysSwitchCard.structSysSwitchCard.LiftNum[i] & (1<<j)) == pow(2,j)
                        )
                        {
                            nLiftNum=i*8+(j+1);
                            break;
                        }
                    }
                }
                strTxtbrwInfos+="可用电梯号："+TypeConvert::intNormal2stdstring(nLiftNum)+"\n";
                //受控楼层
                strTxtbrwInfos+="受控楼层：";
                strTxtbrwInfos+="A门：";
                for(int i=0;i<6;i++)
                {
                    for(int j=0;j<8;j++)
                    {
                        if
                        (
                        (dsSysSwitchCard.structSysSwitchCard.FloorsA[i]&(1<<j)) == pow(2,j)
                        )
                        {
                            int nFloor = i*8+(j+1);
                            strTxtbrwInfos+=TypeConvert::intNormal2stdstring(nFloor)+",";
                        }
                    }
                }
                strTxtbrwInfos.erase(strTxtbrwInfos.end()-1);
                strTxtbrwInfos+="\n";
                break;
            }
            case SWCardType::PublicFloorsSet:
            {
                strTxtbrwInfos+="开关卡分类：公共楼层设置卡\n";
                if(dsSysSwitchCard.structSysSwitchCard.SwitchFlag==0x11)
                {
                    strTxtbrwInfos+="开关标识：开放\n";
                }
                if(dsSysSwitchCard.structSysSwitchCard.SwitchFlag==0x22)
                {
                    strTxtbrwInfos+="开关标识：关闭\n";
                }
                //电梯编号
                int nLiftNum=1;
                for(int i=0;i<32;i++)
                {
                    for(int j=0;j<8;j++)
                    {
                        if
                        (
                        (dsSysSwitchCard.structSysSwitchCard.LiftNum[i]&(1<<j)) == pow(2,j)
                        )
                        {
                            nLiftNum=i*8+(j+1);
                        }
                    }
                }
                strTxtbrwInfos+="可用电梯号："+TypeConvert::intNormal2stdstring(nLiftNum)+"\n";
                //受控楼层
                strTxtbrwInfos+="受控楼层：";
                strTxtbrwInfos+="A门：";
                for(int i=0;i<6;i++)
                {
                    for(int j=0;j<8;j++)
                    {
                        if
                        (
                        (dsSysSwitchCard.structSysSwitchCard.FloorsA[i]&(1<<j)) == pow(2,j)
                        )
                        {
                            int nFloor = i*8+(j+1);
                            strTxtbrwInfos+=TypeConvert::intNormal2stdstring(nFloor)+",";
                        }
                    }
                }
                strTxtbrwInfos.erase(strTxtbrwInfos.end()-1);
                strTxtbrwInfos+="\n";
                break;
            }
            default:
                break;
            }
            break;
        }
        case 0x0A://通讯地址设定卡
        {
            strTxtbrwInfos += "卡类型：通讯地址设定卡\n";
            int nAddr = chData[2];
            strTxtbrwInfos +=
                    "地址："+TypeConvert::intNormal2stdstring(nAddr)+"\n";
            break;
        }
        case 0x0B://清内存卡
        {
            strTxtbrwInfos += "卡类型：清内存卡\n";
            break;
        }     
        default:
        {
            strTxtbrwInfos += "此卡为新卡\n";
            break;
        }
        }
    }
    else
    {
        strTxtbrwInfos = "请插入读卡器！";
    }
    ch375rw.Beep(1);
    strQTxtbrwInfos=QString::fromStdString(strTxtbrwInfos);
#endif

    static int countClick=0;
    countClick++;
    switch(countClick)
    {
    case 1:
    {
        strQTxtbrwInfos="用户卡\n";
        std::vector<QString> arrFiledsUsrCards;
        arrFiledsUsrCards.push_back("卡号");
        arrFiledsUsrCards.push_back("业主姓名");
        arrFiledsUsrCards.push_back("业主门牌");
        arrFiledsUsrCards.push_back("联系电话");
        arrFiledsUsrCards.push_back("限制日期");
        arrFiledsUsrCards.push_back("可用电梯");
        arrFiledsUsrCards.push_back("可用楼层");
        arrFiledsUsrCards.push_back("房间编号");

        QSqlTableModel *modelTableUsrCard = new QSqlTableModel(this);
        modelTableUsrCard->setTable("tableUsrCard");
        modelTableUsrCard->select();
        int rowLast = modelTableUsrCard->rowCount()-1;
        for(int i=0;i<8;i++)
        {
            QModelIndex indexModelLast = modelTableUsrCard->index(rowLast,i);
            QString strUsrCardLast = modelTableUsrCard->data(indexModelLast).toString();
            strQTxtbrwInfos += arrFiledsUsrCards[i] + "："+strUsrCardLast+"\n";
        }
        break;
    }
    case 2:
    {
        strQTxtbrwInfos="此卡为新卡！\n";
        break;
    }
    }

    txtbrwInfos->setText(strQTxtbrwInfos);
}

void MainWindow::slotBtnInitCard()
{
#ifdef USE_CH375
    uchar initData[50] = {0};
    if(ch375rw.bIsOpened)
    {
        if(ch375rw.Write(0x00,50,initData))
        {
            if(ch375rw.Write(50,50,initData))
            {
                Sleep(TIME_DELAY);
                ch375rw.Beep(1);
                txtbrwInfos->setText("====数据初始化成功====");
            }
        }
    }
#endif
    txtbrwInfos->setText("====数据初始化成功====");
}

void MainWindow::InitToolBar()
{
    //主窗体工具栏初始化
    ui->mainToolBar->setStyleSheet("font-size : 16px");
    //qApp->setStyleSheet("QToolBar { font: 20px; }");

    actionGroup=new QActionGroup(this);

    actionConnectCardReader=new QAction("连接读写器",this);
    actionConnectCardReader->setIcon(QIcon(strIconConnectCardReader));
    connect(actionConnectCardReader,SIGNAL(triggered(bool)),this,SLOT(slotConnectCardReader()));

    actionOwnerCard=new QAction("用户卡",actionGroup);
    actionOwnerCard->setIcon(QIcon(strIconOwnerCard));
    actionOwnerCard->setCheckable(true);
    actionOwnerCard->setChecked(true);
    connect(actionOwnerCard,SIGNAL(triggered(bool)),this,SLOT(slotOwnerCard()));

    actionManagerCard=new QAction("管理员卡",actionGroup);
    actionManagerCard->setIcon(QIcon(strIconManagerCard));
    actionManagerCard->setCheckable(true);
    connect(actionManagerCard,SIGNAL(triggered(bool)),this,SLOT(slotManagerCard()));

    actionFunctionCard=new QAction("功能卡",actionGroup);
    actionFunctionCard->setIcon(QIcon(strIconFunctionCard));
    actionFunctionCard->setCheckable(true);
    connect(actionFunctionCard,SIGNAL(triggered(bool)),this,SLOT(slotFunctionCard()));

    actionRemoteOperation=new QAction("远程操作",actionGroup);
    actionRemoteOperation->setIcon(QIcon(strIconRemoteOperation));
    actionRemoteOperation->setCheckable(true);
    connect(actionRemoteOperation,SIGNAL(triggered(bool)),this,SLOT(slotRemoteOperation()));

    actionStatisticalAnalysis=new QAction("统计分析",actionGroup);
    actionStatisticalAnalysis->setIcon(QIcon(strIconStatisticalAnalysis));
    actionStatisticalAnalysis->setCheckable(true);
    connect(actionStatisticalAnalysis,SIGNAL(triggered(bool)),this,SLOT(slotStatisticalAnalysis()));

    actionElevatorManage=new QAction("电梯管理",actionGroup);
    actionElevatorManage->setIcon(QIcon(strIconElevatorManage));
    actionElevatorManage->setCheckable(true);
    connect(actionElevatorManage,SIGNAL(triggered(bool)),this,SLOT(slotElevatorManage()));

    actionSystemSetting=new QAction("系统设置",actionGroup);
    actionSystemSetting->setIcon(QIcon(strIconSystemSetting));
    actionSystemSetting->setCheckable(true);
    connect(actionSystemSetting,SIGNAL(triggered(bool)),this,SLOT(slotSystemSetting()));

    actionHelpSupport=new QAction("帮助支持",actionGroup);
    actionHelpSupport->setIcon(QIcon(strIconHelpSupport));
    actionHelpSupport->setCheckable(true);
    connect(actionHelpSupport,SIGNAL(triggered(bool)),this,SLOT(slotHelpSupport()));

    actionExitApp=new QAction("退出程序",this);
    actionExitApp->setIcon(QIcon(strIconExitApp));
    connect(actionExitApp,SIGNAL(triggered(bool)),qApp,SLOT(quit()));

    ui->mainToolBar->addAction(actionConnectCardReader);
    ui->mainToolBar->addAction(actionOwnerCard);
    ui->mainToolBar->addAction(actionManagerCard);
    ui->mainToolBar->addAction(actionFunctionCard);
    ui->mainToolBar->addAction(actionRemoteOperation);
    ui->mainToolBar->addAction(actionStatisticalAnalysis);
    ui->mainToolBar->addAction(actionElevatorManage);
    ui->mainToolBar->addAction(actionSystemSetting);
    ui->mainToolBar->addAction(actionHelpSupport);
    ui->mainToolBar->addAction(actionExitApp);
}

void MainWindow::InitTabs()
{
    //主窗体Tabs初始化
    layoutVBoxTabs=new QVBoxLayout;

    tabOwnerCard=new TabWidget_OwnerCard();
    tabManagerCard=new TabWidget_ManagerCard();
    tabFunctionCard=new TabWidget_FunctionCard();
    tabRemoteOperation=new TabWidget_RemoteOperation();
    tabStatisticalAnalysis=new TabWidget_StatisticalAnalysis();
    tabElevatorManage=new TabWidget_ElevatorManage();
    tabSystemSetting=new TabWidget_SystemSetting();
    tabHelpSupport=new TabWidget_HelpSupport();

    layoutVBoxTabs->addWidget(tabOwnerCard);
    layoutVBoxTabs->addWidget(tabManagerCard);
    layoutVBoxTabs->addWidget(tabFunctionCard);
    layoutVBoxTabs->addWidget(tabRemoteOperation);
    layoutVBoxTabs->addWidget(tabStatisticalAnalysis);
    layoutVBoxTabs->addWidget(tabElevatorManage);
    layoutVBoxTabs->addWidget(tabSystemSetting);
    layoutVBoxTabs->addWidget(tabHelpSupport);
}

void MainWindow::InitVBoxInfos()
{
    //主窗体信息窗口初始化
    txtbrwInfos=new QTextBrowser();

    btnReadCard=new QPushButton("读取卡信息");
    btnReadCard->setObjectName("objectBtnReadCard");
    btnReadCard->setFixedHeight(50);
    connect(btnReadCard,SIGNAL(clicked(bool)),this,SLOT(slotBtnReadCard()));

    btnInitCard=new QPushButton("初始化卡信息");
    btnInitCard->setObjectName("objectBtnInitCard");
    btnInitCard->setFixedHeight(50);
    connect(btnInitCard,SIGNAL(clicked(bool)),this,SLOT(slotBtnInitCard()));

    layoutVBoxInfos=new QVBoxLayout;
    layoutVBoxInfos->addSpacing(20);
    layoutVBoxInfos->addWidget(txtbrwInfos);
    layoutVBoxInfos->addSpacing(10);
    layoutVBoxInfos->addWidget(btnReadCard);
    layoutVBoxInfos->addWidget(btnInitCard);

    grpboxInfos=new QGroupBox("信息窗口");
    grpboxInfos->setObjectName("objectGrpboxInfos");
    grpboxInfos->setFixedWidth(300);
    grpboxInfos->setLayout(layoutVBoxInfos);
}

void MainWindow::TabWidgetDisplay(ushort nIndex)
{
    switch (nIndex)
    {
    case 0:
        tabOwnerCard->show();
        tabManagerCard->hide();
        tabFunctionCard->hide();
        tabRemoteOperation->hide();
        tabStatisticalAnalysis->hide();
        tabElevatorManage->hide();
        tabSystemSetting->hide();
        tabHelpSupport->hide();
        break;
    case 1:
        tabOwnerCard->hide();
        tabManagerCard->show();
        tabFunctionCard->hide();
        tabRemoteOperation->hide();
        tabStatisticalAnalysis->hide();
        tabElevatorManage->hide();
        tabSystemSetting->hide();
        tabHelpSupport->hide();
        break;
    case 2:
        tabOwnerCard->hide();
        tabManagerCard->hide();
        tabFunctionCard->show();
        tabRemoteOperation->hide();
        tabStatisticalAnalysis->hide();
        tabElevatorManage->hide();
        tabSystemSetting->hide();
        tabHelpSupport->hide();
        break;
    case 3:
        tabOwnerCard->hide();
        tabManagerCard->hide();
        tabFunctionCard->hide();
        tabRemoteOperation->show();
        tabStatisticalAnalysis->hide();
        tabElevatorManage->hide();
        tabSystemSetting->hide();
        tabHelpSupport->hide();
        break;
    case 4:
        tabOwnerCard->hide();
        tabManagerCard->hide();
        tabFunctionCard->hide();
        tabRemoteOperation->hide();
        tabStatisticalAnalysis->show();
        tabElevatorManage->hide();
        tabSystemSetting->hide();
        tabHelpSupport->hide();
        break;
    case 5:
        tabOwnerCard->hide();
        tabManagerCard->hide();
        tabFunctionCard->hide();
        tabRemoteOperation->hide();
        tabStatisticalAnalysis->hide();
        tabElevatorManage->show();
        tabSystemSetting->hide();
        tabHelpSupport->hide();
        break;
    case 6:
        tabOwnerCard->hide();
        tabManagerCard->hide();
        tabFunctionCard->hide();
        tabRemoteOperation->hide();
        tabStatisticalAnalysis->hide();
        tabElevatorManage->hide();
        tabSystemSetting->show();
        tabHelpSupport->hide();
        break;
    case 7:
        tabOwnerCard->hide();
        tabManagerCard->hide();
        tabFunctionCard->hide();
        tabRemoteOperation->hide();
        tabStatisticalAnalysis->hide();
        tabElevatorManage->hide();
        tabSystemSetting->hide();
        tabHelpSupport->show();
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    CH375SetDeviceNotify(0,NULL,NULL);//关闭指定序号设备插拔监视

    //注意：子对象销毁之后才能销毁父对象
    delete ui;

    delete actionConnectCardReader;
    delete actionOwnerCard;
    delete actionManagerCard;
    delete actionFunctionCard;
    delete actionRemoteOperation;
    delete actionStatisticalAnalysis;
    delete actionElevatorManage;
    delete actionSystemSetting;
    delete actionHelpSupport;
    delete actionExitApp;
    delete actionGroup;

    delete layoutVBoxInfos;
    delete txtbrwInfos;
    delete btnReadCard;
    delete btnInitCard;
    delete grpboxInfos;

    delete layoutVBoxTabs;
    delete tabOwnerCard;
    delete tabManagerCard;
    delete tabFunctionCard;
    delete tabRemoteOperation;
    delete tabStatisticalAnalysis;
    delete tabElevatorManage;
    delete tabSystemSetting;
    delete tabHelpSupport;

    delete layoutHBoxMain;

    delete setIniFile;
}
