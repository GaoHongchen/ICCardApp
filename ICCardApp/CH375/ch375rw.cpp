#include "ch375rw.h"
#include <QDebug>
CH375RW::CH375RW(ULONG nIndex):
    nIndexDevice(nIndex),
    bIsOpened(false)
{
}

void CH375RW::SetDeviceNotify()
{
    CH375SetDeviceNotify(nIndexDevice,NULL,CH375NOTIFYROUTINE);
}

bool CH375RW::OpenDevice()
{
    hDevice=CH375OpenDevice(nIndexDevice);
    if(hDevice!=INVALID_HANDLE_VALUE)
    {
        bIsOpened=true;
        CH375SetBufUpload(nIndexDevice,1);
        CH375SetBufDownload(nIndexDevice,1);
        //CH375SetTimeout(nIndexDevice,500,500);
        GetDeviceName(nIndexDevice);
        return true;
    }
    else
    {
        bIsOpened=false;
        return false;
    }
}

void CH375RW::GetUsbID(std::string &strIDVendor,std::string &strIDProduct)
{
    ULONG nIDDevice = CH375GetUsbID(nIndexDevice);
    char  chIDVendor[4];    //厂商ID
    char  chIDProduct[4];   //设备ID
    sprintf_s(chIDVendor ,"%04X",LOWORD(nIDDevice));
    sprintf_s(chIDProduct,"%04X",HIWORD(nIDDevice));
    strIDVendor = chIDVendor;
    strIDProduct= chIDProduct;
}

void CH375RW::GetDeviceName(ULONG nIndexDevice)
{    
    memcpy(&chDeviceName[0],
            CH375GetDeviceName(nIndexDevice),
            sizeof(chDeviceName));
}

///
/// \brief CH375RW::Beep
/// \param nTimes 响声次数(<7)：=0时蜂鸣器发出长声闷响
///
bool CH375RW::Beep(UCHAR nTimes)
{    
    PutDataBeep(nTimes);
    return GetDataBeep();
//    if(PutDataBeep(nTimes))
//    {
//        return GetDataBeep();
//    }
//    else
//    {
//        return NULL;
//    }
}

UCHAR *CH375RW::Read (UCHAR chDataAddr,UCHAR nDataLen)
{
    if(PutDataRead(chDataAddr,nDataLen))
    {
        return GetDataRead(nDataLen);
    }
    else
    {
        return NULL;
    }
}
bool  CH375RW::Write(UCHAR chDataAddr, UCHAR nDataLen, UCHAR *chData)
{
    if(PutDataWrite(chDataAddr,nDataLen,chData))
    {
        return GetDataWrite();
    }
    else
    {
        return false;
    }
}

