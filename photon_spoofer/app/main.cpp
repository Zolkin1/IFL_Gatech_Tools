#include "simUAV.h"
#include "UBX.h"
#include "messages.h"

#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <iostream>
#include <chrono>
#include <thread>

#include <GeographicLib/LocalCartesian.hpp>
#include <GeographicLib/Geocentric.hpp>

using namespace GeographicLib;

void generateACK(UBX ubxMes);

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
    int runType;
    std::cout << "Please indicate if this is a send message or recieve message test. 1 for send message, 2 for recieve message" << std::endl;
    std::cin >> runType;

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
    std::cout << "Generating simulated positions... x, y, z then lat, lon, h:" << std::endl;

    simUAV uav(uavAction, variance, 0, x, y, z, 0.01);
    Geocentric earth(Constants::WGS84_a(), Constants::WGS84_f());

    const double atl_lat = 33.749;
    const double atl_lon = 84.388;
    const double atl_height = 326; // about 326 meters above sea level
    LocalCartesian lc(atl_lat, atl_lon, 0, earth);
    
    double lat, lon, h;
    std::cout << std::left;
    
    UBX ubxMes;

   // std::cout << std::hex << static_cast<int>(message::UBX_NAV_POSLLH::lengthLeast) << std::endl; 

    for (int i = 0; i < 10; i++)
    {
        std::cout << std::setprecision(12);
        std::vector<double> pos = uav.updatePos();
        
       lc.Reverse(pos.at(0), pos.at(1), pos.at(2), lat, lon, h);
       std::cout << pos.at(0) << ", " << pos.at(1) << ", "  << std::setw(30) << pos.at(2) << lat << ", " << lon << ", " << h;
        std::cout << std::endl;
        
        std::vector<double> lla = {lat, lon, h};
        
    }

// TODO: Implement the conversion to UBX and NMEA (UBX first, see pdf in slack)
    int const secondsPerWeek = 604800;
    int const secondsPerYear = 3.154e7;
    time_t timer;
    struct tm gpsStart = {0};
    gpsStart.tm_year = 80;  // Set to January 1980
    if (runType == 1)   // Send messages
    {
        while (true)
        {
            // Generate the fake (x, y, z) data
            std::vector<double> pos = uav.updatePos();

            // Convert the data into LLH
            lc.Reverse(pos.at(0), pos.at(1), pos.at(2), lat, lon, h);

            // Serialize the data
            // Transfer the data to bytes at the proper scale
            int lat_scaled = lat * 1e7;
            int lon_scaled = lon * 1e7;
            int h_scaled = h * 1000;    // mm        

            // Generate the time of week in GPS format
            time(&timer);
            double totalSeconds = difftime(timer, mktime(&gpsStart));   // Get the number of seconds relative to Jan 1 1980
            unsigned int weeks = static_cast<unsigned int>(totalSeconds/secondsPerWeek);
            unsigned int towSeconds = static_cast<unsigned int>(totalSeconds - (weeks * secondsPerWeek))*1000;   // ms

            // Get altitude above sea level
            int alt = static_cast<int>(h * 1000) + (atl_height * 1000);    // mm

            // Horizontal and vertical accuracy - would use vicon, for now hard coding
            unsigned int horzAcc = 10;   // mm
            unsigned int vertAcc = 10;   // mm

            // Package the data 
            // Supposedly all the messages can be easily packed
            int pack_size = 28;
            message::UBX_NAV_POSLLH posllh;
            posllh.tow = __builtin_bswap32(towSeconds);
            posllh.long_scaled = __builtin_bswap32(lon_scaled);
            posllh.lat_scaled = __builtin_bswap32(lat_scaled);
            posllh.h = __builtin_bswap32(h_scaled);
            posllh.alt = __builtin_bswap32(alt);
            posllh.horzAcc = __builtin_bswap32(10);
            posllh.vertAcc = __builtin_bswap32(10);

            ubxMes.sendMessage(static_cast<uint8_t>(message::UBX_NAV_POSLLH::classNum), static_cast<uint8_t>(message::UBX_NAV_POSLLH::ID), message::UBX_NAV_POSLLH::size, &posllh);

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    else    // Recieve message prompt
    {
        uint8_t sync1 = 0xB5;
        uint8_t sync2 = 0x62;
        
        int parse_step = 0;

        std::cout << "Enter a message in hex." << std::endl;
        while (true)
        {
            uint16_t pre1, pre2;
            std::cin >> std::hex >> pre1 >> pre2;

            if (pre1 == sync1 && pre2 == sync2)
            {
                std::cout << "First and second preamble recieved" << std::endl;
                
                uint16_t classNum;
                uint16_t id;
                std::cin >> classNum >> id;
                switch (classNum)
                {
                    case (0x01):    // A NAV Message - it is polling, so send the response with data
                        std::cout << "Class: NAV" << std::endl;
                        switch(id)
                        {
                            case(0x02):
                                // generatePOSLLH();
                                break;
                            case(0x05):
                                // generateATT();
                                break;
                            default:
                                std::cout << "Not a supported message" << std::endl;
                        }
                        break;
                    case (0x06):
                        std::cout << "Class: CFG" << std::endl;
                        switch(id)
                        {
                            case(0x01): // change message rate
                                generateACK(ubxMes);
                                break;
                            case(0x08): // get/set NAV message rate
                                generateACK(ubxMes);
                                break;
                            case(0x00): // get/set port configuration
                                generateACK(ubxMes);
                                break;
                        }
                        break;
                    default:
                        std::cout << "Not a supported class" << std::endl;
                        break;
                }


            } 
        }
    }
}

void generateACK(UBX ubxMes)
{
    message::UBX_ACK ack;
    ubxMes.sendMessage(static_cast<uint8_t>(message::UBX_ACK::classNum),static_cast<uint8_t>(message::UBX_ACK::ID), message::UBX_ACK::size, &ack);
}

// TODO: For the photon port:
// After I know which class the message is then call a "parseClassX(message)" function
// Maybe remove the UBX class and make those just global functions
// Keep the message structs - those work well
// Make sure I ca adjust the rates and abud rates etc... from the cfg messages
//
