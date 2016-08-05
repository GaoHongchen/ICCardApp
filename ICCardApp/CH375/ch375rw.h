#ifndef CH375RW_H
#define CH375RW_H

#include "CH375DLL.H"
#include <iostream>
#include <string>
#include "../Tools/typeconvert.h"

class CH375RW
{
public:
    CH375RW(ULONG nIndex=0);
    ~CH375RW();

public:
    bool        bIsOpened;
    std::string strCardID;

public:
    bool        OpenDevice();
    void        GetUsbID(std::string&, std::string&);
    void        SetDeviceNotify();
    UCHAR *     Read(UCHAR chDataAddr, UCHAR nDataLen);
    bool        Write(UCHAR chDataAddr, UCHAR nDataLen, UCHAR *chData);
    bool        Beep (UCHAR nTimes);

private:
    void        GetDeviceName(ULONG nIndexDevice);
    bool        PutDataRead (UCHAR chDataAddr, UCHAR nDataLen);
    bool        PutDataWrite(UCHAR chDataAddr, UCHAR nDataLen, UCHAR *chData);
    bool        PutDataBeep (UCHAR nTimes);
    UCHAR *     GetDataRead(ULONG nDataLen);
    bool        GetDataWrite();
    bool        GetDataBeep();

private:
    ULONG       nIndexDevice;       //设备索引
    HANDLE      hDevice;            //设备句柄
    UCHAR       chDeviceName[128];  //设备名字
};

void CALLBACK  CH375NOTIFYROUTINE(ULONG iEventStatus);

//自定义消息
#define UM_EVENT_DEVICE_ARRIVAL WM_USER+0x100
#define UM_EVENT_DEVICE_REMOVE  WM_USER+0x101

#define TIME_DELAY 500

#endif // CH375RW_H
