
#include "ChopperBody.h"

ChopperBody::ChopperBody(bool debug)
{
    _debug = debug;
}

void ChopperBody::setupDomeShake()
{
    uint16_t centerPosition = 57;
    uint16_t shakeRange = 30;

    domeShakeTaskManager.addTask(new BoolValueTask(&domeShake, true));

    domeShakeTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_domeShake, centerPosition, centerPosition + shakeRange, 200));

    domeShakeTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_domeShake, centerPosition + shakeRange, centerPosition - shakeRange, 400));

    domeShakeTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_domeShake, centerPosition - shakeRange, centerPosition, 200));
}
void ChopperBody::setupLeftBodyArm()
{
    // bodyLeftArmTaskManager.addTask(new InputTask(IBus, RC_SWITCH_LEFT_OUT, 2000, -1));
    bodyLeftArmTaskManager.addTask(new BoolValueTask(&bodyArmLeft, true));
    // Door Open
    bodyLeftArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_left_door, default_door_left, max_door_left, 200, 200));
    // Bring Tool out
    bodyLeftArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_left_toollift, default_toollift_left, max_toollift_left, 300, 200));
    // Use Tool
    bodyLeftArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_left_action, default_action_left, max_action_left, 200, 400));
    bodyLeftArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_left_action, max_action_left, default_action_left, 200, 400));
    bodyLeftArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_left_action, default_action_left, max_action_left, 200, 400));

    // react on Switch to Bring all in
    // bodyLeftArmTaskManager.addTask(new InputTask(IBus, RC_SWITCH_LEFT_OUT, 1000));
    bodyLeftArmTaskManager.addTask(new BoolValueTask(&bodyArmLeft, false));
    // move tool to retracted position
    bodyLeftArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_left_action, max_action_left, default_action_left, 200, 400));
    // Bring Tool in
    bodyLeftArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_left_toollift, max_toollift_left, default_toollift_left, 300, 500));
    // Door close
    bodyLeftArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_left_door, max_door_left, default_door_left, 200, 200));
}

void ChopperBody::setupRightBodyArm()
{
    // check if swith is active
    // bodyRightArmTaskManager.addTask(new InputTask(IBus, RC_SWITCH_RIGHT_OUT, 2000));
    bodyRightArmTaskManager.addTask(new BoolValueTask(&bodyArmRight, true));
    // open door
    bodyRightArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_right_door, default_door_right, max_door_right, 200, 200));
    // bring tool out
    bodyRightArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_right_toollift, default_toollift_right, max_toollift_right, 300, 600));
    // Use tool, rotate Saw
    bodyRightArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_right_action, default_action_right, max_action_right, 200, 200));

    // react on switch to bring all in
    // bodyRightArmTaskManager.addTask(new InputTask(IBus, RC_SWITCH_RIGHT_OUT, 1000));
    bodyRightArmTaskManager.addTask(new BoolValueTask(&bodyArmRight, false));
    // stop saw
    bodyRightArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_right_action, max_action_right, default_action_right, 200, 0));
    // bring tool in
    bodyRightArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_right_toollift, max_toollift_right, default_toollift_right, 300, 500));
    // close door
    bodyRightArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_right_door, max_door_right, default_door_right, 200, 200));
}

void ChopperBody::setupUtilityArm()
{
    bodyUtilityArmTaskManager.addTask(new BoolValueTask(&utilityArm, true));
    // bring arm out
    bodyUtilityArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_utilityarm, default_utility_arm, max_utility_arm, 800));

    bodyUtilityArmTaskManager.addTask(new BoolValueTask(&utilityArm, false));
    // close gripper
    bodyUtilityArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_utilityarmgripper, default_utility_gripper, default_utility_gripper, 0, 50));
    // bring arm in
    bodyUtilityArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_utilityarm, max_utility_arm, default_utility_arm, 700));
}

void ChopperBody::setupUtilityGripper()
{
    bodyUtilityArmGripperTaskManager.addTask(new BoolValueTask(&utilityArmGripper, true));
    // open Gripper
    bodyUtilityArmGripperTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_utilityarmgripper, default_utility_gripper, max_utility_gripper, 300, 200));

    bodyUtilityArmGripperTaskManager.addTask(new BoolValueTask(&utilityArmGripper, false));
    // close Gripper
    bodyUtilityArmGripperTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_utilityarmgripper, max_utility_gripper, default_utility_gripper, 300, 200));
}

void ChopperBody::setup()
{
    pwm_body.begin();
    pwm_body.setOscillatorFrequency(27000000);
    pwm_body.setPWMFreq(_SERVO_FREQ);

    drive->setupLeftMotor(pwm_body, pwm_body_pin_drive_left_dir, pwm_body_pin_drive_left_pwm);
    drive->setupRightMotor(pwm_body, pwm_body_pin_drive_right_dir, pwm_body_pin_drive_right_pwm);

    domeRotation->setupMotor(pwm_body, pwm_body_pin_dome_rotation_dir, pwm_body_pin_dome_rotation_pwm);

    setupDomeShake();

    setupLeftBodyArm();
    setupRightBodyArm();
    setupUtilityArm();
    setupUtilityGripper();
}
void ChopperBody::loop()
{   
    drive->updateMotorsWith(horizontal, vertical, 5, 150);

    bodyLeftArmTaskManager.loop();
    bodyRightArmTaskManager.loop();
    bodyUtilityArmTaskManager.loop();
    bodyUtilityArmGripperTaskManager.loop();
    domeShakeTaskManager.loop();

    // if (_debug)
    // {
    //     Serial.print("updateMotorsWith: ");
    //     Serial.print(_horizontal);
    //     Serial.print(" - ");
    //     Serial.println(_vertical);
    // }

    domeRotation->updateMotorWith(_rotation, 25);
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
    pwm_body.setPWM(servo, 0, pulselength);
}