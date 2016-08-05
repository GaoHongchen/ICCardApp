#include "tabwidget_functioncard.h"
#include "ui_tabwidget_functioncard.h"

#include "../mainwindow.h"

#include <QRegExp>
#include <QRegExpValidator>

TabWidget_FunctionCard::TabWidget_FunctionCard(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TabWidget_FunctionCard)
{
    ui->setupUi(this);

    //启禁用卡
    ui->enablecardLineEditNum1->setValidator(new QIntValidator(0,99999));
    ui->enablecardLineEditNum2->setValidator(new QIntValidator(0,99999));
    ui->enablecardLineEditNum3->setValidator(new QIntValidator(0,99999));
    ui->enablecardLineEditNum4->setValidator(new QIntValidator(0,99999));

    //时间设置卡
    ui->timesetDTEditCtrl->setDateTime(QDateTime::currentDateTime());

    QRegExp double_rx("([0-2][\.][0-9]{0,1})");
    QValidator *validatorTimeOne=new QRegExpValidator(double_rx);
    ui->timesetLineEditKeyRespOne->setValidator(validatorTimeOne);

    ui->timesetLineEditKeyRespMulti->setValidator(new QIntValidator(1,10));

//    this->removeTab(2);
//    this->removeTab(2);
//    this->removeTab(3);
}

TabWidget_FunctionCard::~TabWidget_FunctionCard()
{
    delete ui;
}

void TabWidget_FunctionCard::on_timesetPushBtnWrite_clicked()
{
    DS_TimeSetting dsTimeSet;
    dsTimeSet.structTimeSet.ProjectID=0x06;
    dsTimeSet.structTimeSet.CardType=0x06;
    //控制器时间设置
    if(ui->timesetRadioBtnCtrl->isChecked())
    {
        dsTimeSet.structTimeSet.TimeSetType=SetType::SetControlerTime;
        QDateTime datetime=ui->timesetDTEditCtrl->dateTime();
        if(!datetime.isValid())
        {
            QMessageBox::warning(this,"警告","时间日期格式错误或为空！",QMessageBox::Yes);
        }
        QString strQDateTime=datetime.toString("yyyyMMddhhmm");
        std::string strDateTime=strQDateTime.toStdString();
        std::string strYearH    =strDateTime.substr(0,2);
        std::string strYearL    =strDateTime.substr(2,2);
        std::string strMon      =strDateTime.substr(4,2);
        std::string strDay      =strDateTime.substr(6,2);
        std::string strHour     =strDateTime.substr(8,2);
        std::string strMin      =strDateTime.substr(10,2);
        dsTimeSet.structTimeSet.ControlerTime[0]=TypeConvert::stdstring2intHex(strYearH.c_str());
        dsTimeSet.structTimeSet.ControlerTime[1]=TypeConvert::stdstring2intHex(strYearL.c_str());
        dsTimeSet.structTimeSet.ControlerTime[2]=TypeConvert::stdstring2intHex(strMon.c_str());
        dsTimeSet.structTimeSet.ControlerTime[3]=TypeConvert::stdstring2intHex(strDay.c_str());
        dsTimeSet.structTimeSet.ControlerTime[4]=TypeConvert::stdstring2intHex(strHour.c_str());
        dsTimeSet.structTimeSet.ControlerTime[5]=TypeConvert::stdstring2intHex(strMin.c_str());
    }
    //按钮响应时间
    if(ui->timesetRadioBtnKeyResp->isChecked())
    {
        dsTimeSet.structTimeSet.TimeSetType=SetType::SetKeyResponseTime;
        QString strQTimeOne=ui->timesetLineEditKeyRespOne->text();
        if(strQTimeOne.isEmpty())
        {
            QMessageBox::warning(this,"警告","请输入数据！",QMessageBox::Yes);
            return;
        }
        float fTimeOne = strQTimeOne.toFloat();
        int nTimeOne = fTimeOne*10;
        if(nTimeOne>=0x01 && nTimeOne<=0x19)
        {
            dsTimeSet.structTimeSet.SingleSelectTime=nTimeOne;
        }
        else
        {
            QMessageBox::warning(this,"错误","单选按键响应时间超出范围！",QMessageBox::Yes);
            return;
        }

        QString strQTimeMul=ui->timesetLineEditKeyRespMulti->text();
        int nTimeMul=strQTimeMul.toInt();
        if(nTimeMul>=1 && nTimeMul<=10)
        {
            dsTimeSet.structTimeSet.MultiSelectTime=nTimeMul;
        }
        else
        {
            QMessageBox::warning(this,"错误","多选按键响应时间超出范围！",QMessageBox::Yes);
            return;
        }
    }
    //访客按钮响应时间
    if(ui->timesetRadioBtnVisitorKey->isChecked())
    {
        dsTimeSet.structTimeSet.TimeSetType=SetType::SetVisitorResponseTime;
        QString strQTimeVisitor=ui->timesetLineEditVisitorKey->text();
        if(strQTimeVisitor.isEmpty())
        {
            QMessageBox::warning(this,"警告","请输入数据！",QMessageBox::Yes);
            return;
        }
        int nTimeVisitor = strQTimeVisitor.toInt();
        dsTimeSet.structTimeSet.VisitorTime[0]=HIBYTE(nTimeVisitor);
        dsTimeSet.structTimeSet.VisitorTime[1]=LOBYTE(nTimeVisitor);
    }

    uchar *strTimeSet = dsTimeSet.DS2chars();
//    uchar chTimeSet[13]={0};
//    for(int i=0;i<13;i++)
//    {
//        chTimeSet[i]=strTimeSet[i];
//    }
    MainWindow *pMainWnd = MainWindow::pMainWnd;//主窗口指针
    if(pMainWnd->ch375rw.bIsOpened)
    {
        if(pMainWnd->ch375rw.Write(0x00,13,strTimeSet))
        {
            Sleep(TIME_DELAY);
            pMainWnd->ch375rw.Beep(1);
            pMainWnd->txtbrwInfos->setText("====数据写入成功====");
        }
    }
}

