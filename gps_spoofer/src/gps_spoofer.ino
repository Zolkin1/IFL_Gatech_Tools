#include <ParticleGeographicLib.h>
#include "messages.h"
#include "configs.h"
#include "math.h"
#include "random.h"

// Vicon UDP packet does not have time in it.

message::UBX_NAV_PVT makePVT(int* llh, int gvel, int itow, int theta, int* nedVel, configs config);
message::UBX_NAV_DOP makeDOP(int itow, configs config);
int getheadMot(double x1, double y1, double x2, double y2);
int getgSpeed(double x1, double y1, double x2, double y2, unsigned long dt);
void getVelNED(int* NED, double x1, double y1, double z1, double x2, double y2, double z2, double theta, unsigned long dt);
void addVariance(double* llh, configs config);

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

int led1 = D0; 
int led2 = D7;

const uint8_t fix_3d = 0x03;
const uint8_t fix_2d = 0x02;
const uint8_t fix_no = 0x00;

Geocentric earth(Constants::WGS84_a(), Constants::WGS84_f());
const double lat0 = 33.7490;    // ATL Capital
const double lon0 = -84.3880;   // ATL Capital

const double dt = 0.5;    // Seconds
double vel = 0;

double x = 1;
double y = 0.75;
double z = 0.5;

configs configurations[2];
int config = 1;

double roomAngleOffset = 10;    // radians

LocalCartesian lc(lat0, lon0, 0, earth);
unsigned long t0 = micros();

void setup() 
{
    config1 configuration1;
    config2 configuration2;

    configurations[0] = configuration1;
    configurations[1] = configuration2; 
    
    Serial.begin(115200);
    Serial1.begin(115200, SERIAL_8N1);
    waitFor(Serial.isConnected, 30000);

    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
}


void loop() 
{     
    unsigned long t1 = micros();
    unsigned long dt_loop = t1 - t0;
    t0 = t1;

    // TODO: Check button to change config
    
    // TODO: Get vicon data
    double x_old, y_old, z_old;

    double lat1, lon1, h;
    double* llh;  

    lc.Reverse(x, y, z, lat1, lon1, h);
    llh[0] = lat1;
    llh[1] = lon1;
    llh[2] = h;
    
    addVariance(llh, configurations[config]);
    
    double x_mod, y_mod, z_mod;
    lc.Forward(llh[0], llh[1], llh[2], x_mod, y_mod, z_mod); // Get the variance adjusted x,y,z
    
    int* llhint;
    llhint[0] = (int)(llh[0] * 10000000);
    llhint[1] = (int)(llh[1] * 10000000);
    llhint[2] = (int)(llh[2] * 1000);
    
    int itow = (int)Time.now();
    
    int theta = getheadMot(x_old, y_old, x_mod, y_mod);
    int gvel = getgSpeed(x_old, y_old, x_mod, y_mod, dt_loop);
    int* nedVel;
    getVelNED(nedVel, x_old, y_old, z_old, x_mod, y_mod, z_mod, roomAngleOffset, dt_loop);

    message::UBX_NAV_PVT pvt = makePVT(llhint, gvel, itow, theta, nedVel, configurations[config]);
    message::UBX_NAV_DOP dop = makeDOP(itow, configurations[config]);
    
    sendMessage(message::UBX_NAV_PVT::classNum, message::UBX_NAV_PVT::ID, message::UBX_NAV_PVT::size, &pvt);
    sendMessage(message::UBX_NAV_DOP::classNum, message::UBX_NAV_DOP::ID, message::UBX_NAV_DOP::size, &dop);
    
    heartbeat();
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

void addVariance(double* llh, configs config)
{
    std::default_random_engine generator;
    std::normal_distribution<double> distr(0, config.hDOP);
    double num = distr(generator);
    llh[0] = llh[0] + num;
    num = distr(generator);
    llh[1] = llh[1] + num;    

    std::normal_distribution<double> distr2(0, config.vDOP);
    num = distr2(generator);
    llh[2] = llh[2] + num;
}

int getheadMot(double x1, double y1, double x2, double y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    double theta = atan2(dy, dx);
    theta = theta * 100000; // Change the order of magnitude for int conversion
    return (int)theta;
}

int getgSpeed(double x1, double y1, double x2, double y2, unsigned long dt)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    double dd = sqrt((dx*dx) + (dy*dy));
    double gvel = 1000*(dd/dt);
    return (int)gvel;
}

void getVelNED(int* NED, double x1, double y1, double z1, double x2, double y2, double z2, double theta, unsigned long dt)
{
    // Get the x, y, z, vels then apply a roation in the x-y plane by theta to rotate x and y onto North and East
    double dx = x2 - x1;
    double dy = y2 - y1;
    double dz = z2 - z1;
    
    double vx = dx/dt;
    double vy = dy/dt;
    double vz = dz/dt;

    NED[0] = 1000*(vx*cos(theta) - vy*sin(theta));
    NED[1] = 1000*(vx*sin(theta) + vy*cos(theta));
    NED[3] = 1000*vz;
}

message::UBX_NAV_PVT makePVT(int* llh, int gvel, int itow, int theta, int* nedVel, configs config)
{
    tstruct t = getTime();

    message::UBX_NAV_PVT pvt;
    pvt.tow = itow;
    
    // Time
    pvt.year = t.year;
    pvt.month = t.month;
    pvt.day = t.day;
    pvt.hour = t.hour;
    pvt.minute = t.minute;
    pvt.sec = t.sec;
    pvt.valid = 0x37;
    pvt.tAcc = config.tAcc;
    pvt.nanoSec = 0x0005621D; 
   
    // Flags and fix type
    pvt.fixType = fix_3d;
    pvt.flag1 = 0x01;
    pvt.flag2 = 0x0A;
    pvt.numSV = config.numSatellites;

    // Position and Velocity Info
    pvt.lon = llh[1];
    pvt.lat = llh[0];
    pvt.height = llh[2];
    pvt.hMSL = llh[2] + 320040; // Add the height that ATL is above the sea in mm
    pvt.hAcc = config.hAcc;
    pvt.vAcc = config.vAcc;
    pvt.velN = nedVel[0];
    pvt.velE = nedVel[1];
    pvt.velD = nedVel[2];
    pvt.gSpeed = gvel;
    pvt.headMot = theta;
    pvt.sAcc = config.sAcc;
    pvt.headAcc = config.hAcc;
    pvt.pDOP = config.pDOP;
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

message::UBX_NAV_DOP makeDOP(int itow, configs config)
{
    message::UBX_NAV_DOP dop;
    
    dop.tow = itow;
    dop.gDOP = config.gDOP;
    dop.pDOP = config.pDOP;
    dop.tDOP = config.tDOP;
    dop.vDOP = config.vDOP;
    dop.hDOP = config.hDOP;
    dop.nDOP = config.nDOP; 
    dop.eDOP = config.eDOP;
    
    return dop;
}
