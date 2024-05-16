
#ifndef ChopperLights_h
#define ChopperLights_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "LightsGroup.h"

class ChopperLights
{
public:
    enum LightType
    {
        bodyBack,
        bodyFront,
        rightEye,
        rightEyeCenter,
        centerEye,
        centerEyeCenter,
        leftEye,
        leftEyeCenter,
        periscope,
        periscopeRainbow
    };

    enum LightsMood
    {
        basic,
        terminator
    };

    uint32_t offColor;

    // grün, rot, blau
    uint32_t frontBodyLightColor;
    uint32_t backBodyLightColor;

    // rot, grün, blau
    uint32_t colorDefaultBlue;
    uint32_t colorRed;
    uint32_t colorGreen;
    uint32_t colorBlue;

    // grün, rot, blau
    uint32_t periscopeColor;

    LightsMood currentMood;
    bool periscopeIsOn;

    ChopperLights(byte pin, uint16_t brightness, bool debug);

    void setup();
    void loop();
    void resetAllLights();
    void updateLight(LightType light, uint32_t color);

private:
    bool _debug;
    LightsGroup *_bodyBack;
    LightsGroup *_bodyFront;

    LightsGroup *_rightEye;
    LightsGroup *_centerEye;
    LightsGroup *_leftEye;

    LightsGroup *_periscope;

    uint16_t _step;

    byte _pin;
    uint16_t _ledsCount;
    uint16_t _brightness;
    Adafruit_NeoPixel *_neoPixelLights;
    neoPixelType pixelFormat = NEO_GRB + NEO_KHZ800;

    void prepareLights();

    uint32_t rainbowColor(uint16_t pos);
};

#endif