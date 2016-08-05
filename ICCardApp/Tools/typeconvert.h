#ifndef TYPECONVERT_H
#define TYPECONVERT_H

#include "stdlib.h"
#include "stdio.h"
#include "string"
#include "vector"
#include "math.h"

typedef unsigned char uchar;

class TypeConvert
{
public:
    TypeConvert();
    ~TypeConvert();

public:
    static std::string intHex2stdstring(int nHex);
    static std::string intDec2stdstring(int nDecimal);
    static std::string intNormal2stdstring(int nNormal);
    static std::string float2stdstring(float fData);

    static int stdstring2intDec(std::string strDecimal);
    static int stdstring2intHex(std::string strDecimal);
};

#endif // TYPECONVERT_H
