#ifndef DS_TIMESETTING_H
#define DS_TIMESETTING_H

#include "Tools/typeconvert.h"
#include "QDateTime"

enum SetType{SetControlerTime,SetKeyResponseTime,SetVisitorResponseTime};

//typedef char CHAR_ARRAY[13];

struct DS_TimeSetting_Struct
{
    uchar       ProjectID;
    uchar       CardType;
    SetType     TimeSetType;
    uchar       ControlerTime[6];
    uchar       SingleSelectTime;
    uchar       MultiSelectTime;
    uchar       VisitorTime[2];
};

class DS_TimeSetting
{
public:
    DS_TimeSetting();
    ~DS_TimeSetting();

public:
    DS_TimeSetting_Struct structTimeSet;

    void  chars2DS(uchar data[13]);
    uchar *DS2chars();

};

#endif // DS_TIMESETTING_H
