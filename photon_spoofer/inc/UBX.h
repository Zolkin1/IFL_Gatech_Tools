#include <cstdint>
#include <vector>
#include "messages.h"

/*
 * This class generates and holds a UBX message
 * The most important message to use is UBX-NAV-POSLLH (pg 331 of the user manual)
 * Supported Messages:
 * ---- NAV ----
 * UBX-NAV-POSLLH
 * UBX-NAV-PVT (?)
 * UBX-NAV-ECEF (?)
 * ---- Info ----
 * UBX-INF-ERROR
 * ---- ACK ----
 *  UBX-ACK
 *  UBX-NACK
 *
 *  Can make a message namespace and put the structs for the messages into the namespace. Then I can template on the messages 
 */
class UBX
{
public:
    UBX();
    ~UBX();
    
    void sendMessage(uint8_t classNum, uint8_t id, unsigned int size, void* package);

private:
    // Dynamically allocated array of chars that represent the message
    uint8_t* _mes;
    
    uint8_t _sync1;
    uint8_t _sync2;
    uint8_t _classNum;
    uint8_t _ID;
    uint8_t _lengthLeast;
    uint8_t _lengthSig;
    uint16_t _mesLength;

    std::vector<unsigned int> _package;
    // Checksum bytes
    uint8_t _ck_a;
    uint8_t _ck_b;
};
