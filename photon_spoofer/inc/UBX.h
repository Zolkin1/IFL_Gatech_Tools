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
    UBX(message::Message mesType);
    ~UBX();
    
    void setPackage(std::vector<uint8_t> package);
    uint8_t* getMessage();

private:
    // Dynamically allocated array of chars that represent the message
    uint8_t* _mes;
    
    uint16_t _mesLength;

    message::Message _mesType;
    std::vector<uint8_t> _package;

    // Checksum bytes
    uint8_t _ck_a;
    uint8_t _ck_b;

    void updateCheckSum();
    void serialize();
};
