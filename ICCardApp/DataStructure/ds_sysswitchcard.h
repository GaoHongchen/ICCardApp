#ifndef DS_SYSSWITCHCARD_H
#define DS_SYSSWITCHCARD_H

#include "Tools/typeconvert.h"

enum SWCardType{SysSwitch,LayerSwitch,PublicFloorsSet};

struct DS_SysSwitchCard_Struct
{
    uchar       ProjectID;      //项目ID
    uchar       CardType;       //卡类型0x08
    SWCardType  SwitchCardType; //开关卡类型
    uchar       SwitchFlag;     //开关标识
    uchar       LiftNum[32];    //电梯编号
    uchar       FloorsA[6];     //受控楼层A/公共楼层
    uchar       FloorsB[6];     //受控楼层B
};

class DS_SysSwitchCard
{
public:
    DS_SysSwitchCard();
    ~DS_SysSwitchCard();

public:
    DS_SysSwitchCard_Struct structSysSwitchCard;

    void  chars2DS(uchar data[48]);
    uchar *DS2chars();
};

#endif // DS_SYSSWITCHCARD_H
