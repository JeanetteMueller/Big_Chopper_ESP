#ifndef Chopper_h
#define Chopper_h

#include <Adafruit_PWMServoDriver.h>

#include "ChopperLights.h"
#include "ChopperBody.h"
#include "ChopperDome.h"

class Chopper
{
public:
    Chopper(bool debug);

    ChopperBody *body;
    ChopperDome *dome;

    ChopperLights *lights;

    void setup();
    void loop();

private:
    bool _debug = false;


    // TIME
    unsigned long _currentMillis; // time current
    unsigned long _previousMillis_100 = 0;
};

#endif