#ifndef DS_USERCARD_H
#define DS_USERCARD_H

#include "Tools/typeconvert.h"

struct DS_UserCard_Struct
{
    uchar   ProjectID;      //项目ID
    uchar   CardType;       //卡类型
    uchar   LiftNum1;       //电梯编号
    uchar   LiftNum2;
    uchar   LiftNum3;
    uchar   RoomNum1[2];       //房号
    uchar   RoomNum2[2];
    uchar   RoomNum3[2];

    uchar   LimitTimes1[2];   //限次
    uchar   LimitDate1[8];   //限日期
    uchar   LimitTimeSpace1[3];//限时间段
    uchar   DoorA1[6];
    uchar   DoorB1[6];
    uchar   SelOneMul1;
    uchar   LimitFlag1;
    uchar   VipTime1[2];

    uchar   LimitTimes2[2];   //限次
    uchar   LimitDate2[8];   //限日期
    uchar   LimitTimeSpace2[3];//限时间段
    uchar   DoorA2[6];
    uchar   DoorB2[6];
    uchar   SelOneMul2;
    uchar   LimitFlag2;
    uchar   VipTime2[2];

    uchar   LimitTimes3[2];   //限次
    uchar   LimitDate3[8];   //限日期
    uchar   LimitTimeSpace3[3];//限时间段
    uchar   DoorA3[6];
    uchar   DoorB3[6];
    uchar   SelOneMul3;
    uchar   LimitFlag3;
    uchar   VipTime3[2];
};

class DS_UserCard
{
public:
    DS_UserCard();
    ~DS_UserCard();

public:
    DS_UserCard_Struct structUserCard;

    void  chars2DS(uchar data[98]);
    uchar *DS2chars();
};

#endif // DS_USERCARD_H