bool CH375RW::PutDataRead (UCHAR chDataAddr, UCHAR nDataLen)
{
    ULONG nCmdReadLen=6;
    UCHAR chCmdRead[nCmdReadLen]={0};
    chCmdRead[0]=0xA9;      //字头
    chCmdRead[1]=0x03;      //长度
    chCmdRead[2]=0x01;      //读命令
    chCmdRead[3]=chDataAddr;//数据起始地址
    chCmdRead[4]=nDataLen;  //数据长度
    chCmdRead[5]=0x00;      //异或校验

    if(CH375WriteData((ULONG)hDevice,&chCmdRead[0],&nCmdReadLen))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool CH375RW::PutDataWrite(UCHAR chDataAddr, UCHAR nDataLen, UCHAR *chData)
{
    ULONG nCmdWriteLen=nDataLen+5;
    UCHAR chCmdWrite[nCmdWriteLen]={0};
    chCmdWrite[0]=0xA9;         //字头
    chCmdWrite[1]=nDataLen+3;   //长度
    chCmdWrite[2]=0x02;         //写命令
    chCmdWrite[3]=chDataAddr;   //数据起始地址
    //写入的数据
    for(short i=0;i<nDataLen;i++)
    {
        chCmdWrite[i+4]=chData[i];
    }
    chCmdWrite[nCmdWriteLen-1]=0x00;//异或校验

    if(CH375WriteData((ULONG)hDevice,&chCmdWrite[0],&nCmdWriteLen))
        return true;
    else
        return false;
}

bool CH375RW::PutDataBeep(UCHAR nTimes)
{
    if(int(nTimes)>=7)
    {
        return false;
    }
    ULONG nCmdBeepLen=5;
    UCHAR chCmdBeep[nCmdBeepLen]={0};
    chCmdBeep[0]=0xA9;      //字头
    chCmdBeep[1]=0x02;      //长度
    chCmdBeep[2]=0x03;      //读命令
    chCmdBeep[3]=nTimes;    //响声次数
    chCmdBeep[4]=0x00;      //异或校验
    if(CH375WriteData((ULONG)hDevice,&chCmdBeep[0],&nCmdBeepLen))
        return true;
    else
        return false;
}

UCHAR *CH375RW::GetDataRead(ULONG nDataLen)
{
    ULONG nBufGetLen=nDataLen+8;
    UCHAR chBufGet[nBufGetLen]={0};
    if(CH375ReadData((ULONG)hDevice,&chBufGet[0],&nBufGetLen))
    {
        if(chBufGet[0]==0xA6)//字头
        {
            if(chBufGet[1]==0x00)//返回成功
            {
//                CHAR chBufGet0X[mCH375_PACKET_LENGTH*8*2+1]={0};
//                ULONG i,j;
//                for(i=0,j=0;i<nBufGetLen;i++)
//                {
//                    sprintf(&chBufGet0X[j],"%02X ",chBufGet[i]);
//                    j += 3;
//                }
//                chBufGet0X[j]='\0';
//                return chBufGet0X;
                strCardID="";
                for(int i=0;i<4;i++)//卡号
                {
                    strCardID+=TypeConvert::intHex2stdstring(int(chBufGet[i+2]));
                }
                UCHAR *chDataBuf=new UCHAR[nDataLen]{0};//返回的nDataLen个数据
                for(int i=0;i<nDataLen;i++)
                {
                    chDataBuf[i]=chBufGet[i+7];
                }
                return chDataBuf;
            }
            else if(chBufGet[1]==0x01)//返回错误
            {
                return NULL;
            }
        }
    }
    else
    {
        return NULL;
    }
}
bool  CH375RW::GetDataWrite()
{
    ULONG nBufGetLen=4;
    UCHAR chBufGet[nBufGetLen]={0};
    if(CH375ReadData((ULONG)hDevice,&chBufGet[0],&nBufGetLen))
    {
        if(chBufGet[0]==0xA6)//字头
        {
            if(chBufGet[1]==0x00)//返回成功
            {
                return true;
            }
            else if(chBufGet[1]==0x01)//返回失败
            {
                return false;
            }
        }
    }
}
bool CH375RW::GetDataBeep()
{
    ULONG nBufGetLen=4;
    UCHAR chBufGet[nBufGetLen]={0};
    if(CH375ReadData((ULONG)hDevice,&chBufGet[0],&nBufGetLen))
    {
        if(chBufGet[0]==0xA6)//字头
        {
            if(chBufGet[1]==0x00)//返回成功
            {
                return true;
            }
            else//返回失败
            {
                return false;
            }
        }
    }
}

CH375RW::~CH375RW()
{
}

/* 设备事件通知回调程序,在此程序里不宜作过多的操作,主要是因为中断服务程序优先级高,
   不宜进行USB传输，通常只是发个消息或者置个全局变量通知主程序处理。*/
void CALLBACK  CH375NOTIFYROUTINE(ULONG iEventStatus)
{
    switch (iEventStatus)
    {
    case CH375_DEVICE_ARRIVAL://检测到设备插入事件
        ::PostMessageA(::GetActiveWindow(),UM_EVENT_DEVICE_ARRIVAL,0,0);
        break;
    case CH375_DEVICE_REMOVE://检测到设备拔出事件
        ::PostMessageA(::GetActiveWindow(),UM_EVENT_DEVICE_REMOVE,0,0);
        break;
    default:
        break;
    }
}


//    UCHAR chCmdRead[6]=//A903010C0F00
//    {0xA9,0x03,0x01,0x0C,0x0F,0x00};

//    UCHAR chBufferGet[mCH375_PACKET_LENGTH];

//    ULONG nLength=mCH375_PACKET_LENGTH;

//    CH375WriteRead(nIndexDevice,&chCmdRead[0],&chBufferGet[0],&nLength);

//    CHAR chBuffer0X[mCH375_PACKET_LENGTH*8*2+1];
//    ULONG i,j;
//    for(i=0,j=0;i<40;i++)
//    {
//        sprintf(&chBuffer0X[j],"%02X ",chBufferGet[i]);
//        j += 3;
//    }
//    chBuffer0X[j] = '\0';
//    return (char*)chBuffer0X;



//    // 打开设备
//    HANDLE hPutData =
//            ::CreateFileA
//            (
//                (char *)&chDeviceName[0],
//                GENERIC_READ | GENERIC_WRITE,
//                FILE_SHARE_READ | FILE_SHARE_WRITE,
//                NULL,
//                OPEN_EXISTING,
//                FILE_ATTRIBUTE_NORMAL,
//                NULL
//            );
