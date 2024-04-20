
#include "ChopperDome.h"

ChopperDome::ChopperDome(bool debug)
{
    _debug = debug;
}

void ChopperDome::setupRightArmTools()
{
    rotateServoToDegree(pwm_head_pin_arms_right_door, _rightArmDoor_min);
    rotateServoToDegree(pwm_head_pin_arms_right_rotate, _rightArmRotate_doorsafe);
    rotateServoToDegree(pwm_head_pin_arms_right_extruder, _rightArmExtruder_min);
    rotateServoToDegree(pwm_head_pin_arms_right_extend, _rightArmExtend_min);

    double extendMin = 1010;
    double extendMax = 2010;
    double extendClosed = 1000;

    // check if swith is active
    domeRightArmTaskManager.addTask(new DoubleValueTask(&_rightArmExtend_target, extendMin, extendMax));
    // open door
    domeRightArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_right_door, _rightArmDoor_min, _rightArmDoor_max, 300, 100));
    // rotate arm to hole
    domeRightArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_right_rotate, _rightArmRotate_doorsafe, _rightArmRotate_min, 300, 200));
    // bring arm out
    domeRightArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_right_extruder, _rightArmExtruder_min, _rightArmExtruder_max, 800, 500));
    // stretch arm to current position
    // domeRightArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_right_extend, _rightArmExtend_min, current_extendRightArm, 400)); // 110
    domeRightArmTaskManager.addTask(new ChangeBoolTask(&rightArmIsReady, true));
    // wait here to bring right arm in and close doors
    // check if arm is vertical
    domeRightArmTaskManager.addTask(new DoubleValueTask(&_rightArmExtend_target, extendClosed));
    domeRightArmTaskManager.addTask(new ChangeBoolTask(&rightArmIsReady, false));
    // stretch arm to min
    domeRightArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_right_extend, current_extendRightArm, _rightArmExtend_min, 500));
    // rotate arm to center
    domeRightArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_right_rotate, current_rotateRightArm, _rightArmRotate_min, 500));
    // bring arm in
    domeRightArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_right_extruder, _rightArmExtruder_max, _rightArmExtruder_min, 800, 200));
    // rotate arm away from hole
    domeRightArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_right_rotate, _rightArmRotate_min, _rightArmRotate_doorsafe, 300, 200));
    // close door
    domeRightArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_right_door, _rightArmDoor_max, _rightArmDoor_min, 300, 200));
}

void ChopperDome::setupLeftArmTools()
{
    rotateServoToDegree(pwm_head_pin_arms_left_door, _leftArmDoor_min);
    rotateServoToDegree(pwm_head_pin_arms_left_rotate, _leftArmRotate_doorsafe);
    rotateServoToDegree(pwm_head_pin_arms_left_extruder, _leftArmExtruder_min);
    rotateServoToDegree(pwm_head_pin_arms_left_extend, _leftArmExtend_min);

    double extendMin = 1010;
    double extendMax = 2010;
    double extendClosed = 1000;

    // check if swith is active
    domeLeftArmTaskManager.addTask(new DoubleValueTask(&_leftArmExtend_target, extendMin, extendMax));
    // open door
    domeLeftArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_left_door, _leftArmDoor_min, _leftArmDoor_max, 300, 100));
    // rotate arm to hole
    domeLeftArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_left_rotate, _leftArmRotate_doorsafe, _leftArmRotate_min, 300, 200));
    // bring arm out
    domeLeftArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_left_extruder, _leftArmExtruder_min, _leftArmExtruder_max, 800, 500));
    // stretch arm to current position
    // domeLeftArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_left_extend, _leftArmExtend_min, current_extendLeftArm, 400)); // 110
    domeLeftArmTaskManager.addTask(new ChangeBoolTask(&leftArmIsReady, true));
    // wait here to bring left arm in and close doors
    // check if arm is vertical
    domeLeftArmTaskManager.addTask(new DoubleValueTask(&_leftArmExtend_target, extendClosed));
    domeLeftArmTaskManager.addTask(new ChangeBoolTask(&leftArmIsReady, false));
    // stretch arm to min
    domeLeftArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_left_extend, current_extendLeftArm, _leftArmExtend_min, 500));
    // rotate arm to center
    domeLeftArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_left_rotate, current_rotateLeftArm, _leftArmRotate_min, 500));
    // bring arm in
    domeLeftArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_left_extruder, _leftArmExtruder_max, _leftArmExtruder_min, 800, 200));
    // rotate arm away from hole
    domeLeftArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_left_rotate, _leftArmRotate_min, _leftArmRotate_doorsafe, 300, 200));
    // close door
    domeLeftArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_left_door, _leftArmDoor_max, _leftArmDoor_min, 300, 200));
}

