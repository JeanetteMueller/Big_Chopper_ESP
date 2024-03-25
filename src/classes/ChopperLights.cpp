#include "ChopperLights.h"

ChopperLights::ChopperLights(byte pin, uint16_t mainBrightness)
{
    _pin = pin;
    _ledsCount = 2 + 7 + 7 + 7 + 1;
    _neoPixelLights = new Adafruit_NeoPixel(_ledsCount, _pin, pixelFormat);
    _neoPixelLights->setBrightness(mainBrightness);

    offColor = _neoPixelLights->Color(0, 0, 0);

    // grün, rot, blau
    frontBodyLightColor = _neoPixelLights->Color(0, 255, 0);
    backBodyLightColor = _neoPixelLights->Color(255, 0, 0);

    // rot, grün, blau
    colorDefaultBlue = _neoPixelLights->Color(0, 0, 128);

    colorRed = _neoPixelLights->Color(255, 0, 0);
    colorGreen = _neoPixelLights->Color(0, 255, 0);
    colorBlue = _neoPixelLights->Color(0, 0, 255);

    // grün, rot, blau
    periscopeColor = _neoPixelLights->Color(0, 255, 0);
}

void ChopperLights::setupLights()
{
    _neoPixelLights->setBrightness(0);
    _neoPixelLights->begin();
}

void ChopperLights::updateLight(LightType light, uint32_t color)
{
    uint16_t startIndex = 0;
    uint16_t length = 1;

    switch (light)
    {
    case bodyBack:
        startIndex = 0;
        length = 1;
        break;
    case bodyFront:
        startIndex = 1;
        length = 1;
        break;
    case rightEye:
        startIndex = 1 + 1;
        length = 7;
        break;
    case rightEyeCenter:
        startIndex = 1 + 1 + 6;
        length = 1;
        break;
    case centerEye:
        startIndex = 1 + 1 + 7;
        length = 7;
        break;
    case centerEyeCenter:
        startIndex = 1 + 1 + 7 + 6;
        length = 1;
        break;
    case leftEye:
        startIndex = 1 + 1 + 7 + 7;
        length = 7;
        break;
    case leftEyeCenter:
        startIndex = 1 + 1 + 7 + 7 + 6;
        length = 1;
        break;
    case periscope:
        startIndex = 1 + 1 + 7 + 7 + 7;
        length = 1;
        break;
    }

    for (uint16_t i = startIndex; i < (startIndex + length); i++)
    {
        _neoPixelLights->setPixelColor(i, color);
    }
}

void ChopperLights::resetAllLights()
{
    for (uint16_t i = 0; i < _ledsCount; i++)
    {
        _neoPixelLights->setPixelColor(i, offColor);
    }
}

void ChopperLights::loopLights()
{
    _neoPixelLights->show();
}