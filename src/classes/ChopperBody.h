#ifndef ChopperBody_h
#define ChopperBody_h

#include "../submodules/JxTankDriver/JxTankDriver.h"
#include "../submodules/JxDomeRotation/JxDomeRotation.h"
#include "../submodules/JxTaskManager/JxTaskManager.h"

#include <Adafruit_PWMServoDriver.h>

#define pwm_body_pin_dome_rotation_dir (byte)0
#define pwm_body_pin_dome_rotation_pwm (byte)1
#define pwm_body_pin_2 (byte)2
#define pwm_body_pin_3 (byte)3
#define pwm_body_pin_right_door (byte)4
#define pwm_body_pin_right_toollift (byte)5
#define pwm_body_pin_right_action (byte)6
#define pwm_body_pin_7 (byte)7
#define pwm_body_pin_left_door (byte)8
#define pwm_body_pin_left_toollift (byte)9
#define pwm_body_pin_left_action (byte)10
#define pwm_body_pin_11 (byte)11
#define pwm_body_pin_12 (byte)12
#define pwm_body_pin_utilityarmgripper (byte)13
#define pwm_body_pin_utilityarm (byte)14
#define pwm_body_pin_domeShake (byte)15

class ChopperBody
{
public:
    ChopperBody(bool debug);
    
    void setup();
    void loop();

    void setDomeRotation(int16_t rotation);

    bool bodyArmLeft = false;
    bool bodyArmRight = false;
    bool domeShake = false;
    bool utilityArm = false;
    bool utilityArmGripper = false;

private:
    bool _debug = false;

    Adafruit_PWMServoDriver pwm_body = Adafruit_PWMServoDriver(0x40);
    
    JxDomeRotation *domeRotation = new JxDomeRotation(1000, 2000, 1500);

    JxTaskManager domeShakeTaskManager = JxTaskManager();
    void setupDomeShake();

    int16_t _rotation = 0;
    int16_t _domeRotateSpeed = 1500;

    // Left
    double default_door_left = 15;
    double max_door_left = 82;
    double default_toollift_left = 70;
    double max_toollift_left = 20;
    double default_action_left = 10;
    double max_action_left = 120;

    JxTaskManager bodyLeftArmTaskManager = JxTaskManager();
    void setupLeftBodyArm();

    // Right
    double default_door_right = 120;
    double max_door_right = 15;
    double default_toollift_right = 10;
    double max_toollift_right = 50;
    double default_action_right = 67;
    double max_action_right = 140;
    JxTaskManager bodyRightArmTaskManager = JxTaskManager();
    void setupRightBodyArm();

    double default_utility_arm = 0;
    double max_utility_arm = 100;
    JxTaskManager bodyUtilityArmTaskManager = JxTaskManager();
    void setupUtilityArm();

    double default_utility_gripper = 120;
    double max_utility_gripper = 65;
    JxTaskManager bodyUtilityArmGripperTaskManager = JxTaskManager();
    void setupUtilityGripper();

    // Servo Parameters
    uint16_t _SERVOMIN = 150;  // This is the 'minimum' pulse length count (out of 4096)
    uint16_t _SERVOMAX = 595;  // This is the 'maximum' pulse length count (out of 4096)
    uint16_t _SERVO_FREQ = 60; // Analog servos run at ~50 Hz updates

    void rotateServoToDegree(uint8_t servo, double degree);
};

#endif