void TabWidget_FunctionCard::on_ClearMemoryPushBtnWrite_clicked()
{
    if(ui->clearmemoryRadioBtn->isChecked())
    {
        uchar chCM[8]={0};
        chCM[0]=0x06;
        chCM[1]=0x0B;//卡类型：0x0B
        MainWindow *pMainWnd = MainWindow::pMainWnd;//主窗口指针
        if(pMainWnd->ch375rw.bIsOpened)
        {
            if(pMainWnd->ch375rw.Write(0x00,8,chCM))
            {
                Sleep(TIME_DELAY);
                pMainWnd->ch375rw.Beep(1);
                pMainWnd->txtbrwInfos->setText("====数据写入成功====");
            }
        }
    }
    else
    {
        QMessageBox::warning(this,"警告","请选择“清内存卡”！",QMessageBox::Yes);
    }
}

void TabWidget_FunctionCard::on_addrsetPushBtn_clicked()
{
    QString strQAddrSet=ui->addrsetLineEdit->text();
    if(strQAddrSet.isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入数据！",QMessageBox::Yes);
        return;
    }

    uchar chAddr[8]={0};
    chAddr[0] = 0x06;
    chAddr[1] = 0x0A;//卡类型：0x0A
    int nAddr = strQAddrSet.toInt();//地址设定
    if(nAddr>0 && nAddr<256)
    {
        chAddr[2] = nAddr;
        MainWindow *pMainWnd = MainWindow::pMainWnd;//主窗口指针
        if(pMainWnd->ch375rw.bIsOpened)
        {
            if(pMainWnd->ch375rw.Write(0x00,8,chAddr))
            {
                Sleep(TIME_DELAY);
                pMainWnd->ch375rw.Beep(1);
                pMainWnd->txtbrwInfos->setText("====数据写入成功====");
            }
        }
    }
    else
    {
        QMessageBox::warning(this,"警告","地址数据超出范围！",QMessageBox::Yes);
    }
}

