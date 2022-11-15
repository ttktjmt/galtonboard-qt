#ifndef CONFIG_H
#define CONFIG_H

#include <QtGlobal>
#include <map>

class Config
{   // units: meters-kilogram-second (MKS)
public:
    const float scale   = 10;

    // frame
    const float frame_w = 0.114f * scale;
    const float frame_h = 0.190f * scale;
    std::map<char, int> frame_margin_pix = {{'w', 10}, {'h', 10}};

    // ball
    const uint ballNum  = 100;
    const float ball_r  = 0.0012f * scale;

};

#endif // CONFIG_H
