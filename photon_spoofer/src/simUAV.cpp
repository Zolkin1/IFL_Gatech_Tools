#include "simUAV.h"
#include <iostream>
#include <cstdlib>
#include <random>
#include <chrono>

simUAV::simUAV(int uavAction, float variance, int dir, float x, float y, float z, float dt)
{
    _uavAction = uavAction;
    _variance = variance;
    _dir = dir;
    _pos.push_back(x);
    _pos.push_back(y);
    _pos.push_back(z);
}

std::vector<double> simUAV::updatePos()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::vector<double> temp = _pos; 
    std::default_random_engine generator(seed);
    std::normal_distribution<double> distr(0, _variance);

    switch (_uavAction)
    {
        case 1:     // Hover
            temp[0] += distr(generator);
            temp[1] += distr(generator);
            temp[2] += distr(generator);
            break;
        default:
            std::cout << "This UAV action is not currently supported." << std::endl;
    }
    

    return temp;
}

void simUAV::setVar(float var)
{
    _variance = var;
}

float simUAV::getdt()
{
    return _dt;
}