void TabWidget_FunctionCard::on_enablecardPushBtnWrite_clicked()
{
    MainWindow *pMainWnd = MainWindow::pMainWnd;//主窗口指针
    pMainWnd->ch375rw.Read(0x00,2);
    Sleep(TIME_DELAY);
    UCHAR *chData = pMainWnd->ch375rw.Read(0x00,2);
    if(int(chData[1])==0x00)
    {
        QMessageBox::critical(this,"警告","此卡不是新卡！",QMessageBox::Yes);
    }

    DS_EnableCard dsEnableCard;
    dsEnableCard.structEnableCard.ProjectID=0x06;//项目ID
    dsEnableCard.structEnableCard.CardType=0x04;//卡类型
    //电梯编号
    QString strQLiftNum=ui->enablecardLineEditLiftNum->text();
    if(strQLiftNum.isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入电梯编号！",QMessageBox::Yes);
        return;
    }
    int nLiftNum = strQLiftNum.toInt();
    dsEnableCard.structEnableCard.LiftNum=nLiftNum;
    //启禁用类型
    if(ui->enablecardRadioBtnCardNum->isChecked())//按卡号
    {
        dsEnableCard.structEnableCard.EnableType=0x01;
    }
    if(ui->enablecardRadioBtnRoomNum->isChecked())//按房号
    {
        dsEnableCard.structEnableCard.EnableType=0x02;
    }
    //受限卡类型
    ushort nIndexCardType=ui->enablecardComBoxCardType->currentIndex()+1;
    switch(nIndexCardType)
    {
    case 0://用户卡
        dsEnableCard.structEnableCard.LimitCardType=0x01;
        break;
    case 1://管理人卡
        dsEnableCard.structEnableCard.LimitCardType=0x02;
        break;
    }
    ushort nEnableNum=0;
    // 1
    QString strQNum1=ui->enablecardLineEditNum1->text();
    if(strQNum1.isEmpty())
    {
        memset(dsEnableCard.structEnableCard.Num1,1,4);
        dsEnableCard.structEnableCard.IsEnable1=0x00;
    }
    else
    {
        nEnableNum++;
        //启禁
        if(ui->enablecardRadioBtn1T->isChecked())
        {
            dsEnableCard.structEnableCard.IsEnable1=0x01;
        }
        if(ui->enablecardRadioBtn1F->isChecked())
        {
            dsEnableCard.structEnableCard.IsEnable1=0x02;
        }
        //卡号或房间号
        std::string strNum1 = strQNum1.toStdString();
        if(ui->enablecardRadioBtnCardNum->isChecked())//按卡号
        {
            if(5==strNum1.length())
            {
                dsEnableCard.structEnableCard.Num1[0]=0x00;
                dsEnableCard.structEnableCard.Num1[1]=
                        std::atoi(strNum1.substr(0,1).c_str());
                dsEnableCard.structEnableCard.Num1[2]=
                        std::atoi(strNum1.substr(1,2).c_str());
                dsEnableCard.structEnableCard.Num1[3]=
                        std::atoi(strNum1.substr(3,2).c_str());
            }
            else
            {
                QMessageBox::warning(this,"警告","卡号应为5位数！",QMessageBox::Yes);
                return;
            }
        }
        if(ui->enablecardRadioBtnRoomNum->isChecked())//按房号
        {
            if(4==strNum1.length())
            {
                dsEnableCard.structEnableCard.Num1[0]=0x00;
                dsEnableCard.structEnableCard.Num1[1]=0x00;
                dsEnableCard.structEnableCard.Num1[2]=
                        std::atoi(strNum1.substr(0,2).c_str());
                dsEnableCard.structEnableCard.Num1[3]=
                        std::atoi(strNum1.substr(2,2).c_str());
            }
            else
            {
                QMessageBox::warning(this,"警告","房号应为4位数！",QMessageBox::Yes);
                return;
            }
        }
    }

    // 2
    QString strQNum2=ui->enablecardLineEditNum2->text();
    if(strQNum2.isEmpty())
    {
        memset(dsEnableCard.structEnableCard.Num2,1,4);
        dsEnableCard.structEnableCard.IsEnable2=0x00;
    }
    else
    {
        nEnableNum++;
        //启禁
        if(ui->enablecardRadioBtn2T->isChecked())
        {
            dsEnableCard.structEnableCard.IsEnable2=0x01;
        }
        if(ui->enablecardRadioBtn2F->isChecked())
        {
            dsEnableCard.structEnableCard.IsEnable2=0x02;
        }
        //卡号或房间号
        std::string strNum2 = strQNum2.toStdString();
        if(ui->enablecardRadioBtnCardNum->isChecked())//按卡号
        {
            if(5==strNum2.length())
            {
                dsEnableCard.structEnableCard.Num2[0]=0x00;
                dsEnableCard.structEnableCard.Num2[1]=
                        std::atoi(strNum2.substr(0,1).c_str());
                dsEnableCard.structEnableCard.Num2[2]=
                        std::atoi(strNum2.substr(1,2).c_str());
                dsEnableCard.structEnableCard.Num2[3]=
                        std::atoi(strNum2.substr(3,2).c_str());
            }
            else
            {
                QMessageBox::warning(this,"警告","卡号应为5位数！",QMessageBox::Yes);
                return;
            }
        }
        if(ui->enablecardRadioBtnRoomNum->isChecked())//按房号
        {
            if(4==strNum2.length())
            {
                dsEnableCard.structEnableCard.Num2[0]=0x00;
                dsEnableCard.structEnableCard.Num2[1]=0x00;
                dsEnableCard.structEnableCard.Num2[2]=
                        std::atoi(strNum2.substr(0,2).c_str());
                dsEnableCard.structEnableCard.Num2[3]=
                        std::atoi(strNum2.substr(2,2).c_str());
            }
            else
            {
                QMessageBox::warning(this,"警告","房号应为4位数！",QMessageBox::Yes);
                return;
            }
        }
    }

    // 3
    QString strQNum3=ui->enablecardLineEditNum3->text();
    if(strQNum3.isEmpty())
    {
        memset(dsEnableCard.structEnableCard.Num3,1,4);
        dsEnableCard.structEnableCard.IsEnable3=0x00;
    }
    else
    {
        nEnableNum++;
        //启禁
        if(ui->enablecardRadioBtn3T->isChecked())
        {
            dsEnableCard.structEnableCard.IsEnable3=0x01;
        }
        if(ui->enablecardRadioBtn3F->isChecked())
        {
            dsEnableCard.structEnableCard.IsEnable3=0x02;
        }
        //卡号或房间号
        std::string strNum3 = strQNum3.toStdString();
        if(ui->enablecardRadioBtnCardNum->isChecked())//按卡号
        {
            if(5==strNum3.length())
            {
                dsEnableCard.structEnableCard.Num3[0]=0x00;
                dsEnableCard.structEnableCard.Num3[1]=
                        std::atoi(strNum3.substr(0,1).c_str());
                dsEnableCard.structEnableCard.Num3[2]=
                        std::atoi(strNum3.substr(1,2).c_str());
                dsEnableCard.structEnableCard.Num3[3]=
                        std::atoi(strNum3.substr(3,2).c_str());
            }
            else
            {
                QMessageBox::warning(this,"警告","卡号应为5位数！",QMessageBox::Yes);
                return;
            }
        }
        if(ui->enablecardRadioBtnRoomNum->isChecked())//按房号
        {
            if(4==strNum3.length())
            {
                dsEnableCard.structEnableCard.Num3[0]=0x00;
                dsEnableCard.structEnableCard.Num3[1]=0x00;
                dsEnableCard.structEnableCard.Num3[2]=
                        std::atoi(strNum3.substr(0,2).c_str());
                dsEnableCard.structEnableCard.Num3[3]=
                        std::atoi(strNum3.substr(2,2).c_str());
            }
            else
            {
                QMessageBox::warning(this,"警告","房号应为4位数！",QMessageBox::Yes);
                return;
            }
        }
    }

    // 4
    QString strQNum4=ui->enablecardLineEditNum4->text();
    if(strQNum4.isEmpty())
    {
        memset(dsEnableCard.structEnableCard.Num4,1,4);
        dsEnableCard.structEnableCard.IsEnable4=0x00;
    }
    else
    {
        nEnableNum++;
        //启禁
        if(ui->enablecardRadioBtn4T->isChecked())
        {
            dsEnableCard.structEnableCard.IsEnable4=0x01;
        }
        if(ui->enablecardRadioBtn4F->isChecked())
        {
            dsEnableCard.structEnableCard.IsEnable4=0x02;
        }
        //卡号或房间号
        std::string strNum4 = strQNum4.toStdString();
        if(ui->enablecardRadioBtnCardNum->isChecked())//按卡号
        {
            if(5==strNum4.length())
            {
                dsEnableCard.structEnableCard.Num4[0]=0x00;
                dsEnableCard.structEnableCard.Num4[1]=
                        std::atoi(strNum4.substr(0,1).c_str());
                dsEnableCard.structEnableCard.Num4[2]=
                        std::atoi(strNum4.substr(1,2).c_str());
                dsEnableCard.structEnableCard.Num4[3]=
                        std::atoi(strNum4.substr(3,2).c_str());
            }
            else
            {
                QMessageBox::warning(this,"警告","卡号应为5位数！",QMessageBox::Yes);
                return;
            }
        }
        if(ui->enablecardRadioBtnRoomNum->isChecked())//按房号
        {
            if(4==strNum4.length())
            {
                dsEnableCard.structEnableCard.Num4[0]=0x00;
                dsEnableCard.structEnableCard.Num4[1]=0x00;
                dsEnableCard.structEnableCard.Num4[2]=
                        std::atoi(strNum4.substr(0,2).c_str());
                dsEnableCard.structEnableCard.Num4[3]=
                        std::atoi(strNum4.substr(2,2).c_str());
            }
            else
            {
                QMessageBox::warning(this,"警告","房号应为4位数！",QMessageBox::Yes);
                return;
            }
        }
    }
    //数量
    if(nEnableNum==0)
    {
        QMessageBox::warning(this,"警告","请填入卡号或房间号！",QMessageBox::Yes);
        return;
    }
    dsEnableCard.structEnableCard.EnableNum=nEnableNum;

    uchar *strEnableCard = dsEnableCard.DS2chars();
    if(pMainWnd->ch375rw.bIsOpened)
    {
        if(pMainWnd->ch375rw.Write(0x00,26,strEnableCard))
        {
            Sleep(TIME_DELAY);
            pMainWnd->ch375rw.Beep(1);
            pMainWnd->txtbrwInfos->setText("====数据写入成功====");
        }
    }
}

