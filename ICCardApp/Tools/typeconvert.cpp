#include "typeconvert.h"

TypeConvert::TypeConvert()
{

}

std::string TypeConvert::intHex2stdstring(int nHex)
{
    char charTemp[100];
    sprintf(charTemp,"%02X",nHex);//两位整数
    std::string strTemp = charTemp;
    return strTemp;
}

std::string TypeConvert::intDec2stdstring(int nDecimal)
{
    char charTemp[100];
    sprintf(charTemp,"%02d",nDecimal);//两位整数
    std::string strTemp = charTemp;
    return strTemp;
}

std::string TypeConvert::intNormal2stdstring(int nNormal)
{
    char charTemp[100];
    sprintf(charTemp,"%d",nNormal);
    std::string strTemp = charTemp;
    return strTemp;
}

std::string TypeConvert::float2stdstring(float fData)
{
    char charTemp[100];
    sprintf(charTemp,"%.1f",fData);
    std::string strTemp = charTemp;
    return strTemp;
}

int TypeConvert::stdstring2intDec(std::string strDecimal)
{
    return std::atoi(strDecimal.c_str());
}

int TypeConvert::stdstring2intHex(std::string strDecimal)
{
    int nDecimal = std::atoi(strDecimal.c_str());
    int nHex = nDecimal/10*16+nDecimal%10;
    return nHex;
}

TypeConvert::~TypeConvert()
{

}

