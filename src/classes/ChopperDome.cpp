
#include "ChopperDome.h"

ChopperDome::ChopperDome(Adafruit_PWMServoDriver *pwm, bool debug)
{
  _debug = debug;

  _pwm_dome = pwm;

  _domeRightArmTaskManager = new JxTaskManager("domeRightArmTaskManager", _debug);
  _domeLeftArmTaskManager = new JxTaskManager("domeLeftArmTaskManager", _debug);
}

void ChopperDome::setupRightArmTools()
{
  rotateServoToDegree(pwm_head_pin_arms_right_door, _rightArmDoor_min);
  rotateServoToDegree(pwm_head_pin_arms_right_extruder, _rightArmExtruder_min);

  double extendMin = 1010;
  double extendMax = 2000;
  double extendClosed = 1000;

  // check if swith is active
  _domeRightArmTaskManager->addTask(new DoubleValueTask(&_rightArmExtend_target, extendMin, extendMax));
  // open door
  _domeRightArmTaskManager->addTask(new MoveServoTask(_pwm_dome, pwm_head_pin_arms_right_door, _rightArmDoor_min, _rightArmDoor_max, 300, 100));
  // bring arm out
  _domeRightArmTaskManager->addTask(new MoveServoTask(_pwm_dome, pwm_head_pin_arms_right_extruder, _rightArmExtruder_min, _rightArmExtruder_max, 800, 500));
  _domeRightArmTaskManager->addTask(new ChangeBoolTask(&rightArmIsReady, true));
  // wait here to bring right arm in and close doors
  // check if arm is vertical
  _domeRightArmTaskManager->addTask(new DoubleValueTask(&_rightArmExtend_target, extendClosed));
  _domeRightArmTaskManager->addTask(new ChangeBoolTask(&rightArmIsReady, false));
  // bring arm in
  _domeRightArmTaskManager->addTask(new MoveServoTask(_pwm_dome, pwm_head_pin_arms_right_extruder, _rightArmExtruder_max, _rightArmExtruder_min, 800, 200));
  // close door
  _domeRightArmTaskManager->addTask(new MoveServoTask(_pwm_dome, pwm_head_pin_arms_right_door, _rightArmDoor_max, _rightArmDoor_min, 300, 200));
}

void ChopperDome::setupLeftArmTools()
{
  rotateServoToDegree(pwm_head_pin_arms_left_door, _leftArmDoor_min);
  rotateServoToDegree(pwm_head_pin_arms_left_extruder, _leftArmExtruder_min);

  double extendMin = 1010;
  double extendMax = 2000;
  double extendClosed = 1000;

  // check if swith is active
  _domeLeftArmTaskManager->addTask(new DoubleValueTask(&_leftArmExtend_target, extendMin, extendMax));
  // open door
  _domeLeftArmTaskManager->addTask(new MoveServoTask(_pwm_dome, pwm_head_pin_arms_left_door, _leftArmDoor_min, _leftArmDoor_max, 300, 100));
  // bring arm out
  _domeLeftArmTaskManager->addTask(new MoveServoTask(_pwm_dome, pwm_head_pin_arms_left_extruder, _leftArmExtruder_min, _leftArmExtruder_max, 800, 500));
  // stretch arm to current position
  _domeLeftArmTaskManager->addTask(new ChangeBoolTask(&leftArmIsReady, true));
  // wait here to bring left arm in and close doors
  // check if arm is vertical
  _domeLeftArmTaskManager->addTask(new DoubleValueTask(&_leftArmExtend_target, extendClosed));
  _domeLeftArmTaskManager->addTask(new ChangeBoolTask(&leftArmIsReady, false));

  // bring arm in
  _domeLeftArmTaskManager->addTask(new MoveServoTask(_pwm_dome, pwm_head_pin_arms_left_extruder, _leftArmExtruder_max, _leftArmExtruder_min, 800, 200));
  // close door
  _domeLeftArmTaskManager->addTask(new MoveServoTask(_pwm_dome, pwm_head_pin_arms_left_door, _leftArmDoor_max, _leftArmDoor_min, 300, 200));
}

void ChopperDome::setup()
{
  setupRightArmTools();
  setupLeftArmTools();
}
void ChopperDome::loop()
{
  _domeRightArmTaskManager->loop();
  _domeLeftArmTaskManager->loop();

  rotateServoToDegree(pwm_head_pin_periscope_lift, _liftPeriscope);
  rotateServoToDegree(pwm_head_pin_periscope_rotate, _rotationPeriscope);
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

void ChopperDome::setLeftArmExtend(double extend)
{
  _leftArmExtend_target = extend;
}
void ChopperDome::setRightArmExtend(double extend)
{
  _rightArmExtend_target = extend;
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
  _pwm_dome->setPWM(servo, 0, pulselength);
}