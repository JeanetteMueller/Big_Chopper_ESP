#ifndef ChopperBody_h
#define ChopperBody_h

#include "../submodules/JxTankDriver/JxTankDriver.h"
#include "../submodules/JxDomeRotation/JxDomeRotation.h"
#include "../submodules/JxTaskManager/JxTaskManager.h"

#include <Adafruit_PWMServoDriver.h>

#define pwm_body_pin_drive_left_pwm (byte)0
#define pwm_body_pin_drive_left_dir (byte)1
#define pwm_body_pin_drive_right_pwm (byte)2
#define pwm_body_pin_drive_right_dir (byte)3
#define pwm_body_pin_right_door (byte)4
#define pwm_body_pin_right_toollift (byte)5
#define pwm_body_pin_right_action (byte)6
#define pwm_body_pin_7 (byte)7
#define pwm_body_pin_left_door (byte)8
#define pwm_body_pin_left_toollift (byte)9
#define pwm_body_pin_left_action (byte)10
#define pwm_body_pin_dome_rotation_dir (byte)11
#define pwm_body_pin_dome_rotation_pwm (byte)12
#define pwm_body_pin_utilityarmgripper (byte)13
#define pwm_body_pin_utilityarm (byte)14
#define pwm_body_pin_domeShake (byte)15

class ChopperBody {
public:
  ChopperBody(Adafruit_PWMServoDriver *pwm, bool debug);

  void setup();
  void loop();

  int16_t horizontal = 0;
  int16_t vertical = 0;

  void setDomeRotation(int16_t rotation);

  bool bodyArmLeft = false;
  bool bodyArmRight = false;
  bool domeShake = false;
  bool utilityArm = false;
  bool utilityArmGripper = false;

private:
  bool _debug = false;

  Adafruit_PWMServoDriver *_pwm_body;

  JxTankDriver *_drive;

  JxDomeRotation *_domeRotation;

  JxTaskManager *_domeShakeTaskManager;

  void setupDomeShake();

  int16_t _rotation = 1500;

  // Left
  double _default_door_left = 19;
  double _max_door_left = 89;
  double _default_toollift_left = 78;
  double _max_toollift_left = 28;
  double _default_action_left = 15;
  double _max_action_left = 120;

  JxTaskManager *_bodyLeftArmTaskManager;
  void setupLeftBodyArm();

  // Right
  double _default_door_right = 123;
  double _max_door_right = 10;
  double _default_toollift_right = 11;
  double _max_toollift_right = 50;
  double _default_action_right = 57;
  double _max_action_right = 90;
  JxTaskManager *_bodyRightArmTaskManager;
  void setupRightBodyArm();

  double _default_utility_arm = 0;
  double _max_utility_arm = 100;
  JxTaskManager *_bodyUtilityArmTaskManager;
  void setupUtilityArm();

  double _default_utility_gripper = 120;
  double _max_utility_gripper = 30;
  JxTaskManager *_bodyUtilityArmGripperTaskManager;
  void setupUtilityGripper();

  // Servo Parameters
  uint16_t _SERVOMIN = 150;   // This is the 'minimum' pulse length count (out of 4096)
  uint16_t _SERVOMAX = 595;   // This is the 'maximum' pulse length count (out of 4096)
  uint16_t _SERVO_FREQ = 60;  // Analog servos run at ~50 Hz updates

  void rotateServoToDegree(uint8_t servo, double degree);
};

#endif