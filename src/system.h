// #include <Arduino.h>
// #ifdef __AVR__
// #include <avr/power.h>
// #endif

// #include <Wire.h>
// #include "searchI2cPorts.h"

// #ifdef ESP32
// #include <WiFi.h>
// #include <AsyncTCP.h>
// #elif defined(ESP8266)
#include <ESP8266WiFi.h>
// #endif

#define SERIAL_PORT_SPEED 115200 // Define the port output serial communication speed

// #include "SoftwareSerial.h"
// #include <DFPlayerMini_Fast.h>

#include "definitions.h"

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

    // Wifi Settings
    wifi->host = IPAddress(192, 168, 10, 1);
    wifi->subnetMask = IPAddress(255, 255, 255, 0);
    wifi->currentMode = JxWifiManager::WifiModeNetwork;

    // Hotspot
    wifi->hotspot_Ssid = "ChopperWifiControl";
    wifi->hotspot_Password = "<YOUR WIFI PASSWORD>";

    // use Local Wifi
    wifi->network_Ssid = "Yavin4"; // <- change if needed
    wifi->network_Password = "29833170985536833475";

    setupInput();

    chopper->setup();

    wifi->setup();
    webServer->start();

    // setupAudio();

    // setupTest();
}

// start of loop ///////////////////////////////////////////////////////////////////////

void loop()
{
    // searchI2CPorts2();
    // return;

    wifi->loop();

    loopInput();

    // debugInput();

    // Driving
    if (ibusVar00 != 0 && ibusVar01 != 0)
    {
        chopper->horizontal = ibusVar00;
        chopper->vertical = ibusVar01;
    }
    else
    {
        int16_t newX = map(webServer->drive_x, -100, 100, 1000, 2000);
        chopper->horizontal = newX;

        int16_t newY = map(webServer->drive_y, -100, 100, 1000, 2000);
        chopper->vertical = newY;
    }

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

            if (ibusVar03 != 0)
            {
                chopper->body->setDomeRotation(ibusVar03);
            }
            else
            {
                chopper->body->setDomeRotation(webServer->domeRotate);
            }
        }
    }
    else
    {
        Serial.println(F("Do Webserver Dome Rotation action"));
        chopper->body->setDomeRotation(webServer->domeRotate);


        Serial.println(F("Do Webserver periscope action"));
        int16_t liftPeriscope = map(webServer->domePeriscopeLift, 1000, 2000, 0, 255);
        chopper->dome->setPeriscopeLift(liftPeriscope);

        int16_t rotationPeriscope = map(webServer->domePeriscopeRotate, 1000, 2000, -127, 127);
        chopper->dome->setPeriscopeRotation(rotationPeriscope);
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

        chopper->body->utilityArm = webServer->utilityArm;
        if (webServer->utilityArmGripper && webServer->utilityArm)
        {
            chopper->body->utilityArmGripper = true;
        }
        else
        {
            chopper->body->utilityArmGripper = false;
        }
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