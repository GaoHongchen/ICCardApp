#include "ds_sysswitchcard.h"

DS_SysSwitchCard::DS_SysSwitchCard()
{
    structSysSwitchCard.ProjectID = 0x00;
    structSysSwitchCard.CardType = 0x00;
    structSysSwitchCard.SwitchCardType = SWCardType::SysSwitch;
    structSysSwitchCard.SwitchFlag = 0x00;
    for(int i=0;i<32;i++)
    {
        structSysSwitchCard.LiftNum[i]=0x00;
    }
    for(int i=0;i<6;i++)
    {
        structSysSwitchCard.FloorsA[i]=0x00;
        structSysSwitchCard.FloorsB[i]=0x00;
    }
}

DS_SysSwitchCard::~DS_SysSwitchCard()
{
}

void DS_SysSwitchCard::chars2DS(uchar data[])
{
    structSysSwitchCard.ProjectID = data[0];
    structSysSwitchCard.CardType = data[1];
    //分类
    if(0x01 == (data[2] & (1<<0)))
    {
        structSysSwitchCard.SwitchCardType = SWCardType::SysSwitch;
    }
    if(0x02 == (data[2] & (1<<1)))
    {
        structSysSwitchCard.SwitchCardType = SWCardType::LayerSwitch;
    }
    if(0x04 == (data[2] & (1<<2)))
    {
        structSysSwitchCard.SwitchCardType = SWCardType::PublicFloorsSet;
    }
    structSysSwitchCard.SwitchFlag = data[3];
    for(int i=0;i<32;i++)
    {
        structSysSwitchCard.LiftNum[i] = data[i+4];
    }
    for(int i=0;i<6;i++)
    {
        structSysSwitchCard.FloorsA[i] = data[i+36];
    }
    for(int i=0;i<6;i++)
    {
        structSysSwitchCard.FloorsB[i] = data[i+42];
    }
}

uchar *DS_SysSwitchCard::DS2chars()
{
    uchar *data = new uchar[48]{0};
    data[0] = structSysSwitchCard.ProjectID;
    data[1] = structSysSwitchCard.CardType;
    //分类
    switch (structSysSwitchCard.SwitchCardType)
    {
    case SWCardType::SysSwitch:
        data[2] = (1<<0);
        break;
    case SWCardType::LayerSwitch:
        data[2] = (1<<1);
        break;
    case SWCardType::PublicFloorsSet:
        data[2] = (1<<2);
        break;
    default:
        break;
    }
    data[3] = structSysSwitchCard.SwitchFlag;
    for(int i=0;i<32;i++)
    {
        data[i+4] = structSysSwitchCard.LiftNum[i];
    }
    for(int i=0;i<6;i++)
    {
        data[i+36] = structSysSwitchCard.FloorsA[i];
    }
    for(int i=0;i<6;i++)
    {
        data[i+42] = structSysSwitchCard.FloorsB[i];
    }
    return data;
}
