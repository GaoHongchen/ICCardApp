#include "tabwidget_ownercard.h"
#include "ui_tabwidget_ownercard.h"

#include "../mainwindow.h"

TabWidget_OwnerCard::TabWidget_OwnerCard(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TabWidget_OwnerCard)
{
    ui->setupUi(this);

    ui->newcardDateEditStart->setDate(QDate::currentDate());
    ui->newcardDateEditEnd->setDate(QDate::currentDate());

    ui->datachangeDateEditEnd->setDate(QDate::currentDate());
    ui->datachangeDateEditStart->setDate(QDate::currentDate());

    this->removeTab(2);

    ui->reissueDateEditEnd->setDate(QDate::currentDate());
    ui->reissueDateEditStart->setDate(QDate::currentDate());

    std::vector<QString> arrFiledsUsrCards;
    arrFiledsUsrCards.push_back("卡号");
    arrFiledsUsrCards.push_back("业主姓名");
    arrFiledsUsrCards.push_back("业主门牌");
    arrFiledsUsrCards.push_back("联系电话");
    arrFiledsUsrCards.push_back("限制日期");
    arrFiledsUsrCards.push_back("可用电梯");
    arrFiledsUsrCards.push_back("可用楼层");
    arrFiledsUsrCards.push_back("房间编号");
    modelDBUsrCard = new SqlDBModel("tableUsrCard",arrFiledsUsrCards);
}

TabWidget_OwnerCard::~TabWidget_OwnerCard()
{
    delete ui;
}

void TabWidget_OwnerCard::on_newcardPushBtnLiftNum1_clicked()
{
    SelectLiftDlg dlgSelectLift;
    dlgSelectLift.show();
    if(dlgSelectLift.exec() == QDialog::Accepted)
    {
        newcardArrValuesLiftInfos.clear();
        std::vector<QString>().swap(newcardArrValuesLiftInfos);
        newcardArrValuesLiftInfos = dlgSelectLift.arrValues;
        newcardLiftNum = QString(newcardArrValuesLiftInfos[0]).toInt();
        ui->newcardLineEditLiftNum1->setText(QString::number(newcardLiftNum));
    }
}

void TabWidget_OwnerCard::on_newcardPushBtnFloorNum1_clicked()
{
    if(ui->newcardLineEditLiftNum1->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请先选择电梯！",QMessageBox::Yes);
        return;
    }
    std::vector<QString> arrValues;
    arrValues.push_back(QString(newcardArrValuesLiftInfos[1]));
    arrValues.push_back(QString(newcardArrValuesLiftInfos[2]));
    arrValues.push_back(QString(newcardArrValuesLiftInfos[3]));
    arrValues.push_back(QString(newcardArrValuesLiftInfos[4]));

    SelectFloorDlg dlgSelectFloor;
    dlgSelectFloor.ModifyFloorInfo(arrValues);
    dlgSelectFloor.show();
    if(dlgSelectFloor.exec() == QDialog::Accepted)
    {
        newcardMapFloorsA=dlgSelectFloor.mapFloorsA;
        QString strFloors;
        std::map<int,QString>::iterator it;
        for(it=newcardMapFloorsA.begin();it!=newcardMapFloorsA.end();++it)
        {
            strFloors += it->second + ",";
        }
        strFloors.remove(strFloors.length()-1,1);
        ui->newcardLineEditFloorNum1->setText("A门："+strFloors+";");
    }
}

void TabWidget_OwnerCard::on_newcardPushBtnLiftNum2_clicked()
{
    SelectLiftDlg dlgSelectLift;
    dlgSelectLift.show();
    if(dlgSelectLift.exec() == QDialog::Accepted)
    {
        newcardArrValuesLiftInfos.clear();
        std::vector<QString>().swap(newcardArrValuesLiftInfos);
        newcardArrValuesLiftInfos = dlgSelectLift.arrValues;
        newcardLiftNum = QString(newcardArrValuesLiftInfos[0]).toInt();
        ui->newcardLineEditLiftNum2->setText(QString::number(newcardLiftNum));
    }
}

