// #include <Arduino.h>
// #ifdef __AVR__
// #include <avr/power.h>
// #endif

#include <Wire.h>
#include "searchI2cPorts.h"

#define SERIAL_PORT_SPEED 115200 // Define the port output serial communication speed

#include "definitions.h"

#include "debug.h"
#include "input.h"

// #include "test.h"

/*

// -> 06.11.2024 Outdated, should be updated

5     PWM board
4     PWM Board
0
2     LEDs
14    PWM motor 1
12    DIR motor 1
13    PWM motor 2
15    DIR motor 2
3     RX RC Reciever
1

*/

/////////////////////////////////// SETUP ////////////////////////////////////////////////////
void setup()
{
  Serial.begin(SERIAL_PORT_SPEED); // Used only for debugging on arduino serial monitor
  Serial.println(F("Big Droid Chopper! v2.2"));

  pwm_body->begin();
  pwm_body->setOscillatorFrequency(27000000);
  pwm_body->setPWMFreq(60);

  pwm_dome->begin();
  pwm_dome->setOscillatorFrequency(27000000);
  pwm_dome->setPWMFreq(60);

  setupInput();

  chopper->setup();

  // setupTest();
}

// start of loop ///////////////////////////////////////////////////////////////////////

void loopDriving()
{
  if (ibusVar00 != 0 && ibusVar01 != 0)
  {
    chopper->body->horizontal = ibusVar00;
    chopper->body->vertical = ibusVar01;
  }
  else
  {
    chopper->body->horizontal = 1500;
    chopper->body->vertical = 1500;
  }
}

void loopDomeRotationAndPeriscope()
{
  // Dome & Periscope Rotation
  if (ibusVar02 != 0 && ibusVar03 != 0)
  {
    if (ibusVar02 >= 1500 && ibusVar02 <= 2000)
    {
      chopper->body->setDomeRotation(1500);

      int16_t liftPeriscope = map(ibusVar02, 1500, 2000, 0, 255);
      chopper->dome->setPeriscopeLift(liftPeriscope);

      int16_t rotationPeriscope = map(ibusVar03, 1000, 2000, -127, 127);
      chopper->dome->setPeriscopeRotation(rotationPeriscope);
    }
    else
    {
      chopper->dome->setPeriscopeLift(0);
      chopper->dome->setPeriscopeRotation(0);

      chopper->body->setDomeRotation(ibusVar03);
    }
  }
}

void loopDomeArmRight()
{
  if (ibusVar05 >= 1000 && ibusVar05 <= 2000)
  {
    chopper->dome->setRightArmExtend(ibusVar05);
  }
}

void loopDomeArmLeft()
{
  if (ibusVar04 >= 1000 && ibusVar04 <= 2000)
  {
    chopper->dome->setLeftArmExtend(ibusVar04);
  }
}

void loopDomeShake()
{
  if (ibusVar07 == 2000)
  {
    chopper->body->domeShake = true;
  }
  else
  {
    chopper->body->domeShake = false;
  }
}

void loopBodyToolRight()
{

  if (ibusVar09 >= 1500 && ibusVar09 <= 2000)
  {
    chopper->body->bodyArmRight = true;
  }
  else
  {
    chopper->body->bodyArmRight = false;
  }
}

void loopBodyToolLeft()
{
  if (ibusVar06 >= 1500 && ibusVar06 <= 2000)
  {
    chopper->body->bodyArmLeft = true;
  }
  else
  {
    chopper->body->bodyArmLeft = false;
  }
}

void loopBodyUtilityArm()
{
  if (ibusVar08 != 0)
  {
    if (ibusVar08 >= 1500 && ibusVar08 <= 2000)
    {
      chopper->body->utilityArm = true;

      if (ibusVar08 == 2000)
      {
        chopper->body->utilityArmGripper = true;
      }
      else
      {
        chopper->body->utilityArmGripper = false;
      }
    }
    else
    {
      chopper->body->utilityArmGripper = false;

      chopper->body->utilityArm = false;
    }
  }
}

void loopLights()
{
  if (ibusVar02 >= 1650 && ibusVar02 <= 2000)
  {
    chopper->lights->periscopeIsOn = true;
  }
  else
  {
    chopper->lights->periscopeIsOn = false;
  }

  if (chopper->body->bodyArmRight)
  {
    chopper->lights->currentMood = ChopperLights::LightsMood::terminator;
  }
  else
  {
    chopper->lights->currentMood = ChopperLights::LightsMood::basic;
  }
}

bool i2cSetupIsDone = false;

void loop()
{
  // Serial.println(F("Main Loop"));

  if (i2cSetupIsDone)
  {

    loopInput();

    debugInput();

    loopDriving();

    loopDomeRotationAndPeriscope();
    loopDomeArmRight();
    loopDomeArmLeft();
    loopDomeShake();

    loopBodyToolRight();
    loopBodyToolLeft();
    loopBodyUtilityArm();

    loopLights();

    // Do Main Loop
    chopper->loop();

    // testTaskManager.loop();

    // Serial.print("globalBool is: ");
    // // bool globalBoolValue = *globalBool;
    // Serial.println(globalBool == true ? "-----------------true" : "-----------------false");
  }
  else
  {
    if (searchI2CPorts2())
    {
      i2cSetupIsDone = true;
    }
  }
}

// end of loop ///////////////////////////////////////////////////////////////////////////////////////////