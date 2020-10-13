#include "UBX.h"

#include <vector>
#include <iostream>

UBX::UBX() 
{
    _ck_a = 0;
    _ck_b = 0;
    _sync1 = 0xB5;
    _sync2 = 0x62;
}

UBX::~UBX() {}

void UBX::sendMessage(uint8_t classNum, uint8_t id, unsigned int size, void* package)
{
    _classNum = classNum;
    _ID = id;
    
    _mesLength = size;
    _lengthSig = (size) & (0xFF00);
    _lengthLeast = (size) & (0x00FF);
    std::cout << std::hex; 
    std::cout << unsigned(_sync1) << " ";
    _ck_a += _sync1;
    _ck_b += _ck_a;
    std::cout << unsigned(_sync2) << " ";
    _ck_a += _sync2;
    _ck_b += _ck_a;
    std::cout << unsigned(_classNum) << " ";
    _ck_a += _classNum;
    _ck_b += _ck_a;
    std::cout << unsigned(_ID) << " ";
    _ck_a += _ID;
    _ck_b += _ck_a;
    std::cout << unsigned(_lengthLeast) << " ";
    _ck_a += _lengthLeast;
    _ck_b += _ck_a;
    std::cout << unsigned(_lengthSig) << " ";
    _ck_a += _lengthSig;
    _ck_b += _ck_a;
    for (int i = 0; i < size/4; i++)
    {
        // Need to convert to unsigned ints to print with cout - this won't work with messages that have only 1 or 2 bytes, but in the future I won't need to print to the screen. So this shouldn't be an issue
        std::cout << *((unsigned*)(package)+i) << " ";
        _ck_a += *((unsigned*)(package)+i);    
        _ck_b += _ck_a;
    }
    std::cout << unsigned(_ck_a) << " ";
    std::cout << unsigned(_ck_b) << " ";
    std::cout << std::endl;
    _ck_a = 0;
    _ck_b = 0;
}