void TabWidget_FunctionCard::on_enablecardRadioBtnCardNum_toggled(bool checked)
{
    ui->enablecardLabelNumType1->setText("卡 号");
    ui->enablecardLabelNumType2->setText("卡 号");
    ui->enablecardLabelNumType3->setText("卡 号");
    ui->enablecardLabelNumType4->setText("卡 号");

    ui->enablecardLabelNumSize1->setText("(5位数字)");
    ui->enablecardLabelNumSize2->setText("(5位数字)");
    ui->enablecardLabelNumSize3->setText("(5位数字)");
    ui->enablecardLabelNumSize4->setText("(5位数字)");
}

void TabWidget_FunctionCard::on_enablecardRadioBtnRoomNum_toggled(bool checked)
{
    ui->enablecardLabelNumType1->setText("房 间 号");
    ui->enablecardLabelNumType2->setText("房 间 号");
    ui->enablecardLabelNumType3->setText("房 间 号");
    ui->enablecardLabelNumType4->setText("房 间 号");

    ui->enablecardLabelNumSize1->setText("(4位数字)");
    ui->enablecardLabelNumSize2->setText("(4位数字)");
    ui->enablecardLabelNumSize3->setText("(4位数字)");
    ui->enablecardLabelNumSize4->setText("(4位数字)");
}

