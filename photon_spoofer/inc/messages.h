#ifndef __mes__
#define __mes__

namespace message
{
    struct Message
    {
        const static uint8_t sync_char1 = 0xB5;
        const static uint8_t sync_char2 = 0x62;
        uint8_t lengthSig;
        uint8_t lengthLeast;
        uint8_t classNum;
        uint8_t ID;
    };

    struct UBX_ACK : Message
    {
        const static uint8_t classNum = 0x05;
        const static uint8_t ID = 0x01;
        const static uint8_t lengthSig = 0x00;
        const static uint8_t lengthLeast = 0x02;    // 2 bytes
    };

    struct UBX_NACK : Message
    {
        const static uint8_t classNum = 0x05;
        const static uint8_t ID = 0x00;
        const static uint8_t lengthSig = 0x00;
        const static uint8_t lengthLeast = 0x02;    // 2 bytes
    };

    struct UBX_INF_ERROR : Message
    {
        const static uint8_t classNum = 0x04;
        const static uint8_t ID = 0x04;
        
        // Variable length for this message
        uint8_t lengthSig;
        uint8_t lengthLeast;
    };

    struct UBX_NAV_POSLLH : Message
    {
        const static uint8_t classNum = 0x01;
        const static uint8_t ID = 0x02;
        const static uint8_t lengthSig = 0x00;
        const static uint8_t lengthLeast = 0x1C;    // 28 bytes
    };

}

#endif
