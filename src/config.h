#ifndef CONFIG_H
#define CONFIG_H

#include <QtGlobal>
#include <map>
#include <vector>
#include <numeric>
#include <Box2D/Box2D.h>

using std::vector;
using std::accumulate;

class Config
{   // units: meters-kilogram-second (MKS)
public:
    const float scale   = 50;   // bigger -> more accurate but slower

    // frame
    const float frameW  = 0.114f * scale;
    const float frameH  = 0.190f * scale;
    std::map<char, int> frameMarginPix = {{'w', 5}, {'h', 5}};

    // pin
    const vector<uint> pinNumEach = {9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}; // This should increase one by one
    const uint pinNumAll = accumulate(pinNumEach.begin(), pinNumEach.end(), 0);
    const float pinR    = 0.0010f * scale;

    // fence
    const uint fenceNum = 27;
    const float fenceW  = 0.0006f * scale;

    // ball
    const uint ballNum  = 300;
    const float ballR   = 0.0012f * scale;

    // gravity
    const float gScale  = 1;

    // box2d world
    const float timeStep           = 1.0f/60;
    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;
};

#endif // CONFIG_H