void TabWidget_OwnerCard::on_newcardPushBtnFloorNum2_clicked()
{
    if(ui->newcardLineEditLiftNum2->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请先选择电梯！",QMessageBox::Yes);
        return;
    }
    std::vector<QString> arrValues;
    arrValues.push_back(QString(newcardArrValuesLiftInfos[1]));
    arrValues.push_back(QString(newcardArrValuesLiftInfos[2]));
    arrValues.push_back(QString(newcardArrValuesLiftInfos[3]));
    arrValues.push_back(QString(newcardArrValuesLiftInfos[4]));

    SelectFloorDlg dlgSelectFloor;
    dlgSelectFloor.ModifyFloorInfo(arrValues);
    dlgSelectFloor.show();
    if(dlgSelectFloor.exec() == QDialog::Accepted)
    {
        newcardMapFloorsA=dlgSelectFloor.mapFloorsA;
        QString strFloors;
        std::map<int,QString>::iterator it;
        for(it=newcardMapFloorsA.begin();it!=newcardMapFloorsA.end();++it)
        {
            strFloors += it->second + ",";
        }
        strFloors.remove(strFloors.length()-1,1);
        ui->newcardLineEditFloorNum2->setText("A门："+strFloors+";");
    }
}

void TabWidget_OwnerCard::on_newcardPushBtnLiftNum3_clicked()
{
    SelectLiftDlg dlgSelectLift;
    dlgSelectLift.show();
    if(dlgSelectLift.exec() == QDialog::Accepted)
    {
        newcardArrValuesLiftInfos.clear();
        std::vector<QString>().swap(newcardArrValuesLiftInfos);
        newcardArrValuesLiftInfos = dlgSelectLift.arrValues;
        newcardLiftNum = QString(newcardArrValuesLiftInfos[0]).toInt();
        ui->newcardLineEditLiftNum3->setText(QString::number(newcardLiftNum));
    }
}

void TabWidget_OwnerCard::on_newcardPushBtnFloorNum3_clicked()
{
    if(ui->newcardLineEditLiftNum3->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请先选择电梯！",QMessageBox::Yes);
        return;
    }
    std::vector<QString> arrValues;
    arrValues.push_back(QString(newcardArrValuesLiftInfos[1]));
    arrValues.push_back(QString(newcardArrValuesLiftInfos[2]));
    arrValues.push_back(QString(newcardArrValuesLiftInfos[3]));
    arrValues.push_back(QString(newcardArrValuesLiftInfos[4]));

    SelectFloorDlg dlgSelectFloor;
    dlgSelectFloor.ModifyFloorInfo(arrValues);
    dlgSelectFloor.show();
    if(dlgSelectFloor.exec() == QDialog::Accepted)
    {
        newcardMapFloorsA=dlgSelectFloor.mapFloorsA;
        QString strFloors;
        std::map<int,QString>::iterator it;
        for(it=newcardMapFloorsA.begin();it!=newcardMapFloorsA.end();++it)
        {
            strFloors += it->second + ",";
        }
        strFloors.remove(strFloors.length()-1,1);
        ui->newcardLineEditFloorNum3->setText("A门："+strFloors+";");
    }
}

