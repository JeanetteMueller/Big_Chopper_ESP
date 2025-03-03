
#include "ChopperBody.h"

ChopperBody::ChopperBody(Adafruit_PWMServoDriver *pwm, bool debug)
{
  _debug = debug;

  _pwm_body = pwm;

  _drive = new JxTankDriver(1000, 2000, 1500);
  _domeRotation = new JxDomeRotation(1000, 2000, 1500);

  _bodyLeftArmTaskManager = new JxTaskManager("bodyLeftArmTaskManager", _debug);
  _bodyRightArmTaskManager = new JxTaskManager("bodyRightArmTaskManager", _debug);
  _bodyUtilityArmTaskManager = new JxTaskManager("bodyUtilityArmTaskManager", _debug);
  _bodyUtilityArmGripperTaskManager = new JxTaskManager("bodyUtilityArmGripperTaskManager", _debug);
  _domeShakeTaskManager = new JxTaskManager("domeShakeTaskManager", _debug);
}

void ChopperBody::setupDomeShake()
{
  uint16_t centerPosition = 57;
  uint16_t shakeRange = 30;

  _domeShakeTaskManager->addTask(new BoolValueTask(&domeShake, true, _debug));

  _domeShakeTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_domeShake, centerPosition, centerPosition + shakeRange, 200, _debug));

  _domeShakeTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_domeShake, centerPosition + shakeRange, centerPosition - shakeRange, 400, _debug));

  _domeShakeTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_domeShake, centerPosition - shakeRange, centerPosition, 200, _debug));
}
void ChopperBody::setupLeftBodyArm()
{
  // bodyLeftArmTaskManager->addTask(new InputTask(IBus, RC_SWITCH_LEFT_OUT, 2000, -1));
  _bodyLeftArmTaskManager->addTask(new BoolValueTask(&bodyArmLeft, true));
  // Door Open
  _bodyLeftArmTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_left_door, _default_door_left, _max_door_left, 200, 200, _debug));
  // Bring Tool out
  _bodyLeftArmTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_left_toollift, _default_toollift_left, _max_toollift_left, 300, 200, _debug));
  // Use Tool
  _bodyLeftArmTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_left_action, _default_action_left, _max_action_left, 200, 400, _debug));
  _bodyLeftArmTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_left_action, _max_action_left, _default_action_left, 200, 400, _debug));
  _bodyLeftArmTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_left_action, _default_action_left, _max_action_left, 200, 400, _debug));

  // react on Switch to Bring all in
  // bodyLeftArmTaskManager->addTask(new InputTask(IBus, RC_SWITCH_LEFT_OUT, 1000));
  _bodyLeftArmTaskManager->addTask(new BoolValueTask(&bodyArmLeft, false, _debug));
  // move tool to retracted position
  _bodyLeftArmTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_left_action, _max_action_left, _default_action_left, 200, 400, _debug));
  // Bring Tool in
  _bodyLeftArmTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_left_toollift, _max_toollift_left, _default_toollift_left, 300, 500, _debug));
  // Door close
  _bodyLeftArmTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_left_door, _max_door_left, _default_door_left, 200, 20, _debug));
}

void ChopperBody::setupRightBodyArm()
{
  // check if swith is active
  // bodyRightArmTaskManager->addTask(new InputTask(IBus, RC_SWITCH_RIGHT_OUT, 2000));
  _bodyRightArmTaskManager->addTask(new BoolValueTask(&bodyArmRight, true, _debug));
  // open door
  _bodyRightArmTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_right_door, _default_door_right, _max_door_right, 200, 200, _debug));
  // bring tool out
  _bodyRightArmTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_right_toollift, _default_toollift_right, _max_toollift_right, 300, 600, _debug));
  // Use tool, rotate Saw
  _bodyRightArmTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_right_action, _default_action_right, _max_action_right, 200, 200, _debug));

  // react on switch to bring all in
  // bodyRightArmTaskManager->addTask(new InputTask(IBus, RC_SWITCH_RIGHT_OUT, 1000));
  _bodyRightArmTaskManager->addTask(new BoolValueTask(&bodyArmRight, false, _debug));
  // stop saw
  _bodyRightArmTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_right_action, _max_action_right, _default_action_right, 200, 0, _debug));
  // bring tool in
  _bodyRightArmTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_right_toollift, _max_toollift_right, _default_toollift_right, 300, 500, _debug));
  // close door
  _bodyRightArmTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_right_door, _max_door_right, _default_door_right, 200, 200, _debug));
}

