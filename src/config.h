#ifndef CONFIG_H
#define CONFIG_H

#include <QtGlobal>
#include <map>
#include <Box2D/Box2D.h>

class Config
{   // units: meters-kilogram-second (MKS)
public:
    const float scale   = 50;  // bigger -> more accurate but slower

    // frame
    const float frame_w = 0.114f * scale;
    const float frame_h = 0.190f * scale;
    std::map<char, int> frame_margin_pix = {{'w', 5}, {'h', 5}};

    // ball
    const uint ballNum  = 200;
    const float ball_r  = 0.0012f * scale;

    // gravity
    const float g_scale = 1;

    // box2d world
    const float timeStep = 1.0f/60;
    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;
};

#endif // CONFIG_H