void TabWidget_OwnerCard::on_newcardPushBtnWrite_clicked()
{
#ifdef USE_CH375
    DS_UserCard dsUserCard;

    //限制日期
    if(ui->newcardRadioButtonLimitDate->isChecked())
    {
        QDate dateStart=ui->newcardDateEditStart->date();
        QDate dateEnd = ui->newcardDateEditEnd->date();
        if(!dateStart.isValid() || !dateEnd.isValid())
        {
            QMessageBox::warning(this,"警告","日期格式错误或为空！",QMessageBox::Yes);
        }
        QString strQDateStart=dateStart.toString("yyyyMMdd");
        QString strQDateEnd=dateEnd.toString("yyyyMMdd");
        std::string strDateTimeStart=strQDateStart.toStdString();
        std::string strYearHStart =strDateTimeStart.substr(0,2);
        std::string strYearLStart =strDateTimeStart.substr(2,2);
        std::string strMonStart   =strDateTimeStart.substr(4,2);
        std::string strDayStart   =strDateTimeStart.substr(6,2);
        std::string strDateTimeEnd=strQDateEnd.toStdString();
        std::string strYearHEnd =strDateTimeEnd.substr(0,2);
        std::string strYearLEnd =strDateTimeEnd.substr(2,2);
        std::string strMonEnd   =strDateTimeEnd.substr(4,2);
        std::string strDayEnd   =strDateTimeEnd.substr(6,2);
        dsUserCard.structUserCard.LimitDate1[0]=TypeConvert::stdstring2intHex(strYearHStart.c_str());
        dsUserCard.structUserCard.LimitDate1[1]=TypeConvert::stdstring2intHex(strYearLStart.c_str());
        dsUserCard.structUserCard.LimitDate1[2]=TypeConvert::stdstring2intHex(strMonStart.c_str());
        dsUserCard.structUserCard.LimitDate1[3]=TypeConvert::stdstring2intHex(strDayStart.c_str());
        dsUserCard.structUserCard.LimitDate1[0]=TypeConvert::stdstring2intHex(strYearHEnd.c_str());
        dsUserCard.structUserCard.LimitDate1[1]=TypeConvert::stdstring2intHex(strYearLEnd.c_str());
        dsUserCard.structUserCard.LimitDate1[2]=TypeConvert::stdstring2intHex(strMonEnd.c_str());
        dsUserCard.structUserCard.LimitDate1[3]=TypeConvert::stdstring2intHex(strDayEnd.c_str());
        dsUserCard.structUserCard.LimitDate2[0]=TypeConvert::stdstring2intHex(strYearHStart.c_str());
        dsUserCard.structUserCard.LimitDate2[1]=TypeConvert::stdstring2intHex(strYearLStart.c_str());
        dsUserCard.structUserCard.LimitDate2[2]=TypeConvert::stdstring2intHex(strMonStart.c_str());
        dsUserCard.structUserCard.LimitDate2[3]=TypeConvert::stdstring2intHex(strDayStart.c_str());
        dsUserCard.structUserCard.LimitDate2[0]=TypeConvert::stdstring2intHex(strYearHEnd.c_str());
        dsUserCard.structUserCard.LimitDate2[1]=TypeConvert::stdstring2intHex(strYearLEnd.c_str());
        dsUserCard.structUserCard.LimitDate2[2]=TypeConvert::stdstring2intHex(strMonEnd.c_str());
        dsUserCard.structUserCard.LimitDate2[3]=TypeConvert::stdstring2intHex(strDayEnd.c_str());
        dsUserCard.structUserCard.LimitDate3[0]=TypeConvert::stdstring2intHex(strYearHStart.c_str());
        dsUserCard.structUserCard.LimitDate3[1]=TypeConvert::stdstring2intHex(strYearLStart.c_str());
        dsUserCard.structUserCard.LimitDate3[2]=TypeConvert::stdstring2intHex(strMonStart.c_str());
        dsUserCard.structUserCard.LimitDate3[3]=TypeConvert::stdstring2intHex(strDayStart.c_str());
        dsUserCard.structUserCard.LimitDate3[0]=TypeConvert::stdstring2intHex(strYearHEnd.c_str());
        dsUserCard.structUserCard.LimitDate3[1]=TypeConvert::stdstring2intHex(strYearLEnd.c_str());
        dsUserCard.structUserCard.LimitDate3[2]=TypeConvert::stdstring2intHex(strMonEnd.c_str());
        dsUserCard.structUserCard.LimitDate3[3]=TypeConvert::stdstring2intHex(strDayEnd.c_str());

        dsUserCard.structUserCard.LimitFlag1=0x02;
        dsUserCard.structUserCard.LimitFlag2=0x02;
        dsUserCard.structUserCard.LimitFlag3=0x02;
    }
    //乘梯信息
    int nCountLift=0;
    //设备号/可用电梯号,strLiftNum1从1开始
    QString strLiftNum1 = ui->newcardLineEditLiftNum1->text();
    if(!strLiftNum1.isEmpty())
    {
        nCountLift++;
        dsUserCard.structUserCard.LiftNum1=strLiftNum1.toInt();
        //受控楼层
        if(ui->newcardLineEditFloorNum1->text().isEmpty())
        {
            QMessageBox::warning(this,"警告","请选择楼层！",QMessageBox::Yes);
            return;
        }
        // A
        for(int i=0;i<6;i++)
        {
            dsUserCard.structUserCard.DoorA1[i]=0x00;
        }
        std::map<int,QString>::iterator it;
        for(it=newcardMapFloorsA.begin();it!=newcardMapFloorsA.end();++it)
        {
            int nFloor = int(it->first);
            dsUserCard.structUserCard.DoorA1[(nFloor)/8] |= 1<<((nFloor)%8);
        }
        if(newcardMapFloorsA.size()==1)
        {
            dsUserCard.structUserCard.SelOneMul1=1;
        }
        if(newcardMapFloorsA.size()>1)
        {
            dsUserCard.structUserCard.SelOneMul1=2;
        }
        // B 保留
        for(int i=0;i<6;i++)
        {
            dsUserCard.structUserCard.DoorB1[i]=0x00;
        }
        //房间编号1
        QString strQRoomNum1 = ui->newcardLineEditRoomNum1->text();
        if(strQRoomNum1.isEmpty())
        {
            QMessageBox::warning(this,"警告","请输入房间编号！",QMessageBox::Yes);
            return;
        }
        std::string strRoomNum1=strQRoomNum1.toStdString();
        dsUserCard.structUserCard.RoomNum1[0]=TypeConvert::stdstring2intDec(strRoomNum1.substr(0,2));
        dsUserCard.structUserCard.RoomNum1[1]=TypeConvert::stdstring2intDec(strRoomNum1.substr(2,2));
    }
    //设备号/可用电梯号,strLiftNum2从1开始
    QString strLiftNum2 = ui->newcardLineEditLiftNum2->text();
    if(!strLiftNum2.isEmpty())
    {
        nCountLift++;
        dsUserCard.structUserCard.LiftNum2=strLiftNum2.toInt();
        //受控楼层
        if(ui->newcardLineEditFloorNum2->text().isEmpty())
        {
            QMessageBox::warning(this,"警告","请选择楼层！",QMessageBox::Yes);
            return;
        }
        // A
        for(int i=0;i<6;i++)
        {
            dsUserCard.structUserCard.DoorA2[i]=0x00;
        }
        std::map<int,QString>::iterator it;
        for(it=newcardMapFloorsA.begin();it!=newcardMapFloorsA.end();++it)
        {
            int nFloor = int(it->first);
            dsUserCard.structUserCard.DoorA2[(nFloor)/8] |= 1<<((nFloor)%8);
        }
        if(newcardMapFloorsA.size()==1)
        {
            dsUserCard.structUserCard.SelOneMul2=1;
        }
        if(newcardMapFloorsA.size()>1)
        {
            dsUserCard.structUserCard.SelOneMul2=2;
        }
        // B 保留
        for(int i=0;i<6;i++)
        {
            dsUserCard.structUserCard.DoorB2[i]=0x00;
        }
        //房间编号1
        QString strQRoomNum2 = ui->newcardLineEditRoomNum2->text();
        if(strQRoomNum2.isEmpty())
        {
            QMessageBox::warning(this,"警告","请输入房间编号！",QMessageBox::Yes);
            return;
        }
        std::string strRoomNum2=strQRoomNum2.toStdString();
        dsUserCard.structUserCard.RoomNum2[0]=TypeConvert::stdstring2intDec(strRoomNum2.substr(0,2));
        dsUserCard.structUserCard.RoomNum2[1]=TypeConvert::stdstring2intDec(strRoomNum2.substr(2,2));
    }
    //设备号/可用电梯号,strLiftNum3从1开始
    QString strLiftNum3 = ui->newcardLineEditLiftNum3->text();
    if(!strLiftNum3.isEmpty())
    {
        nCountLift++;
        dsUserCard.structUserCard.LiftNum3=strLiftNum3.toInt();
        //受控楼层
        if(ui->newcardLineEditFloorNum3->text().isEmpty())
        {
            QMessageBox::warning(this,"警告","请选择楼层！",QMessageBox::Yes);
            return;
        }
        // A
        for(int i=0;i<6;i++)
        {
            dsUserCard.structUserCard.DoorA3[i]=0x00;
        }
        std::map<int,QString>::iterator it;
        for(it=newcardMapFloorsA.begin();it!=newcardMapFloorsA.end();++it)
        {
            int nFloor = int(it->first);
            dsUserCard.structUserCard.DoorA3[(nFloor)/8] |= 1<<((nFloor)%8);
        }
        if(newcardMapFloorsA.size()==1)
        {
            dsUserCard.structUserCard.SelOneMul3=1;
        }
        if(newcardMapFloorsA.size()>1)
        {
            dsUserCard.structUserCard.SelOneMul3=2;
        }
        // B 保留
        for(int i=0;i<6;i++)
        {
            dsUserCard.structUserCard.DoorB3[i]=0x00;
        }
        //房间编号1
        QString strQRoomNum3 = ui->newcardLineEditRoomNum3->text();
        if(strQRoomNum3.isEmpty())
        {
            QMessageBox::warning(this,"警告","请输入房间编号！",QMessageBox::Yes);
            return;
        }
        std::string strRoomNum3=strQRoomNum3.toStdString();
        dsUserCard.structUserCard.RoomNum3[0]=TypeConvert::stdstring2intDec(strRoomNum3.substr(0,2));
        dsUserCard.structUserCard.RoomNum3[1]=TypeConvert::stdstring2intDec(strRoomNum3.substr(2,2));
    }
    if(nCountLift==0)
    {
        QMessageBox::warning(this,"警告","请选择电梯！",QMessageBox::Yes);
        return;
    }

    uchar *strUserCard = dsUserCard.DS2chars();
    uchar strUserCardH[49]={0};
    uchar strUserCardL[49]={0};
    memmove(strUserCardH,strUserCard,49*sizeof(uchar));
    memmove(strUserCardL,strUserCard+49,49*sizeof(uchar));
    MainWindow *pMainWnd = MainWindow::pMainWnd;//主窗口指针
    if(pMainWnd->ch375rw.bIsOpened)
    {
        if(pMainWnd->ch375rw.Write(0x00,49,strUserCardH))
        {
            Sleep(TIME_DELAY);
            if(pMainWnd->ch375rw.Write(49,49,strUserCardL))
            {
                Sleep(TIME_DELAY);
                pMainWnd->ch375rw.Beep(1);
                pMainWnd->txtbrwInfos->setText("====数据写入成功====");
            }
        }
    }
#endif

    std::vector<QString> arrValues;

    //卡号
    arrValues.push_back(ui->newcardLineEditCardID->text());
    //业主姓名
    arrValues.push_back(ui->newcardLineEditUsrName->text());
    //业主门牌
    arrValues.push_back(ui->newcardLineEditDoorNum->text());
    //联系电话
    arrValues.push_back(ui->newcardLineEditPhone->text());  
    //限制日期
    if(ui->newcardRadioButtonLimitDate->isChecked())
    {
        QDate dateStart=ui->newcardDateEditStart->date();
        QDate dateEnd = ui->newcardDateEditEnd->date();
        if(!dateStart.isValid() || !dateEnd.isValid())
        {
            QMessageBox::warning(this,"警告","日期格式错误或为空！",QMessageBox::Yes);
        }
        QString strQDateStart=dateStart.toString("yyyy.MM.dd");
        QString strQDateEnd=dateEnd.toString("yyyy.MM.dd");

        arrValues.push_back(strQDateStart+"-"+strQDateEnd);
    }
    //乘梯信息
    //设备号/可用电梯号,strLiftNum1从1开始
    QString strLiftNum1 = ui->newcardLineEditLiftNum1->text();
    if(!strLiftNum1.isEmpty())
    {
        arrValues.push_back(strLiftNum1);

        //受控楼层
        if(ui->newcardLineEditFloorNum1->text().isEmpty())
        {
            QMessageBox::warning(this,"警告","请选择楼层！",QMessageBox::Yes);
            return;
        }
        arrValues.push_back(ui->newcardLineEditFloorNum1->text());

        //房间编号1
        QString strQRoomNum1 = ui->newcardLineEditRoomNum1->text();
        if(strQRoomNum1.isEmpty())
        {
            QMessageBox::warning(this,"警告","请输入房间编号！",QMessageBox::Yes);
            return;
        }
        arrValues.push_back(strQRoomNum1);
        modelDBUsrCard->addData(arrValues);
    }
}