void TabWidget_FunctionCard::on_enablecardPushBtnSelLift_clicked()
{
    SelectLiftDlg dlgSelectLift;
    dlgSelectLift.show();
    if(dlgSelectLift.exec() == QDialog::Accepted)
    {
        enablecardArrValuesLiftInfos.clear();
        std::vector<QString>().swap(enablecardArrValuesLiftInfos);
        enablecardArrValuesLiftInfos = dlgSelectLift.arrValues;
        enablecardLiftNum = QString(enablecardArrValuesLiftInfos[0]).toInt();
        ui->enablecardLineEditLiftNum->setText(QString::number(enablecardLiftNum));
    }
}

void TabWidget_FunctionCard::on_sysswitchRadioBtnSys_toggled(bool checked)
{
    ui->sysswitchGrpBoxFlag->setEnabled(false);
    ui->sysswitchGrpBoxLiftInfo->setEnabled(false);
}

void TabWidget_FunctionCard::on_sysswitchRadioBtnLayer_toggled(bool checked)
{
    ui->sysswitchGrpBoxFlag->setEnabled(true);
    ui->sysswitchGrpBoxLiftInfo->setEnabled(true);
}

void TabWidget_FunctionCard::on_sysswitchRadioBtnCommonFloor_toggled(bool checked)
{
    ui->sysswitchGrpBoxFlag->setEnabled(true);
    ui->sysswitchGrpBoxLiftInfo->setEnabled(true);
}

