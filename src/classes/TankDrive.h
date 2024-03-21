
#ifndef TankDrive_h
#define TankDrive_h

#include "Arduino.h"
#include <CytronMotorDriver.h>

class TankDrive
{
public:
    TankDrive(uint16_t inputMin, uint16_t inputMax, uint16_t inputCenter);

    void setupLeftMotor(MODE mode, uint8_t pin1, uint8_t pin2);
    void setupRightMotor(MODE mode, uint8_t pin1, uint8_t pin2);

    void updateMotorsWith(uint16_t horizontal, uint16_t vertical, uint16_t deadPoint, int16_t maxSpeed);
    void stop();

    int16_t currentSpeedLeft() const { return _speedLeft; };
    int16_t currentSpeedRight() const { return _speedRight; };
private:

    int16_t _inputMin = -500;
    int16_t _inputMax = 500;
    int16_t _inputCenter = 0;

    int16_t _speedLeft = 0;
    int16_t _speedRight = 0;
    CytronMD *_motorLeft;
    CytronMD *_motorRight;

    void updateSpeed();
};

#endif