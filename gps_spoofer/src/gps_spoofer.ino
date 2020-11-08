// This #include statement was automatically added by the Particle IDE.
#include <ParticleGeographicLib.h>
#include "messages.h"

message::UBX_NAV_PVT makePVT(int lat, int lon, int height, int hMSL, int hAcc, int vAcc, int dopI, int itow);
message::UBX_NAV_DOP makeDOP(int dopI, int itow);

struct tstruct
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int sec;
    int microsec;
};

tstruct getTime();

using namespace GeographicLib;
using namespace std;

// TODO: Move this into a github project
// TODO: Make this script use parameters in a .txt file that can be edited with all the parameters in it

int led1 = D0; 
int led2 = D7;

const uint8_t fix_3d = 0x03;
const uint8_t fix_2d = 0x02;
const uint8_t fix_no = 0x00;

int dopI = 111;      // Scaled by a factor of 100 so it can be an int

Geocentric earth(Constants::WGS84_a(), Constants::WGS84_f());
const double lat0 = 33.7490;
const double lon0 = -84.3880;

const double dt = 0.5;    // Seconds
double vel = 0;

uint8_t numSatellites = 6;

double x = 1;
double y = 0.75;
double z = 0.5;

LocalCartesian lc(lat0, lon0, 0, earth);
unsigned long t0 = micros();

void setup() 
{

    Serial.begin(115200);
    Serial1.begin(115200, SERIAL_8N1);
    waitFor(Serial.isConnected, 30000);

    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
}


void loop() 
{     
    // TODO: Programatically generate the messages.
    //  - Can use either vicon accuracy or use the accuracy of the spoofed gps signals
    //  - Does pAcc and sAcc need to match the DOP?
    //  - Figure out last set of constants
    //  - Make it easy to change constants
    //  - Respond to messages
    //  - Attach to code that recieves Vicon data
    
    double lat1, lon1, h;
  
    lc.Reverse(x, y, z, lat1, lon1, h);
    int lat2 = lat1 * 10000000;
    int lon2 = lon1 * 10000000;
    int h2 = h * 1000;
    
    int itow = (int)Time.now();

    message::UBX_NAV_PVT pvt = makePVT(lat2, lon2, h2, 1, 1, 1, dopI, itow);
    message::UBX_NAV_DOP dop = makeDOP(dopI, itow);
    
    sendMessage(message::UBX_NAV_PVT::classNum, message::UBX_NAV_PVT::ID, message::UBX_NAV_PVT::size, &pvt);
    sendMessage(message::UBX_NAV_DOP::classNum, message::UBX_NAV_DOP::ID, message::UBX_NAV_DOP::size, &dop);
    
    heartbeat();
    
    x += vel * dt;
}

void sendMessage(uint8_t classNum, uint8_t id, unsigned int size, void* package)
{
    uint8_t ck_a = 0;
    uint8_t ck_b = 0;    

    uint8_t sync1 = 0xB5;
    uint8_t sync2 = 0x62;
    
    uint8_t length_sig = size & (0xFF00);
    uint8_t length_least = size & (0x00FF);
    
    uint8_t message[8 + size];

    message[0] = sync1;
    message[1] = sync2;
    message[2] = classNum;
    message[3] = id;
    message[4] = length_least;
    message[5] = length_sig; 

    for (unsigned int i = 0; i < size; i++)
    {
        message[6+i] = *((uint8_t*)(package)+i);
    }

    for (unsigned int i = 2; i < 6+size; i++)
    {
        ck_a += message[i];
        ck_b += ck_a;        
    }    

    message[6+(size)] = ck_a;
    message[7+(size)] = ck_b;
    Serial1.write(message,8+size);
    Serial.write(message, 8+(size));
}

void heartbeat()
{
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);

    delay(static_cast<long>(dt*1000));

    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);

    delay(static_cast<long>(dt*1000));
}

tstruct getTime()
{
    tstruct t;

    t.year = Time.year();
    t.month = Time.month();
    t.day = Time.day();
    t.hour = Time.hour();   // TODO: This is giving te wrong hour (was returning 23 when it was actualy 17 in CO on 10/31/2020)
    t.minute = Time.minute();
    t.sec = Time.second(); 
    // No good way to get the exact time in anything less than seconds. Can only get the difference in time at a microsecond level
    unsigned long tn = micros();
    unsigned long tdiff = tn - t0;
    t.microsec = tdiff % 60000000;
    t0 = tn;
    return t; 
}
// TODO: Fix function. Pointer points to the wrong side. May need to move this all back to main.
message::UBX_NAV_PVT makePVT(int lat, int lon, int height, int hMSL, int hAcc, int vAcc, int dopI, int itow)
{
    tstruct t = getTime();

    message::UBX_NAV_PVT pvt;
    pvt.tow = itow;//0x15932D98;
    
    // Time
    pvt.year = t.year; //0x07E4;
    pvt.month = t.month; //0x0A;
    pvt.day = t.day; //0x16;
    pvt.hour = t.hour; //0x04;
    pvt.minute = t.minute; //0x20;
    pvt.sec = t.sec; //0x1D;
    pvt.valid = 0x37;   // I believe this is sayig valid magnetic direction, fully resolved, and valid date but not valid time
    pvt.tAcc = 0x00000011;
    pvt.nanoSec = 0x0005621D; 
   
    // Flags and fix type
    pvt.fixType = fix_3d;
    pvt.flag1 = 0x01;
    pvt.flag2 = 0x0A;
    pvt.numSV = numSatellites;

    // Position and Velocity Info
    pvt.lon = lon;//0xC0C47BBB;
    pvt.lat = lat;//0x179D1389;
    pvt.height = height;//0x002B01C4;
    pvt.hMSL = 0x002B53C2; //hMSL
    pvt.hAcc = 0x00001F2B; //hAcc
    pvt.vAcc = 0x00002259; //vAcc
    pvt.velN = 0x0000002D;
    pvt.velE = 0xFFFFFFB1;
    pvt.velD = 0x0000005B;
    pvt.gSpeed = 0x0000005B;
    pvt.headMot = 0x0204BD70;
    pvt.sAcc = 0x00000911;
    pvt.headAcc = 0x002602B8;
    pvt.pDOP = dopI;
    pvt.flag3 = 0xDE;

    // Dont need to touch these
    pvt.reserved1[0] = 0xF7;
    pvt.reserved1[1] = 0x86;
    pvt.reserved1[2] = 0x4C;
    pvt.reserved1[3] = 0x22;
    pvt.reserved1[4] = 0x00;

    
    pvt.headVeh = 0x181F68FE;
    pvt.magDec = 0x04A3;
    pvt.magAcc = 0x0000;

    return pvt;
}

message::UBX_NAV_DOP makeDOP(int dopI, int itow)
{
    message::UBX_NAV_DOP dop;
    
    dop.tow = itow;
    dop.gDOP = dopI; //218;
    dop.pDOP = dopI; //0x00CA;
    dop.tDOP = dopI; //0x0053;
    dop.vDOP = dopI; //0x00A9;
    dop.hDOP = dopI; //0x006E;
    dop.nDOP = dopI; //0x003D;
    dop.eDOP = dopI; //0x005B;    
    
    return dop;
}
