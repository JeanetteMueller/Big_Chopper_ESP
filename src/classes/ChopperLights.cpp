#include "ChopperLights.h"

ChopperLights::ChopperLights(byte pin, uint16_t brightness)
{
    _pin = pin;
    _ledsCount = 1 + 1 + 7 + 7 + 7 + 1;
    _brightness = brightness;
}

void ChopperLights::setupLights()
{

    _neoPixelLights = new Adafruit_NeoPixel(_ledsCount, _pin, pixelFormat);
    _neoPixelLights->setBrightness(_brightness);
    _neoPixelLights->begin();

    _bodyBack = new LightsGroup(_neoPixelLights, 0, 1);
    _bodyFront = new LightsGroup(_neoPixelLights, 1, 1);

    _rightEye = new LightsGroup(_neoPixelLights, 2, 7);
    _centerEye = new LightsGroup(_neoPixelLights, 9, 7);
    _leftEye = new LightsGroup(_neoPixelLights, 16, 7);

    _periscope = new LightsGroup(_neoPixelLights, 23, 1);

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

void ChopperLights::updateLight(LightType light, uint32_t color)
{
    switch (light)
    {
    case bodyBack:
        _bodyBack->setColor(color);
        break;
    case bodyFront:
        _bodyFront->setColor(color);
        break;
    case rightEye:
        _rightEye->setColor(color);
        break;
    case rightEyeCenter:
        _rightEye->setColorOnIndex(color, 6);
        break;
    case centerEye:
        _centerEye->setColor(color);
        break;
    case centerEyeCenter:
        _centerEye->setColorOnIndex(color, 6);
        break;
    case leftEye:
        _leftEye->setColor(color);
        break;
    case leftEyeCenter:
        _leftEye->setColorOnIndex(color, 6);
        break;
    case periscope:
        _periscope->setColor(color);
        break;
    }
}

void ChopperLights::resetAllLights()
{
    // LightsGroup* list[6] = {
    //     _bodyBack, _bodyFront,
    //     _rightEye, _centerEye, _leftEye,
    //     _periscope
    // };

    // int len = *(&list + 1) - list;

    // for (uint16_t i = 0; i < len; i++)
    // {
    //     LightsGroup* group = list[i];

    //     group->setColor(offColor);
    // }

    for (uint16_t i = 0; i < _ledsCount; i++)
    {
        _neoPixelLights->setPixelColor(i, offColor);
    }
}

void ChopperLights::loopLights()
{
    _neoPixelLights->show();
}