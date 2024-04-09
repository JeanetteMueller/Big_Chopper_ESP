
bool debug = true;

// Wifi Settings

//Hotspot
// #define WiFiMode 0
// #define WifiSsid "ChopperWifiControl"
// #define WifiPassword "<YOUR WIFI PASSWORD>"

//use Local Wifi
#define WiFiMode 1
#define WifiSsid "Yavin4" // <- change if needed
#define WifiPassword "29833170985536833475"

IPAddress apIP(192, 168, 10, 1); //only for WiFiMode Mode 0
#define ServerPort 80

#include "classes/WebServer.h"
WebServer *webServer = new WebServer(ServerPort);

#include "classes/Chopper.h"
Chopper *chopper = new Chopper(debug);

// RC values coming from the iBUS RC-Reciever
IBusBM *IBus = new IBusBM();
uint16_t ibusVar00 = 0;
uint16_t ibusVar01 = 0;
uint16_t ibusVar02 = 0;
uint16_t ibusVar03 = 0;
uint16_t ibusVar04 = 0;
uint16_t ibusVar05 = 0;
uint16_t ibusVar06 = 0;
uint16_t ibusVar07 = 0;
uint16_t ibusVar08 = 0;
uint16_t ibusVar09 = 0;

#define RC_STICK_RIGHT_H (byte)0
#define RC_STICK_RIGHT_V (byte)1
#define RC_STICK_LEFT_V (byte)2
#define RC_STICK_LEFT_H (byte)3
#define RC_TURN_LEFT (byte)4
#define RC_TURN_RIGHT (byte)5
#define RC_SWITCH_LEFT_OUT (byte)6
#define RC_SWITCH_LEFT_IN (byte)7
#define RC_SWITCH_RIGHT_IN (byte)8
#define RC_SWITCH_RIGHT_OUT (byte)9


// Audio
// SoftwareSerial mySerial(6,5); // RX, TX
// DFPlayerMini_Fast player;
// bool directStart = true;
// uint16_t audioPause = 2000;
// uint16_t audioItemCount = 0;