////////////数据变更
void TabWidget_OwnerCard::on_datachangePushBtnLiftNum1_clicked()
{
    SelectLiftDlg dlgSelectLift;
    dlgSelectLift.show();
    if(dlgSelectLift.exec() == QDialog::Accepted)
    {
        datachangeArrValuesLiftInfos.clear();
        std::vector<QString>().swap(datachangeArrValuesLiftInfos);
        datachangeArrValuesLiftInfos = dlgSelectLift.arrValues;
        datachangeLiftNum = QString(datachangeArrValuesLiftInfos[0]).toInt();
        ui->datachangeLineEditLiftNum1->setText(QString::number(datachangeLiftNum));
    }
}

void TabWidget_OwnerCard::on_datachangePushBtnLiftNum2_clicked()
{
    SelectLiftDlg dlgSelectLift;
    dlgSelectLift.show();
    if(dlgSelectLift.exec() == QDialog::Accepted)
    {
        datachangeArrValuesLiftInfos.clear();
        std::vector<QString>().swap(datachangeArrValuesLiftInfos);
        datachangeArrValuesLiftInfos = dlgSelectLift.arrValues;
        datachangeLiftNum = QString(datachangeArrValuesLiftInfos[0]).toInt();
        ui->datachangeLineEditLiftNum2->setText(QString::number(datachangeLiftNum));
    }
}


