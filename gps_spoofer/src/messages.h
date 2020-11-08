#pragma once
#pragma pack(1)

namespace message
{
    struct UBX_ACK
    {
        const static uint8_t classNum = 0x05;
        const static uint8_t ID = 0x01;
        const static uint8_t lengthLeast = 0x02;
        const static uint8_t lengthSig = 0x00;
        const static int size = 2;
    };

    struct UBX_NAV_DOP
    {
        const static uint8_t classNum = 0x01;
        const static uint8_t ID = 0x04;
        const static uint8_t lengthLeast = 0x12;
        const static uint8_t lengthSig = 0x00;
        const static int size = 18;
        unsigned int tow;
        unsigned short gDOP;
        unsigned short pDOP;
        unsigned short tDOP;
        unsigned short vDOP;
        unsigned short hDOP;
        unsigned short nDOP;
        unsigned short eDOP;
    };

    struct UBX_NAV_SOL
    {
        const static uint8_t classNum = 0x01;
        const static uint8_t ID = 0x06;
        const static uint8_t lengthLeast = 0x34;
        const static uint8_t lengthSig = 0x00;
        const static int size = 52;
        unsigned int tow;
        int fracTow;    // 2's compliment
        short week;     // 2's compliment
        uint8_t gpsFix;
        uint8_t flag;   // bit field - each bit means something
        int ecefX;      // all ecef's are 2's compliemnt
        int ecefY;
        int ecefZ;
        unsigned int pAcc;
        int ecefVX;
        int ecefVY;
        int ecefVZ;
        unsigned int sAcc;
        unsigned short pDOP;
        uint8_t reserved1;
        uint8_t numSV;
        uint8_t reserved2[4];
    };

    struct UBX_NAV_PVT
    {
        const static uint8_t classNum = 0x01;
        const static uint8_t ID = 0x07;
        const static uint8_t lengthLeast = 0x5C;
        const static uint8_t lengthSig = 0x00;
        const static int size = 92;
        unsigned int tow;
        unsigned short year;
        uint8_t month;
        uint8_t day;
        uint8_t hour;
        uint8_t minute;
        uint8_t sec;
        uint8_t valid;  // bitfield
        unsigned int tAcc;
        int nanoSec;
        uint8_t fixType;
        uint8_t flag1;  // bitfield
        uint8_t flag2;  // bitfield
        uint8_t numSV;
        int lon;
        int lat;
        int height;
        int hMSL;
        unsigned int hAcc;
        unsigned int vAcc;
        int velN;
        int velE;
        int velD;
        int gSpeed;
        int headMot;
        unsigned int sAcc;
        unsigned int headAcc;
        unsigned short pDOP;
        uint8_t flag3;
        uint8_t reserved1[5];
        int headVeh;
        short magDec;
        unsigned short magAcc;
    };
}