void TabWidget_FunctionCard::on_sysswitchPushBtnLift_clicked()
{
    SelectLiftDlg dlgSelectLift;
    dlgSelectLift.show();
    if(dlgSelectLift.exec() == QDialog::Accepted)
    {
        sysswitchArrValuesLiftInfos.clear();
        std::vector<QString>().swap(sysswitchArrValuesLiftInfos);
        sysswitchArrValuesLiftInfos = dlgSelectLift.arrValues;
        sysswitchLiftNum = QString(sysswitchArrValuesLiftInfos[0]).toInt();
        ui->sysswitchLineEditLiftNum->setText(QString::number(sysswitchLiftNum));
        ui->sysswitchLineEditFloorNum->clear();
    }
}

void TabWidget_FunctionCard::on_sysswitchPushBtnFloor_clicked()
{
    if(ui->sysswitchLineEditLiftNum->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请先选择电梯！",QMessageBox::Yes);
        return;
    }
    std::vector<QString> arrValues;
    arrValues.push_back(QString(sysswitchArrValuesLiftInfos[1]));
    arrValues.push_back(QString(sysswitchArrValuesLiftInfos[2]));
    arrValues.push_back(QString(sysswitchArrValuesLiftInfos[3]));
    arrValues.push_back(QString(sysswitchArrValuesLiftInfos[4]));

    SelectFloorDlg dlgSelectFloor;
    dlgSelectFloor.ModifyFloorInfo(arrValues);
    dlgSelectFloor.show();
    if(dlgSelectFloor.exec() == QDialog::Accepted)
    {
        sysswitchMapFloorsA=dlgSelectFloor.mapFloorsA;
        QString strFloors;
        std::map<int,QString>::iterator it;
        for(it=sysswitchMapFloorsA.begin();it!=sysswitchMapFloorsA.end();++it)
        {
            strFloors += it->second + ",";
        }
        strFloors.remove(strFloors.length()-1,1);
        ui->sysswitchLineEditFloorNum->setText("A门："+strFloors+";");
    }
}

void TabWidget_FunctionCard::on_sysswitchPushBtnFind_clicked()
{
    SelectSysSwitchDlg dlgSelectSysSwitch;
    dlgSelectSysSwitch.show();
    if(dlgSelectSysSwitch.exec() == QDialog::Accepted)
    {

    }
}

void TabWidget_FunctionCard::on_sysswitchPushBtnReissue_clicked()
{

}

