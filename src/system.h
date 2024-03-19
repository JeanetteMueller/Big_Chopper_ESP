#include <Arduino.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#include <Wire.h>
#include "searchI2cPorts.h"

#define SERIAL_PORT_SPEED 115200 // Define the port output serial communication speed

#include <IBusBM.h>
#include <CytronMotorDriver.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_NeoPixel.h>
#include "SoftwareSerial.h"
#include <DFPlayerMini_Fast.h>
#include <TaskManager.h>

#include "definitions.h"

#include "functions.h"
#include "debug.h"
#include "input.h"

#include "domeRotation.h"
#include "domeShake.h"
#include "domePeriscope.h"
#include "drive.h"
#include "bodyTools.h"
#include "domeTools.h"
#include "lights.h"
// #include "audio.h"

/*

5     PWM board
4     PWM Board
0     PWM motor 3
2     DIR motor 3
14    PWM motor 1
12    DIR motor 1
13    PWM motor 2
15    DIR motor 2
3     RX RC Reciever
1     LEDs

*/

/////////////////////////////////// SETUP ////////////////////////////////////////////////////
void setup()
{
  Serial.begin(SERIAL_PORT_SPEED); // Used only for debugging on arduino serial monitor
  Serial.println(F("Big Droid Chopper! v2.0"));

  pwm_body.begin();
  pwm_body.setOscillatorFrequency(27000000);
  pwm_body.setPWMFreq(SERVO_FREQ);

  pwm_head.begin();
  pwm_head.setOscillatorFrequency(27000000);
  pwm_head.setPWMFreq(SERVO_FREQ);

  setupInput();

  setupDrive();
  setupDomeRotation();
  setupDomeShake();
  setupBodyTools();
  setupLights();
  setupDomeTools();
  setupDomePeriscope();
  // setupAudio();
}

// start of loop ///////////////////////////////////////////////////////////////////////

void loop()
{
  // searchI2CPorts2();
  // return;

  currentMillis = millis();
  if (currentMillis < previousMillis_005)
  {
    previousMillis_005 = 0;
  }
  if (currentMillis < previousMillis_020)
  {
    previousMillis_020 = 0;
  }
  if (currentMillis < previousMillis_100)
  {
    previousMillis_100 = 0;
  }
  if (currentMillis < previousMillis_200)
  {
    previousMillis_200 = 0;
  }

  initLoopDrive();

  loopInput();

  // debug();

  loopDrive();
  loopDomeRotation();

  if (currentMillis - previousMillis_005 >= 5)
  {
    previousMillis_005 = currentMillis;

    updateDriveSpeed();
  }

  if (currentMillis - previousMillis_020 >= 20)
  {
    previousMillis_020 = currentMillis;

    bodyLeftArmTaskManager.loop();
    bodyRightArmTaskManager.loop();
    bodyUtilityArmTaskManager.loop();
    bodyUtilityArmGripperTaskManager.loop();
    domeRightArmTaskManager.loop();
    domeLeftArmTaskManager.loop();
    loopDomeArms();
    domeShakeTaskManager.loop();
  }

  if (currentMillis - previousMillis_100 >= 100)
  {
    previousMillis_100 = currentMillis;

    loopLights();

    loopDomePeriscope();

    // loopAudio();
    // Serial.print( stack_unused() ); Serial.print(F(" -> ")); Serial.println( stack_free() );
  }
}

// end of loop ///////////////////////////////////////////////////////////////////////////////////////////