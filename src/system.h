#include <Arduino.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#include <Wire.h>
#include "searchI2cPorts.h"

#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#define SERIAL_PORT_SPEED 115200 // Define the port output serial communication speed

#include <IBusBM.h>
#include <Adafruit_PWMServoDriver.h>

#include "SoftwareSerial.h"
#include <DFPlayerMini_Fast.h>
#include <TaskManager.h>
#include <JxTankDriver.h>
#include <JxDomeRotation.h>

#include "classes/ChopperLights.h"
#include "classes/WebServer.h"

#include "definitions.h"

#include "Wifi.h"

#include "functions.h"
#include "debug.h"
#include "input.h"

#include "domeRotation.h"
#include "domeShake.h"
#include "domePeriscope.h"
#include "bodyTools.h"
#include "domeTools.h"

// #include "test.h"

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

  setupWifi();
  webServer->start();

  drive->setupLeftMotor(PWM_DIR, 14, 12);
  drive->setupRightMotor(PWM_DIR, 13, 15);

  domeRotation->setupMotor(PWM_DIR, 0, 2);

  setupDomeShake();
  setupBodyTools();
  if (enableLight)
  {
    lights->setupLights();
  }
  setupDomeTools();

  // setupAudio();

  // setupTest();
}

// start of loop ///////////////////////////////////////////////////////////////////////

void prepareLights()
{
  lights->resetAllLights();
  lights->updateLight(ChopperLights::LightType::bodyBack, lights->backBodyLightColor);
  lights->updateLight(ChopperLights::LightType::bodyFront, lights->frontBodyLightColor);

  // Eyes
  if (ibusVar09 == 2000)
  {
    lights->updateLight(ChopperLights::LightType::leftEyeCenter, lights->colorRed);
  }
  else
  {
    lights->updateLight(ChopperLights::LightType::rightEye, lights->colorDefaultBlue);
    lights->updateLight(ChopperLights::LightType::centerEye, lights->colorDefaultBlue);
    lights->updateLight(ChopperLights::LightType::leftEye, lights->colorDefaultBlue);
  }

  // Periscope
  if (ibusVar02 >= 1650 && ibusVar02 <= 2000)
  {
    lights->updateLight(ChopperLights::LightType::periscope, lights->periscopeColor);
  }
  else
  {
    lights->updateLight(ChopperLights::LightType::periscope, lights->offColor);
  }
}

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

  loopWifi();

  loopInput();

  // debug();

  if (currentMillis - previousMillis_005 >= 5)
  {
    previousMillis_005 = currentMillis;

    drive->updateMotorsWith(driveValueHorizontal, driveValueVertical, 5, 150);

    loopDomeRotation();
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

    if (enableLight)
    {
      prepareLights();
      lights->loopLights();
    }
    loopDomePeriscope();

    // loopAudio();
    // Serial.print( stack_unused() ); Serial.print(F(" -> ")); Serial.println( stack_free() );

    // testTaskManager.loop();

    // Serial.print("globalBool is: ");
    // // bool globalBoolValue = *globalBool;
    // Serial.println(globalBool == true ? "-----------------true" : "-----------------false");
  }
}

// end of loop ///////////////////////////////////////////////////////////////////////////////////////////