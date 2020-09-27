#include "UBX.h"
#include <vector>

UBX::UBX(message::Message mesType)
{
    _mesType = mesType;
    _package = package;


    _ck_a = 0;
    _ck_b = 0;

    _mesLength = (mesType.lengthSig << 8) | (mesType.lengthLeast);
    _mes = new uint8_t[_mesLength + 8]; // dynamically allocate space for the message

    serialize();
}

UBX::~UBX()
{
    delete _mes;
}

uint8_t* UBX::getMessage()
{
    return _mes;
}

void UBX::updateCheckSum()
{
    for (int i = 0; i < _mesLength + 6; i++)
    {
        _ck_a += _mes[i];
        _ck_b += _ck_a;
    }
}

void UBX::serialize()
{
    _mes[0] = _mesType.sync_char1;
    _mes[1] = _mesType.sync_char2;

    _mes[2] = _mesType.classNum;
    _mes[3] = _mesType.ID;
    _mes[4] = _mesType.lengthLeast;
    _mes[5] = _mesType.lengthSig;
    
    for (int i = 0; i < _mesLength; i++)
    {
        _mes[6+i] = _package.at(i);
    }

    updateCheckSum();
    _mes[6+_mesLength] = _ck_a;
    _mes[7+_mesLength] = _ck_b;
}

void UBX::setPackage(std::vector<uint8_t> package)
{
    _package = package;
}
