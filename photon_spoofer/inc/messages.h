#ifndef __mes__
#define __mes__
#pragma pack(1) // Makes the struct alligned on 1 byte - packs the struct

namespace message
{
    struct UBX_ACK
    {
        const static uint8_t classNum = 0x05;
        const static uint8_t ID = 0x01;
        const static uint8_t lengthLeast = 0x02;
        const static uint8_t lengthSig = 0x00;    // 2 bytes
        const static int size = 2;
    };

    struct UBX_NACK
    {
        const static uint8_t classNum = 0x05;
        const static uint8_t ID = 0x00;
        const static uint8_t lengthLeast = 0x02;
        const static uint8_t lengthSig = 0x00;    // 2 bytes
    };

    struct UBX_NAV_POSLLH
    {
        const static uint8_t classNum = 0x01;
        const static uint8_t ID = 0x02;
        const static uint8_t lengthLeast = 0x1C;
        const static uint8_t lengthSig = 0x00;    // 28 bytes
        unsigned int tow;
        int long_scaled;
        int lat_scaled;
        int h;
        int alt;
        unsigned int horzAcc;
        unsigned int vertAcc;
        const static int size = 28;
    };

}

#endif
