
#ifndef Lights_h
#define Lights_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

class Lights
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

  

  Lights(byte);
  void setupLights();
  void loopLights();

  void resetAllLights();

  void updateLight(LightType light, uint32_t color);

private:
  byte _pin;
  uint16_t _ledsCount;
  Adafruit_NeoPixel *_neoPixelLights;
  neoPixelType pixelFormat = NEO_GRB + NEO_KHZ800;
};

#endif