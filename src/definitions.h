
bool debug = false;

#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver *pwm_body = new Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver *pwm_dome = new Adafruit_PWMServoDriver(0x60);

#include "classes/DYPlayerESP32SoftwareSerial.h"
DY::PlayerEsp32SoftwareSerial player(UART_NUM_2, 26, 25);

#include "classes/Chopper.h"
Chopper *chopper = new Chopper(pwm_body, pwm_dome, &player,  debug);

// RC values coming from the iBUS RC-Reciever
#include <IBusBM.h>
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
