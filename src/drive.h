
#include "Arduino.h"

void setupDrive()
{
  // set leg motors to zero

  Motor_Dive_Left.setSpeed(0);
  Motor_Dive_Right.setSpeed(0);

  analogWriteFreq(18000); // 18khz for less noisy motor drive
}

void loopDrive()
{
  int16_t leftMotorSpeedTarget = 0;
  int16_t rightMotorSpeedTarget = 0;

  uint16_t deadPoint = 5;
  uint16_t minValue = 1000;
  uint16_t maxValue = 2000;
  uint16_t centerPoint = 1500;
  int16_t maxSpeed = 150; // of 255

  if (driveValueVertical < centerPoint - deadPoint || driveValueVertical > centerPoint + deadPoint)
  {
    joystickY = map(driveValueVertical, minValue, maxValue, maxSpeed, -(maxSpeed));

    // Convert joystick values to motor speeds
    leftMotorSpeedTarget += joystickY;
    rightMotorSpeedTarget += joystickY;
  }

  if (driveValueHorizontal < centerPoint - deadPoint || driveValueHorizontal > centerPoint + deadPoint)
  {
    joystickX = map(driveValueHorizontal, minValue, maxValue, maxSpeed, -(maxSpeed));

    leftMotorSpeedTarget += joystickX;
    rightMotorSpeedTarget -= joystickX;
  }

  // Make sure motor speeds are within range
  leftMotorSpeed = constrain(leftMotorSpeedTarget, -(maxSpeed), maxSpeed);
  rightMotorSpeed = constrain(rightMotorSpeedTarget, -(maxSpeed), maxSpeed);

  Motor_Dive_Left.setSpeed(leftMotorSpeed);
  Motor_Dive_Right.setSpeed(rightMotorSpeed);
}