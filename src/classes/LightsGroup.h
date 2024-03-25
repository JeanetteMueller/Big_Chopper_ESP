#ifndef LightsGroup_h
#define LightsGroup_h

#include <Adafruit_NeoPixel.h>

class LightsGroup
{
public:
    LightsGroup(Adafruit_NeoPixel *neoPixelLights, uint16_t startIndex, uint16_t ledCount);

    void setColor(uint32_t color);
    void setColor(uint32_t color, uint16_t index);

private:
    Adafruit_NeoPixel *_neoPixelLights;
    uint16_t _startIndex;
    uint16_t _ledCount;
};

#endif