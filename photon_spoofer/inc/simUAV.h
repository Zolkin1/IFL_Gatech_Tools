#include <vector>

class simUAV
{
private:
    int _uavAction;
    float _variance;
    int _dir;
    std::vector<double> _pos;
    float _dt;

public:
    simUAV(int uavAction, float variance, int dir, float x, float y, float z, float dt);
    std::vector<double> updatePos();
    void setVar(float var);
    float getdt();
};
