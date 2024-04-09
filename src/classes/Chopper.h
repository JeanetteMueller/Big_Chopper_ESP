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

    void setDriveHorizontal(int16_t horizontal);
    void setDriveVertical(int16_t vertical);

private:
    bool _debug = false;

    JxTankDriver *drive = new JxTankDriver(1000, 2000, 1500);
    int16_t _horizontal = 0;
    int16_t _vertical = 0;
    int16_t _driveValueHorizontal = 1500;
    int16_t _driveValueVertical = 1500;

    // TIME
    unsigned long _currentMillis; // time current
    unsigned long _previousMillis_100 = 0;
};

#endif