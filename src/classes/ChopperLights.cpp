#include "ChopperLights.h"

ChopperLights::ChopperLights(byte pin, uint16_t brightness, bool debug)
{
    _debug = debug;
    _pin = pin;
    _ledsCount = 1 + 1 + 7 + 7 + 7 + 7;
    _brightness = brightness;
}

void ChopperLights::setup()
{
    _neoPixelLights = new Adafruit_NeoPixel(_ledsCount, _pin, pixelFormat);
    _neoPixelLights->setBrightness(_brightness);
    _neoPixelLights->begin();

    _bodyBack = new LightsGroup(_neoPixelLights, 0, 1);
    _bodyFront = new LightsGroup(_neoPixelLights, 1, 1);

    _rightEye = new LightsGroup(_neoPixelLights, 2, 7);
    _centerEye = new LightsGroup(_neoPixelLights, 9, 7);
    _leftEye = new LightsGroup(_neoPixelLights, 16, 7);

    _periscope = new LightsGroup(_neoPixelLights, 23, 7);

    offColor = _neoPixelLights->Color(0, 0, 0);

    // grün, rot, blau
    frontBodyLightColor = _neoPixelLights->Color(0, 255, 0);
    backBodyLightColor = _neoPixelLights->Color(255, 0, 0);

    // rot, grün, blau
    colorDefaultBlue = _neoPixelLights->Color(0, 0, 128);

    colorRed = _neoPixelLights->Color(255, 0, 0);
    colorGreen = _neoPixelLights->Color(0, 255, 0);
    colorBlue = _neoPixelLights->Color(0, 0, 255);
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
    case periscopeCenter:
        _periscope->setColorOnIndex(color, 6);
        break;
    case periscopeRainbow:
        uint16_t raised = 20;
        _periscope->setColorOnIndex(rainbowColor(_step + raised * 0), 0);
        _periscope->setColorOnIndex(rainbowColor(_step + raised * 1), 1);
        _periscope->setColorOnIndex(rainbowColor(_step + raised * 2), 2);
        _periscope->setColorOnIndex(rainbowColor(_step + raised * 3), 3);
        _periscope->setColorOnIndex(rainbowColor(_step + raised * 4), 4);
        _periscope->setColorOnIndex(rainbowColor(_step + raised * 5), 5);
        _periscope->setColorOnIndex(offColor, 6);
        break;
    }
    _step += 1;

    if (_step > 255)
    {
        _step = 0;
    }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t ChopperLights::rainbowColor(uint16_t pos)
{
    if (pos > 255)
    {
        pos = pos - 255;
    }

    if (pos < 85)
    {
        return _neoPixelLights->Color(pos * 3, 255 - pos * 3, 0);
    }
    else if (pos < 170)
    {
        pos -= 85;
        return _neoPixelLights->Color(255 - pos * 3, 0, pos * 3);
    }
    else
    {
        pos -= 170;
        return _neoPixelLights->Color(0, pos * 3, 255 - pos * 3);
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

void ChopperLights::prepareLights()
{
    resetAllLights();
    updateLight(ChopperLights::LightType::bodyBack, backBodyLightColor);
    updateLight(ChopperLights::LightType::bodyFront, frontBodyLightColor);

    // Eyes
    if (currentMood == terminator)
    {
        updateLight(ChopperLights::LightType::rightEye, colorRed);
        updateLight(ChopperLights::LightType::centerEye, colorRed);
        updateLight(ChopperLights::LightType::leftEye, colorRed);

        if (periscopeIsOn)
        {
            updateLight(ChopperLights::LightType::periscopeCenter, colorRed);
        }
    }
    else
    {
        updateLight(ChopperLights::LightType::rightEye, colorDefaultBlue);
        updateLight(ChopperLights::LightType::centerEye, colorDefaultBlue);
        updateLight(ChopperLights::LightType::leftEye, colorDefaultBlue);

        if (periscopeIsOn)
        {
            updateLight(ChopperLights::LightType::periscopeRainbow, offColor);
        }
    }
}

void ChopperLights::loop()
{
    prepareLights();
    _neoPixelLights->show();
}