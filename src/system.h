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

#include "classes/Chopper.h"

#include "definitions.h"

#include "Wifi.h"

#include "functions.h"
#include "debug.h"
#include "input.h"

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
    Serial.println(F("Big Droid Chopper! v2.1"));

    setupInput();

    setupWifi();
    webServer->start();

    chopper->setup();

    // setupAudio();

    // setupTest();
}

// start of loop ///////////////////////////////////////////////////////////////////////

void loop()
{
    // searchI2CPorts2();
    // return;

    loopWifi();
    loopInput();

    // debugInput();

    // Driving
    if (ibusVar00 != 0 && ibusVar01 != 0)
    {
        chopper->body->setDriveHorizontal(ibusVar00);
        chopper->body->setDriveVertical(ibusVar01);
    }
    else
    {
        int16_t newX = map(webServer->joy1_x, -100, 100, 1000, 2000);
        chopper->body->setDriveHorizontal(newX);

        int16_t newY = map(webServer->joy1_y, -100, 100, 1000, 2000);
        chopper->body->setDriveVertical(newY);
    }

    // Dome & Periscope Rotation
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

        if (ibusVar03 != 0)
        {
            chopper->body->setDomeRotation(ibusVar03);
        }
        else
        {
            chopper->body->setDomeRotation(webServer->domeRotate);
        }
    }

    // Dome Arms
    chopper->dome->setRightArmExtend(ibusVar05);
    chopper->dome->setLeftArmExtend(ibusVar04);

    chopper->dome->setRightArmRotation(ibusVar05);
    chopper->dome->setLeftArmRotation(ibusVar04);

    // Dome Shake
    if (ibusVar07 == 2000)
    {
        chopper->body->domeShake = true;
    }
    else
    {
        chopper->body->domeShake = false;
    }

    // Lights
    if (ibusVar09 == 2000)
    {
        chopper->lights->currentMood = ChopperLights::LightsMood::terminator;
    }
    else
    {
        chopper->lights->currentMood = ChopperLights::LightsMood::basic;
    }

    if (ibusVar02 >= 1650 && ibusVar02 <= 2000)
    {
        chopper->lights->periscopeIsOn = true;
    }
    else
    {
        chopper->lights->periscopeIsOn = false;
    }

    // Body Tools
    if (ibusVar06 != 0)
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
    else
    {
        chopper->body->bodyArmLeft = webServer->bodyArmLeft;
    }

    if (ibusVar09 != 0)
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
    else
    {
        chopper->body->bodyArmRight = webServer->bodyArmRight;
    }

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

    // Do Main Loop
    chopper->loop();

    // loopAudio();
    // Serial.print( stack_unused() ); Serial.print(F(" -> ")); Serial.println( stack_free() );

    // testTaskManager.loop();

    // Serial.print("globalBool is: ");
    // // bool globalBoolValue = *globalBool;
    // Serial.println(globalBool == true ? "-----------------true" : "-----------------false");
}

// end of loop ///////////////////////////////////////////////////////////////////////////////////////////