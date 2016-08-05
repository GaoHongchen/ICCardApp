#include "ds_usercard.h"

DS_UserCard::DS_UserCard()
{
}

DS_UserCard::~DS_UserCard()
{
}

void DS_UserCard::chars2DS(uchar data[])
{
    structUserCard.ProjectID = data[0];
    structUserCard.CardType = data[1];

    structUserCard.LiftNum1 = data[2];
    structUserCard.LiftNum2 = data[3];
    structUserCard.LiftNum3 = data[4];

    structUserCard.RoomNum1[0]=data[5];
    structUserCard.RoomNum1[1]=data[6];
    structUserCard.RoomNum2[0]=data[7];
    structUserCard.RoomNum2[1]=data[8];
    structUserCard.RoomNum3[0]=data[9];
    structUserCard.RoomNum3[1]=data[10];

    //////// 1
    structUserCard.LimitTimes1[0]=data[11];
    structUserCard.LimitTimes1[1]=data[12];

    for(int i=0;i<8;i++)
    {
        structUserCard.LimitDate1[i]=data[13+i];
    }

    for(int i=0;i<3;i++)
    {
        structUserCard.LimitTimeSpace1[i]=data[21+i];
    }

    for(int i=0;i<6;i++)
    {
        structUserCard.DoorA1[i]=data[24+i];
    }

    for(int i=0;i<6;i++)
    {
        structUserCard.DoorB1[i]=data[30+i];
    }

    structUserCard.SelOneMul1=data[36];

    structUserCard.LimitFlag1=data[37];

    structUserCard.LimitTimeSpace1[0]=data[38];
    structUserCard.LimitTimeSpace1[1]=data[39];

    //////// 2
    structUserCard.LimitTimes2[0]=data[40];
    structUserCard.LimitTimes2[1]=data[41];

    for(int i=0;i<8;i++)
    {
        structUserCard.LimitDate2[i]=data[42+i];
    }

    for(int i=0;i<3;i++)
    {
        structUserCard.LimitTimeSpace2[i]=data[50+i];
    }

    for(int i=0;i<6;i++)
    {
        structUserCard.DoorA2[i]=data[53+i];
    }

    for(int i=0;i<6;i++)
    {
        structUserCard.DoorB2[i]=data[59+i];
    }

    structUserCard.SelOneMul2=data[65];

    structUserCard.LimitFlag2=data[66];

    structUserCard.LimitTimeSpace2[0]=data[67];
    structUserCard.LimitTimeSpace2[1]=data[68];

    //////// 3
    structUserCard.LimitTimes3[0]=data[69];
    structUserCard.LimitTimes3[1]=data[70];

    for(int i=0;i<8;i++)
    {
        structUserCard.LimitDate3[i]=data[71+i];
    }

    for(int i=0;i<3;i++)
    {
        structUserCard.LimitTimeSpace3[i]=data[79+i];
    }

    for(int i=0;i<6;i++)
    {
        structUserCard.DoorA3[i]=data[82+i];
    }

    for(int i=0;i<6;i++)
    {
        structUserCard.DoorB3[i]=data[88+i];
    }

    structUserCard.SelOneMul3=data[94];

    structUserCard.LimitFlag3=data[95];

    structUserCard.LimitTimeSpace3[0]=data[96];
    structUserCard.LimitTimeSpace3[1]=data[97];
}

uchar *DS_UserCard::DS2chars()
{
    uchar *data = new uchar[98]{0};

    data[0]= structUserCard.ProjectID;
    data[1]= structUserCard.CardType;

    data[2]= structUserCard.LiftNum1;
    data[3]= structUserCard.LiftNum2;
    data[4]= structUserCard.LiftNum3;

    data[5]= structUserCard.RoomNum1[0];
    data[6]= structUserCard.RoomNum1[1];
    data[7]= structUserCard.RoomNum2[0];
    data[8]= structUserCard.RoomNum2[1];
    data[9]= structUserCard.RoomNum3[0];
    data[10]= structUserCard.RoomNum3[1];

    //////// 1
    data[11]= structUserCard.LimitTimes1[0];
    data[12]= structUserCard.LimitTimes1[1];

    for(int i=0;i<8;i++)
    {
        data[13+i]=structUserCard.LimitDate1[i];
    }

    for(int i=0;i<3;i++)
    {
       data[21+i]=structUserCard.LimitTimeSpace1[i];
    }

    for(int i=0;i<6;i++)
    {
       data[24+i]=structUserCard.DoorA1[i];
    }

    for(int i=0;i<6;i++)
    {
       data[30+i]=structUserCard.DoorB1[i];
    }

    data[36]= structUserCard.SelOneMul1;

    data[37]= structUserCard.LimitFlag1;

    data[38]= structUserCard.LimitTimeSpace1[0];
    data[39]= structUserCard.LimitTimeSpace1[1];

    //////// 2
    data[40] =structUserCard.LimitTimes2[0];
    data[41] =structUserCard.LimitTimes2[1];

    for(int i=0;i<8;i++)
    {
       data[42+i]=structUserCard.LimitDate2[i];
    }

    for(int i=0;i<3;i++)
    {
       data[50+i]=structUserCard.LimitTimeSpace2[i];
    }

    for(int i=0;i<6;i++)
    {
       data[53+i]=structUserCard.DoorA2[i];
    }

    for(int i=0;i<6;i++)
    {
       data[59+i]=structUserCard.DoorB2[i];
    }

    data[65]= structUserCard.SelOneMul2;

    data[66]= structUserCard.LimitFlag2;

    data[67]= structUserCard.LimitTimeSpace2[0];
    data[68]= structUserCard.LimitTimeSpace2[1];

    //////// 3
    data[69]= structUserCard.LimitTimes3[0];
    data[70]= structUserCard.LimitTimes3[1];

    for(int i=0;i<8;i++)
    {
       data[71+i]=structUserCard.LimitDate3[i];
    }

    for(int i=0;i<3;i++)
    {
       data[79+i]=structUserCard.LimitTimeSpace3[i];
    }

    for(int i=0;i<6;i++)
    {
       data[82+i]=structUserCard.DoorA3[i];
    }

    for(int i=0;i<6;i++)
    {
       data[88+i]=structUserCard.DoorB3[i];
    }

    data[94]= structUserCard.SelOneMul3;

    data[95]= structUserCard.LimitFlag3;

    data[96]= structUserCard.LimitTimeSpace3[0];
    data[97]= structUserCard.LimitTimeSpace3[1];

    return data;
}
