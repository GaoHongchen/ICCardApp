#include "ds_enablecard.h"

DS_EnableCard::DS_EnableCard()
{

}

void DS_EnableCard::chars2DS(uchar data[])
{
    //项目ID
    structEnableCard.ProjectID=data[0];
    //卡类型
    structEnableCard.CardType=data[1];
    //电梯编号
    structEnableCard.LiftNum=data[2];
    //启禁用类型：房号还是卡号
    structEnableCard.EnableType=data[3];
    //受限卡类型
    structEnableCard.LimitCardType=data[4];
    //启禁用数量
    structEnableCard.EnableNum=data[5];
    //启禁1
    structEnableCard.IsEnable1=data[6];
    for(int i=0;i<4;i++)
    {
        structEnableCard.Num1[i]=data[i+7];
    }
    //启禁2
    structEnableCard.IsEnable2=data[11];
    for(int i=0;i<4;i++)
    {
        structEnableCard.Num2[i]=data[i+12];
    }
    //启禁3
    structEnableCard.IsEnable3=data[16];
    for(int i=0;i<4;i++)
    {
        structEnableCard.Num3[i]=data[i+17];
    }
    //启禁4
    structEnableCard.IsEnable4=data[21];
    for(int i=0;i<4;i++)
    {
        structEnableCard.Num4[i]=data[i+22];
    }
}

uchar *DS_EnableCard::DS2chars()
{
    uchar *data = new uchar[26]{0};
    data[0]=structEnableCard.ProjectID;
    data[1]=structEnableCard.CardType;
    data[2]=structEnableCard.LiftNum;
    data[3]=structEnableCard.EnableType;
    data[4]=structEnableCard.LimitCardType;
    data[5]=structEnableCard.EnableNum;
    data[6]=structEnableCard.IsEnable1;
    for(int i=0;i<4;i++)
    {
        data[i+7]=structEnableCard.Num1[i];
    }
    data[11]=structEnableCard.IsEnable2;
    for(int i=0;i<4;i++)
    {
        data[i+12]=structEnableCard.Num2[i];
    }
    data[16]=structEnableCard.IsEnable3;
    for(int i=0;i<4;i++)
    {
        data[i+17]=structEnableCard.Num3[i];
    }
    data[21]=structEnableCard.IsEnable4;
    for(int i=0;i<4;i++)
    {
        data[i+22]=structEnableCard.Num4[i];
    }

    return data;
}

DS_EnableCard::~DS_EnableCard()
{
}
