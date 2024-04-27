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
        chopper->horizontal = 1500;
        chopper->vertical = 1500;
    }

    // Dome & Periscope Rotation
    if (ibusVar02 != 0 && ibusVar03 != 0)
    {
        if (ibusVar02 >= 1500 && ibusVar02 <= 2000)
        {
            chopper->body->setDomeRotation(1500);
            webServer->domeRotate = 1500;

            int16_t liftPeriscope = map(ibusVar02, 1500, 2000, 0, 255);
            chopper->dome->setPeriscopeLift(liftPeriscope);
            webServer->domePeriscopeLift = liftPeriscope;

            int16_t rotationPeriscope = map(ibusVar03, 1000, 2000, -127, 127);
            chopper->dome->setPeriscopeRotation(rotationPeriscope);
            webServer->domePeriscopeRotate = rotationPeriscope;
        }
        else
        {
            chopper->dome->setPeriscopeLift(0);
            chopper->dome->setPeriscopeRotation(0);

            chopper->body->setDomeRotation(ibusVar03);
            webServer->domeRotate = ibusVar03;
        }
    }
    else
    {
        chopper->body->setDomeRotation(webServer->domeRotate);
        chopper->dome->setPeriscopeLift(webServer->domePeriscopeLift);
        chopper->dome->setPeriscopeRotation(webServer->domePeriscopeRotate);
    }

    
    

    // Dome Right Arm
    if (ibusVar05 != 0)
    {
        if (ibusVar05 >= 1000 && ibusVar05 <= 2000)
        {
            chopper->dome->setRightArmExtend(ibusVar05);
            chopper->dome->setRightArmRotation(ibusVar05);
            webServer->domeArmsRightRotate = ibusVar05;
        }
    }
    else
    {
        chopper->dome->setRightArmExtend(webServer->domeArmsRightExtend);
        chopper->dome->setRightArmRotation(webServer->domeArmsRightRotate);
    }

    // Dome Left Arm
    if (ibusVar04 != 0)
    {
        if (ibusVar04 >= 1000 && ibusVar04 <= 2000)
        {
            chopper->dome->setLeftArmExtend(ibusVar04);
            chopper->dome->setLeftArmRotation(ibusVar04);
            webServer->domeArmsLeftRotate = ibusVar04;
        }
    }
    else
    {
        chopper->dome->setLeftArmExtend(webServer->domeArmsLeftExtend);
        chopper->dome->setLeftArmRotation(webServer->domeArmsLeftRotate);
    }

    // Dome Shake
    if (ibusVar07 != 0)
    {
        if (ibusVar07 == 2000)
        {
            chopper->body->domeShake = true;
            webServer->domeShake = true;
        }
        else
        {
            chopper->body->domeShake = false;
            webServer->domeShake = false;
        }
    }
    else
    {
        chopper->body->domeShake = webServer->domeShake;
    }

    

    // Body Tools
    if (ibusVar06 != 0)
    {
        if (ibusVar06 >= 1500 && ibusVar06 <= 2000)
        {
            chopper->body->bodyArmLeft = true;
            webServer->bodyArmLeft = true;
        }
        else
        {
            chopper->body->bodyArmLeft = false;
            webServer->bodyArmLeft = false;
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
            webServer->bodyArmRight = true;
        }
        else
        {
            chopper->body->bodyArmRight = false;
            webServer->bodyArmRight = false;
        }
    }
    else
    {
        chopper->body->bodyArmRight = webServer->bodyArmRight;
    }


    // Lights
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

    //Utility Arms
    if (ibusVar08 != 0)
    {
        if (ibusVar08 >= 1500 && ibusVar08 <= 2000)
        {
            chopper->body->utilityArm = true;
            webServer->utilityArm = true;
            if (ibusVar08 == 2000)
            {
                chopper->body->utilityArmGripper = true;
                webServer->utilityArmGripper = true;
            }
            else
            {
                chopper->body->utilityArmGripper = false;
                webServer->utilityArmGripper = false;
            }
        }
        else
        {
            chopper->body->utilityArmGripper = false;
            webServer->utilityArmGripper = false;

            chopper->body->utilityArm = false;
            webServer->utilityArm = false;
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