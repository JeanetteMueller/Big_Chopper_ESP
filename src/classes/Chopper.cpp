
#include "Chopper.h"

Chopper::Chopper(Adafruit_PWMServoDriver *pwm_body, Adafruit_PWMServoDriver *pwm_dome, DY::PlayerEsp32SoftwareSerial *player, bool debug)
{
  _debug = debug;

  // init
  body = new ChopperBody(pwm_body, debug);
  dome = new ChopperDome(pwm_dome, debug);
  lights = new ChopperLights(5, 150, _debug);
  audio = new ChopperAudio(player, debug);
}

void Chopper::setup()
{
  body->setup();
  dome->setup();
  lights->setup();
  audio->setup();
}

void Chopper::loop()
{
  _currentMillis = millis();

  // if (_currentMillis - _previousMillis_1 >= 1)
  // {
  //   _previousMillis_1 = _currentMillis;

  if (_currentMillis - _previousMillis_1000 >= 1000)
  {
    _previousMillis_1000 = _currentMillis;
    Serial.print("Loop every 1000ms: ");
    Serial.println(_currentMillis);
  }

  body->loop();
  dome->loop();
  audio->loop();

  if (_currentMillis - _previousMillis_100 >= 100)
  {
    _previousMillis_100 = _currentMillis;

    lights->loop();
  }
  // }
}