void TabWidget_OwnerCard::on_datachangePushBtnLiftNum3_clicked()
{
    SelectLiftDlg dlgSelectLift;
    dlgSelectLift.show();
    if(dlgSelectLift.exec() == QDialog::Accepted)
    {
        datachangeArrValuesLiftInfos.clear();
        std::vector<QString>().swap(datachangeArrValuesLiftInfos);
        datachangeArrValuesLiftInfos = dlgSelectLift.arrValues;
        datachangeLiftNum = QString(datachangeArrValuesLiftInfos[0]).toInt();
        ui->datachangeLineEditLiftNum3->setText(QString::number(datachangeLiftNum));
    }
}

void TabWidget_OwnerCard::on_datachangePushBtnFloorNum1_clicked()
{
    if(ui->datachangeLineEditLiftNum1->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请先选择电梯！",QMessageBox::Yes);
        return;
    }
    std::vector<QString> arrValues;
    arrValues.push_back(QString(datachangeArrValuesLiftInfos[1]));
    arrValues.push_back(QString(datachangeArrValuesLiftInfos[2]));
    arrValues.push_back(QString(datachangeArrValuesLiftInfos[3]));
    arrValues.push_back(QString(datachangeArrValuesLiftInfos[4]));

    SelectFloorDlg dlgSelectFloor;
    dlgSelectFloor.ModifyFloorInfo(arrValues);
    dlgSelectFloor.show();
    if(dlgSelectFloor.exec() == QDialog::Accepted)
    {
        datachangeMapFloorsA=dlgSelectFloor.mapFloorsA;
        QString strFloors;
        std::map<int,QString>::iterator it;
        for(it=datachangeMapFloorsA.begin();it!=datachangeMapFloorsA.end();++it)
        {
            strFloors += it->second + ",";
        }
        strFloors.remove(strFloors.length()-1,1);
        ui->datachangeLineEditFloorNum1->setText("A门："+strFloors+";");
    }
}

