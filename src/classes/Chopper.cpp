
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
    body->setup();
    dome->setup();
    lights->setup();
}

void Chopper::loop()
{
    _currentMillis = millis();

    body->loop();
    dome->loop();

    if (_currentMillis - _previousMillis_100 >= 100)
    {
        _previousMillis_100 = _currentMillis;

        lights->loop();
    }
}
