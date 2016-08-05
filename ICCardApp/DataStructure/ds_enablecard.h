#ifndef DS_ENABLECARD_H
#define DS_ENABLECARD_H

#include "Tools/typeconvert.h"

struct DS_EnableCard_Struct
{
    uchar   ProjectID;      //项目ID
    uchar   CardType;       //卡类型
    uchar   LiftNum;        //电梯编号
    uchar   EnableType;     //按卡号还是房号
    uchar   LimitCardType;  //受限卡类型
    uchar   EnableNum;      //数量
    uchar   IsEnable1;
    uchar   Num1[4];
    uchar   IsEnable2;
    uchar   Num2[4];
    uchar   IsEnable3;
    uchar   Num3[4];
    uchar   IsEnable4;
    uchar   Num4[4];
};

class DS_EnableCard
{
public:
    DS_EnableCard();
    ~DS_EnableCard();

public:
    DS_EnableCard_Struct structEnableCard;

    void  chars2DS(uchar data[26]);
    uchar *DS2chars();
};

#endif // DS_ENABLECARD_H