void TabWidget_FunctionCard::on_sysswitchPushBtnWrite_clicked()
{
    DS_SysSwitchCard dsSysSwitchCard;
    dsSysSwitchCard.structSysSwitchCard.ProjectID = 0x06;
    dsSysSwitchCard.structSysSwitchCard.CardType = 0x08;
    if(ui->sysswitchRadioBtnSys->isChecked())//系统开关卡
    {
        dsSysSwitchCard.structSysSwitchCard.SwitchCardType = SWCardType::SysSwitch;
    }
    if(ui->sysswitchRadioBtnLayer->isChecked())//分层开关卡
    {
        //开关卡类型
        dsSysSwitchCard.structSysSwitchCard.SwitchCardType = SWCardType::LayerSwitch;
        //开关标志
        if(ui->sysswitchRadioBtnOpen->isChecked())
        {
            dsSysSwitchCard.structSysSwitchCard.SwitchFlag=0x11;
        }
        if(ui->sysswitchRadioBtnClose->isChecked())
        {
            dsSysSwitchCard.structSysSwitchCard.SwitchFlag=0x22;
        }
        //设备号/可用电梯号,sysswitchLiftNum从1开始
        if(ui->sysswitchLineEditLiftNum->text().isEmpty())
        {
            QMessageBox::warning(this,"警告","请选择电梯！",QMessageBox::Yes);
            return;
        }
        for(int i=0;i<32;i++)
        {
            dsSysSwitchCard.structSysSwitchCard.LiftNum[i]=0x00;
        }
        dsSysSwitchCard.structSysSwitchCard.LiftNum[(sysswitchLiftNum-1)/8]
                |= 1<<((sysswitchLiftNum-1)%8);

        //受控楼层
        if(ui->sysswitchLineEditFloorNum->text().isEmpty())
        {
            QMessageBox::warning(this,"警告","请选择楼层！",QMessageBox::Yes);
            return;
        }
        // A
        for(int i=0;i<6;i++)
        {
            dsSysSwitchCard.structSysSwitchCard.FloorsA[i]=0x00;
        }
        std::map<int,QString>::iterator it;
        for(it=sysswitchMapFloorsA.begin();it!=sysswitchMapFloorsA.end();++it)
        {
            int nFloor = int(it->first);
            dsSysSwitchCard.structSysSwitchCard.FloorsA[(nFloor)/8]
                    |= 1<<((nFloor)%8);
        }
        // B 保留
        for(int i=0;i<6;i++)
        {
            dsSysSwitchCard.structSysSwitchCard.FloorsB[i]=0x00;
        }
    }
    if(ui->sysswitchRadioBtnCommonFloor->isChecked())//公共楼层设置卡
    {
        //开关卡类型
        dsSysSwitchCard.structSysSwitchCard.SwitchCardType = SWCardType::PublicFloorsSet;
        //开关标志
        if(ui->sysswitchRadioBtnOpen->isChecked())
        {
            dsSysSwitchCard.structSysSwitchCard.SwitchFlag=0x11;
        }
        if(ui->sysswitchRadioBtnClose->isChecked())
        {
            dsSysSwitchCard.structSysSwitchCard.SwitchFlag=0x22;
        }
        //设备号/可用电梯号,sysswitchLiftNum从1开始
        if(ui->sysswitchLineEditLiftNum->text().isEmpty())
        {
            QMessageBox::warning(this,"警告","请选择电梯！",QMessageBox::Yes);
            return;
        }
        for(int i=0;i<32;i++)
        {
            dsSysSwitchCard.structSysSwitchCard.LiftNum[i]=0x00;
        }
        dsSysSwitchCard.structSysSwitchCard.LiftNum[(sysswitchLiftNum-1)/8]
                |= 1<<((sysswitchLiftNum-1)%8);
        //受控楼层
        if(ui->sysswitchLineEditFloorNum->text().isEmpty())
        {
            QMessageBox::warning(this,"警告","请选择楼层！",QMessageBox::Yes);
            return;
        }
        // A
        for(int i=0;i<6;i++)
        {
            dsSysSwitchCard.structSysSwitchCard.FloorsA[i]=0x00;
        }
        std::map<int,QString>::iterator it;
        for(it=sysswitchMapFloorsA.begin();it!=sysswitchMapFloorsA.end();++it)
        {
            int nFloor = it->first;
            dsSysSwitchCard.structSysSwitchCard.FloorsA[(nFloor)/8]
                    |= 1<<((nFloor)%8);
        }
        // B 保留
        for(int i=0;i<6;i++)
        {
            dsSysSwitchCard.structSysSwitchCard.FloorsB[i]=0x00;
        }
    }

    uchar *strSysSwitchCard = dsSysSwitchCard.DS2chars();

    MainWindow *pMainWnd = MainWindow::pMainWnd;//主窗口指针
    if(pMainWnd->ch375rw.bIsOpened)
    {
        if(pMainWnd->ch375rw.Write(0x00,48,strSysSwitchCard))
        {
            Sleep(TIME_DELAY);
            pMainWnd->ch375rw.Beep(1);
            pMainWnd->txtbrwInfos->setText("====数据写入成功====");
        }
    }
}