void TabWidget_OwnerCard::on_datachangePushBtnFloorNum2_clicked()
{
    if(ui->datachangeLineEditLiftNum2->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请先选择电梯！",QMessageBox::Yes);
        return;
    }
    std::vector<QString> arrValues;
    arrValues.push_back(QString(datachangeArrValuesLiftInfos[1]));
    arrValues.push_back(QString(datachangeArrValuesLiftInfos[2]));
    arrValues.push_back(QString(datachangeArrValuesLiftInfos[3]));
    arrValues.push_back(QString(datachangeArrValuesLiftInfos[4]));

    SelectFloorDlg dlgSelectFloor;
    dlgSelectFloor.ModifyFloorInfo(arrValues);
    dlgSelectFloor.show();
    if(dlgSelectFloor.exec() == QDialog::Accepted)
    {
        datachangeMapFloorsA=dlgSelectFloor.mapFloorsA;
        QString strFloors;
        std::map<int,QString>::iterator it;
        for(it=datachangeMapFloorsA.begin();it!=datachangeMapFloorsA.end();++it)
        {
            strFloors += it->second + ",";
        }
        strFloors.remove(strFloors.length()-1,1);
        ui->datachangeLineEditFloorNum2->setText("A门："+strFloors+";");
    }
}

void TabWidget_OwnerCard::on_datachangePushBtnFloorNum3_clicked()
{
    if(ui->datachangeLineEditLiftNum3->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请先选择电梯！",QMessageBox::Yes);
        return;
    }
    std::vector<QString> arrValues;
    arrValues.push_back(QString(datachangeArrValuesLiftInfos[1]));
    arrValues.push_back(QString(datachangeArrValuesLiftInfos[2]));
    arrValues.push_back(QString(datachangeArrValuesLiftInfos[3]));
    arrValues.push_back(QString(datachangeArrValuesLiftInfos[4]));

    SelectFloorDlg dlgSelectFloor;
    dlgSelectFloor.ModifyFloorInfo(arrValues);
    dlgSelectFloor.show();
    if(dlgSelectFloor.exec() == QDialog::Accepted)
    {
        datachangeMapFloorsA=dlgSelectFloor.mapFloorsA;
        QString strFloors;
        std::map<int,QString>::iterator it;
        for(it=datachangeMapFloorsA.begin();it!=datachangeMapFloorsA.end();++it)
        {
            strFloors += it->second + ",";
        }
        strFloors.remove(strFloors.length()-1,1);
        ui->datachangeLineEditFloorNum3->setText("A门："+strFloors+";");
    }
}