void ChopperBody::setupUtilityArm()
{
  _bodyUtilityArmTaskManager->addTask(new BoolValueTask(&utilityArm, true, _debug));
  // bring arm out
  _bodyUtilityArmTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_utilityarm, _default_utility_arm, _max_utility_arm, 800, _debug));

  _bodyUtilityArmTaskManager->addTask(new BoolValueTask(&utilityArm, false, _debug));
  // close gripper
  _bodyUtilityArmTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_utilityarmgripper, _default_utility_gripper, _default_utility_gripper, 0, 50, _debug));
  // bring arm in
  _bodyUtilityArmTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_utilityarm, _max_utility_arm, _default_utility_arm, 700, _debug));
}

void ChopperBody::setupUtilityGripper()
{
  _bodyUtilityArmGripperTaskManager->addTask(new BoolValueTask(&utilityArmGripper, true, _debug));
  // open Gripper
  _bodyUtilityArmGripperTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_utilityarmgripper, _default_utility_gripper, _max_utility_gripper, 300, 200, _debug));

  _bodyUtilityArmGripperTaskManager->addTask(new BoolValueTask(&utilityArmGripper, false, _debug));
  // close Gripper
  _bodyUtilityArmGripperTaskManager->addTask(new MoveServoTask(_pwm_body, pwm_body_pin_utilityarmgripper, _max_utility_gripper, _default_utility_gripper, 300, 200, _debug));
}

void ChopperBody::setup()
{
  // _drive->setupLeftMotor(_pwm_body, pwm_body_pin_drive_left_dir, pwm_body_pin_drive_left_pwm);
  // _drive->setupRightMotor(_pwm_body, pwm_body_pin_drive_right_dir, pwm_body_pin_drive_right_pwm);

  _drive->setupRightMotor(PWM_DIR, 33, 32);
  _drive->setupLeftMotor(PWM_DIR, 2, 15);

  _domeRotation->setupMotor(_pwm_body, pwm_body_pin_dome_rotation_dir, pwm_body_pin_dome_rotation_pwm);

  setupLeftBodyArm();
  setupRightBodyArm();
  setupUtilityArm();
  setupUtilityGripper();
  setupDomeShake();
}
void ChopperBody::loop()
{
  _drive->updateMotorsWith(horizontal, vertical, 5, 600);

  _bodyLeftArmTaskManager->loop();
  _bodyRightArmTaskManager->loop();
  _bodyUtilityArmTaskManager->loop();
  _bodyUtilityArmGripperTaskManager->loop();
  _domeShakeTaskManager->loop();

  // if (_debug) {
  //   Serial.print("updateMotorsWith: ");
  //   Serial.print(horizontal);
  //   Serial.print(" - ");
  //   Serial.println(vertical);
  // }

  _domeRotation->updateMotorWith(_rotation, 5);
}

void ChopperBody::setDomeRotation(int16_t rotation)
{
  _rotation = rotation;
}

void ChopperBody::rotateServoToDegree(uint8_t servo, double degree)
{
  uint16_t pulselength = map(degree, 0, 180, _SERVOMIN, _SERVOMAX); //  Calibrate the positive range (see below)
  /*
    Serial.print(F("rotateServoToDegree Servo: "));
    Serial.print(servo);
    Serial.print(F(" to Degree: "));
    Serial.print(degree);
    Serial.print(F(" with Pulselength: "));
    Serial.println(pulselength);
    */
  _pwm_body->setPWM(servo, 0, pulselength);
}