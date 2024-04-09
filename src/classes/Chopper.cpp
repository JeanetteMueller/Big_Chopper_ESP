
#include "Chopper.h"

Chopper::Chopper(bool debug)
{
    _debug = debug;
    // init
    body = new ChopperBody(debug);
    dome = new ChopperDome(debug);
    lights = new ChopperLights(1, 150, _debug);
}

void Chopper::setup()
{
    drive->setupLeftMotor(PWM_DIR, 14, 12);
    drive->setupRightMotor(PWM_DIR, 13, 15);

    body->setup();
    dome->setup();
    lights->setup();
}

void Chopper::loop()
{
    _currentMillis = millis();

    drive->updateMotorsWith(horizontal, vertical, 5, 150);

    body->loop();
    dome->loop();

    if (_currentMillis - _previousMillis_100 >= 100)
    {
        _previousMillis_100 = _currentMillis;

        lights->loop();
    }
}