void TabWidget_OwnerCard::on_datachangePushBtnFindUsr_clicked()
{

}

void TabWidget_OwnerCard::on_datachangePushBtnWrite_clicked()
{

}

void TabWidget_OwnerCard::on_reissuePushBtnLiftNum1_clicked()
{
    SelectLiftDlg dlgSelectLift;
    dlgSelectLift.show();
    if(dlgSelectLift.exec() == QDialog::Accepted)
    {
        reissueArrValuesLiftInfos.clear();
        std::vector<QString>().swap(reissueArrValuesLiftInfos);
        reissueArrValuesLiftInfos = dlgSelectLift.arrValues;
        reissueLiftNum = QString(reissueArrValuesLiftInfos[0]).toInt();
        ui->reissueLineEditLiftNum1->setText(QString::number(reissueLiftNum));
    }
}

void TabWidget_OwnerCard::on_reissuePushBtnLiftNum2_clicked()
{
    SelectLiftDlg dlgSelectLift;
    dlgSelectLift.show();
    if(dlgSelectLift.exec() == QDialog::Accepted)
    {
        reissueArrValuesLiftInfos.clear();
        std::vector<QString>().swap(reissueArrValuesLiftInfos);
        reissueArrValuesLiftInfos = dlgSelectLift.arrValues;
        reissueLiftNum = QString(reissueArrValuesLiftInfos[0]).toInt();
        ui->reissueLineEditLiftNum2->setText(QString::number(reissueLiftNum));
    }
}

void TabWidget_OwnerCard::on_reissuePushBtnLiftNum3_clicked()
{
    SelectLiftDlg dlgSelectLift;
    dlgSelectLift.show();
    if(dlgSelectLift.exec() == QDialog::Accepted)
    {
        reissueArrValuesLiftInfos.clear();
        std::vector<QString>().swap(reissueArrValuesLiftInfos);
        reissueArrValuesLiftInfos = dlgSelectLift.arrValues;
        reissueLiftNum = QString(reissueArrValuesLiftInfos[0]).toInt();
        ui->reissueLineEditLiftNum3->setText(QString::number(reissueLiftNum));
    }
}

