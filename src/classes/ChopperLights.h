
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
    periscope
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

  ChopperLights(byte pin, uint16_t mainBrightness);
  void setupLights();
  void loopLights();

  void resetAllLights();

  void updateLight(LightType light, uint32_t color);

private:
  LightsGroup *_bodyBack;
  LightsGroup *_bodyFront;

  LightsGroup *_rightEye;
  LightsGroup *_centerEye;
  LightsGroup *_leftEye;

  LightsGroup *_periscope;

  byte _pin;
  uint16_t _ledsCount;
  Adafruit_NeoPixel *_neoPixelLights;
  neoPixelType pixelFormat = NEO_GRB + NEO_KHZ800;
};

#endif