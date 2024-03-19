
void setupDrive()
{
  // set leg motors to zero

  Motor_Dive_Left.setSpeed(0);
  Motor_Dive_Right.setSpeed(0);

  analogWriteFreq(18000); // 18khz for less noisy motor drive
}

void initLoopDrive()
{
  leftMotorSpeedTarget = 0;
  rightMotorSpeedTarget = 0;
}

void loopDrive()
{
  uint16_t deadPoint = 5;
  uint16_t minValue = 1000;
  uint16_t maxValue = 2000;
  uint16_t centerPoint = 1500;
  int16_t maxSpeed = 120; // of 255

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
  leftMotorSpeedTarget = constrain(leftMotorSpeedTarget, -(maxSpeed), maxSpeed);
  rightMotorSpeedTarget = constrain(rightMotorSpeedTarget, -(maxSpeed), maxSpeed);
}

void updateDriveSpeed()
{
  leftMotorSpeed = leftMotorSpeedTarget;
  rightMotorSpeed = rightMotorSpeedTarget;

  Motor_Dive_Left.setSpeed(leftMotorSpeed);
  Motor_Dive_Right.setSpeed(rightMotorSpeed);
}