void TabWidget_OwnerCard::on_reissuePushBtnFloorNum1_clicked()
{
    if(ui->reissueLineEditLiftNum1->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请先选择电梯！",QMessageBox::Yes);
        return;
    }
    std::vector<QString> arrValues;
    arrValues.push_back(QString(reissueArrValuesLiftInfos[1]));
    arrValues.push_back(QString(reissueArrValuesLiftInfos[2]));
    arrValues.push_back(QString(reissueArrValuesLiftInfos[3]));
    arrValues.push_back(QString(reissueArrValuesLiftInfos[4]));

    SelectFloorDlg dlgSelectFloor;
    dlgSelectFloor.ModifyFloorInfo(arrValues);
    dlgSelectFloor.show();
    if(dlgSelectFloor.exec() == QDialog::Accepted)
    {
        reissueMapFloorsA=dlgSelectFloor.mapFloorsA;
        QString strFloors;
        std::map<int,QString>::iterator it;
        for(it=reissueMapFloorsA.begin();it!=reissueMapFloorsA.end();++it)
        {
            strFloors += it->second + ",";
        }
        strFloors.remove(strFloors.length()-1,1);
        ui->reissueLineEditFloorNum1->setText("A门："+strFloors+";");
    }
}

void TabWidget_OwnerCard::on_reissuePushBtnFloorNum2_clicked()
{
    if(ui->reissueLineEditLiftNum2->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请先选择电梯！",QMessageBox::Yes);
        return;
    }
    std::vector<QString> arrValues;
    arrValues.push_back(QString(reissueArrValuesLiftInfos[1]));
    arrValues.push_back(QString(reissueArrValuesLiftInfos[2]));
    arrValues.push_back(QString(reissueArrValuesLiftInfos[3]));
    arrValues.push_back(QString(reissueArrValuesLiftInfos[4]));

    SelectFloorDlg dlgSelectFloor;
    dlgSelectFloor.ModifyFloorInfo(arrValues);
    dlgSelectFloor.show();
    if(dlgSelectFloor.exec() == QDialog::Accepted)
    {
        reissueMapFloorsA=dlgSelectFloor.mapFloorsA;
        QString strFloors;
        std::map<int,QString>::iterator it;
        for(it=reissueMapFloorsA.begin();it!=reissueMapFloorsA.end();++it)
        {
            strFloors += it->second + ",";
        }
        strFloors.remove(strFloors.length()-1,1);
        ui->reissueLineEditFloorNum2->setText("A门："+strFloors+";");
    }
}

void TabWidget_OwnerCard::on_reissuePushBtnFloorNum3_clicked()
{
    if(ui->reissueLineEditLiftNum3->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请先选择电梯！",QMessageBox::Yes);
        return;
    }
    std::vector<QString> arrValues;
    arrValues.push_back(QString(reissueArrValuesLiftInfos[1]));
    arrValues.push_back(QString(reissueArrValuesLiftInfos[2]));
    arrValues.push_back(QString(reissueArrValuesLiftInfos[3]));
    arrValues.push_back(QString(reissueArrValuesLiftInfos[4]));

    SelectFloorDlg dlgSelectFloor;
    dlgSelectFloor.ModifyFloorInfo(arrValues);
    dlgSelectFloor.show();
    if(dlgSelectFloor.exec() == QDialog::Accepted)
    {
        reissueMapFloorsA=dlgSelectFloor.mapFloorsA;
        QString strFloors;
        std::map<int,QString>::iterator it;
        for(it=reissueMapFloorsA.begin();it!=reissueMapFloorsA.end();++it)
        {
            strFloors += it->second + ",";
        }
        strFloors.remove(strFloors.length()-1,1);
        ui->reissueLineEditFloorNum3->setText("A门："+strFloors+";");
    }
}

void TabWidget_OwnerCard::on_reissuePushBtnFind_clicked()
{

}

void TabWidget_OwnerCard::on_reissuePushBtnWrite_clicked()
{

}
