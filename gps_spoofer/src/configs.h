struct configs
{
    uint8_t numSatellites = 6;
    unsigned int hAcc = 100;
    unsigned int vAcc = 100;
    unsigned int sAcc = 100;
    unsigned int headAcc = 1200000;
    unsigned int tAcc = 1000;
    unsigned short pDOP = 100;
    unsigned short gDOP = 100;
    unsigned short tDOP = 100;
    unsigned short vDOP = 100;
    unsigned short hDOP = 100;
    unsigned short nDOP = 100;
    unsigned short eDOP = 100;

};

struct config1 : configs
{
    const static uint8_t numSatellites = 6;
    const static unsigned int hAcc = 100;   // 0.1 m
    const static unsigned int vAcc = 100;   // 0.1 m
    const static unsigned int sAcc = 2000;  // 2 m/s
    const static unsigned int headAcc = 1200000;    // 25 deg
    const static unsigned int tAcc = 1000;          // 1 mirco second
    const static unsigned short pDOP = 100; // 1.0 m
    const static unsigned short gDOP = 100;
    const static unsigned short tDOP = 100;
    const static unsigned short vDOP = 100;
    const static unsigned short hDOP = 100;
    const static unsigned short nDOP = 100;
    const static unsigned short eDOP = 100;
};

struct config2 : configs
{
    const static uint8_t numSatellites = 7;
    const static unsigned int hAcc = 200;
    const static unsigned int vAcc = 200;   
    const static unsigned int sAcc = 4000;
    const static unsigned int headAcc = 2500000;
    const static unsigned int tAcc = 2000;
    const static unsigned short pDOP = 200;
    const static unsigned short gDOP = 200;
    const static unsigned short tDOP = 200;
    const static unsigned short vDOP = 200;
    const static unsigned short hDOP = 200;
    const static unsigned short nDOP = 200;
    const static unsigned short eDOP = 200;
};
