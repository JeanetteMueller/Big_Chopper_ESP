#ifndef Chopper_h
#define Chopper_h

#include "ChopperLights.h"
#include "ChopperBody.h"
#include "ChopperDome.h"
#include "ChopperAudio.h"

#include <Adafruit_PWMServoDriver.h>
#include "DYPlayerEsp32SoftwareSerial.h"

class Chopper
{
public:
    Chopper(Adafruit_PWMServoDriver *pwm_body, Adafruit_PWMServoDriver *pwm_dome, DY::PlayerEsp32SoftwareSerial *player, bool debug);

    ChopperBody *body;
    ChopperDome *dome;
    ChopperLights *lights;
    ChopperAudio *audio;

    void setup();
    void loop();

private:
    bool _debug = false;

    // TIME
    unsigned long _currentMillis; // time current
    unsigned long _previousMillis_1 = 0;
    unsigned long _previousMillis_100 = 0;
    unsigned long _previousMillis_1000 = 0;
};

#endif