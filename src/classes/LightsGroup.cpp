#include "LightsGroup.h"

LightsGroup::LightsGroup(Adafruit_NeoPixel *neoPixelLights, uint16_t startIndex, uint16_t ledCount)
{
    _neoPixelLights = neoPixelLights;
    _startIndex = startIndex;
    _ledCount = ledCount;
}

void LightsGroup::setColor(uint32_t color)
{
    for (uint16_t i = _startIndex; i < (_startIndex + _ledCount); i++)
    {
        _neoPixelLights->setPixelColor(i, color);
    }
}

void LightsGroup::setColorOnIndex(uint32_t color, uint16_t index)
{
    _neoPixelLights->setPixelColor(_startIndex + index, color);
}