#include <iostream>
#include "simUAV.h"
#include <vector>
#include <string>
#include <iomanip>

#include <GeographicLib/LocalCartesian.hpp>
#include <GeographicLib/Geocentric.hpp>

using namespace GeographicLib;

int main()
{
    // Take user input to ask what the quad should do
    // 1) Hover
    // 2) Fly up
    // 3) Fly down
    // 4) Fly parallel to the ground
    //
    // Then take the start location of the quad (x, y, z)
    //
    // Take the input of the LLA of the origin of the VICON system
    int uavAction;
    std::cout << "Please indicate what the simulated UAV should do. \n 1) Hover \n 2) Fly up \n 3) Fly down \n 4) Fly parallel to the ground" << std::endl;
    std::cout << "Currently, only (1) Hover is supported." << std::endl;
    std::cin >> uavAction;

    if (std::cin.fail())    // User did not enter an int
    {
        while (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "You did not enter an integer. Please type in a new integer." << std::endl;
        
            std::cin >> uavAction;
        }
    }

    float variance;

    std::cout << "Please input a position measurement variance." << std::endl;
    std::cin >> variance;
    
    if (std::cin.fail())    // User did not enter an float
    {
        while (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "You did not enter a float. Please type in a new float." << std::endl;
        
            std::cin >> variance;
        }
    }

// ****** Get position input ******* //
float x, y, z;

std::cout << "Please input a starting position (x then y then z)." << std::endl;

    for (int i = 0; i < 3; i++)
    {    
        if (i == 0)
        {
            std::cin >> x;
        }
        else if (i == 1)
        {
            std::cin >> y;
        }
        else
        {
            std::cin >> z;
        }
        if (std::cin.fail())    // User did not enter an float
        {
            while (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "You did not enter a float. Please type in a new float." << std::endl;
                if (i == 0)
                {
                    std::cin >> x;
                }
                else if (i == 1)
                {
                    std::cin >> y;
                }
                else
                {
                    std::cin >> z;
                }
        }
    }
}

    std::cout << "\n";    
    std::cout << "Generating simulated positions... (x, y, z):" << std::endl;

    simUAV uav(uavAction, variance, 0, x, y, z, 0.01);
    Geocentric earth(Constants::WGS84_a(), Constants::WGS84_f());

    const double atl_lat = 33.749;
    const double atl_lon = 84.388;
    LocalCartesian lc(atl_lat, atl_lon, 0, earth);
    
    double lat, lon, h;
    std::cout << std::left;
    //std::cout << std::setw(45) <<"Measured UAV Position" << "| LLA Conversion"  <<std::endl;
    
    for (int i = 0; i < 10; i++)
    {
        std::cout << std::setprecision(12);
        std::vector<double> pos = uav.updatePos();
        
        lc.Reverse(pos.at(0), pos.at(1), pos.at(2), lat, lon, h);

        std::cout << pos.at(0) << ", " << pos.at(1) << ", "  << std::setw(30) << pos.at(2) << lat << ", " << lon << ", " << h;
        std::cout << std::endl;
    }

// TODO: Implement the conversion to UBX and NMEA (UBX first, see pdf in slack)

}
