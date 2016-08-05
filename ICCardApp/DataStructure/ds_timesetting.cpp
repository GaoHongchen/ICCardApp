#include "ds_timesetting.h"

#include <QDebug>

DS_TimeSetting::DS_TimeSetting()
{

}

void DS_TimeSetting::chars2DS(uchar data[])
{
    //项目ID
    structTimeSet.ProjectID=data[0];
    //卡类型
    structTimeSet.CardType=data[1];
    //分类
    if(0x01 == (data[2] & (1<<0)))
    {
        structTimeSet.TimeSetType = SetType::SetControlerTime;
    }
    if(0x02 == (data[2] & (1<<1)))
    {
        structTimeSet.TimeSetType = SetType::SetKeyResponseTime;
    }
    if(0x04 == (data[2] & (1<<2)))
    {
        structTimeSet.TimeSetType = SetType::SetVisitorResponseTime;
    }
    //控制器时间   
    for(int i=3;i<=8;i++)
    {
        structTimeSet.ControlerTime[i-3]=data[i];
    }
    //单选按钮响应时间
    structTimeSet.SingleSelectTime=data[9];
    //多选按钮响应时间
    structTimeSet.MultiSelectTime=data[10];
    //访客按钮响应时间
    structTimeSet.VisitorTime[0]=data[11];
    structTimeSet.VisitorTime[1]=data[12];
}

uchar *DS_TimeSetting::DS2chars()
{
    uchar *data = new uchar[13]{0};
    //项目ID
    data[0]=structTimeSet.ProjectID;
    //卡类型
    data[1]=structTimeSet.CardType;
    //分类
    switch (structTimeSet.TimeSetType)
    {
    case SetType::SetControlerTime:
        data[2] = (1<<0);
        break;
    case SetType::SetKeyResponseTime:
        data[2] = (1<<1);
        break;
    case SetType::SetVisitorResponseTime:
        data[2] = (1<<2);
        break;
    default:
        break;
    }
    //控制器时间
    for(int i=3;i<=8;i++)
    {
        data[i]=structTimeSet.ControlerTime[i-3];
    }
    //单选按钮响应时间
    data[9]=structTimeSet.SingleSelectTime;
    //多选按钮响应时间
    data[10]=structTimeSet.MultiSelectTime;
    //访客按钮响应时间
    data[11]=structTimeSet.VisitorTime[0];
    data[12]=structTimeSet.VisitorTime[1];

    return data;
}

DS_TimeSetting::~DS_TimeSetting()
{
}