void ChopperDome::setup()
{
    pwm_head.begin();
    pwm_head.setOscillatorFrequency(27000000);
    pwm_head.setPWMFreq(_SERVO_FREQ);

    setupRightArmTools();
    setupLeftArmTools();
}
void ChopperDome::loop()
{
    domeRightArmTaskManager.loop();
    domeLeftArmTaskManager.loop();

    rotateServoToDegree(pwm_head_pin_periscope_lift, _liftPeriscope);
    rotateServoToDegree(pwm_head_pin_periscope_rotate, _rotationPeriscope);

    if (rightArmIsReady == true)
    {
        if (_rightArmExtend_target >= 1200 && _rightArmExtend_target <= 2000)
        {
            current_extendRightArm = map(_rightArmExtend_target, 1200, 2000, _rightArmExtend_min, _rightArmExtend_max);
            rotateServoToDegree(pwm_head_pin_arms_right_extend, current_extendRightArm);
        }

        if (_rightArmRotate_target >= 1000 && _rightArmRotate_target <= 2000)
        {
            current_rotateRightArm = map(_rightArmRotate_target, 1000, 2000, _rightArmRotate_min, _rightArmRotate_max);
            rotateServoToDegree(pwm_head_pin_arms_right_rotate, current_rotateRightArm);
        }
    }

    if (leftArmIsReady == true)
    {
        if (_leftArmExtend_target >= 1200 && _leftArmExtend_target <= 2000)
        {
            current_extendLeftArm = map(_leftArmExtend_target, 1200, 2000, _leftArmExtend_min, _leftArmExtend_max);
            rotateServoToDegree(pwm_head_pin_arms_left_extend, current_extendLeftArm);
        }

        if (_leftArmRotate_target >= 1000 && _leftArmRotate_target <= 2000)
        {
            current_rotateLeftArm = map(_leftArmRotate_target, 1000, 2000, _leftArmRotate_min, _leftArmRotate_max);
            rotateServoToDegree(pwm_head_pin_arms_left_rotate, current_rotateLeftArm);
        }
    }
}
void ChopperDome::setPeriscopeLift(uint8_t liftValue)
{
    _liftPeriscope = map(liftValue, 0, 255, _minPeriscopeLift, _maxPeriscopeLift);

    if (_liftPeriscope < _minPeriscopeLift)
    {
        _liftPeriscope = _minPeriscopeLift;
    }
}
void ChopperDome::setPeriscopeRotation(int8_t rotationValue)
{
    if (rotationValue >= -127 && rotationValue <= 127)
    {
        _rotationPeriscope = map(rotationValue, -127, 127, _minPeriscopeRotation, _maxPeriscopeRotation);
    }
}

void ChopperDome::setLeftArmExtend(bool extend)
{
    _leftArmExtend_target = extend ? 1010 : 1000;
}
void ChopperDome::setRightArmExtend(bool extend)
{
    _rightArmExtend_target = extend ? 1010 : 1000;
}

void ChopperDome::setLeftArmRotation(double rotation)
{
    _leftArmRotate_target = rotation;
}
void ChopperDome::setRightArmRotation(double rotation)
{
    _rightArmRotate_target = rotation;
}

void ChopperDome::rotateServoToDegree(uint8_t servo, double degree)
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
    pwm_head.setPWM(servo, 0, pulselength);
}