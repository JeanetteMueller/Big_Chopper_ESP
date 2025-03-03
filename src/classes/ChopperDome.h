#ifndef ChopperDome_h
#define ChopperDome_h

#include "../submodules/JxTaskManager/JxTaskManager.h"
#include <Adafruit_PWMServoDriver.h>

#define pwm_head_pin_periscope_rotate (byte)0
#define pwm_head_pin_periscope_lift (byte)1
#define pwm_head_pin_2 (byte)2
#define pwm_head_pin_3 (byte)3
#define pwm_head_pin_arms_left_door (byte)4
#define pwm_head_pin_arms_left_extruder (byte)5
#define pwm_head_pin_arms_left_rotate (byte)6
#define pwm_head_pin_arms_left_extend (byte)7
#define pwm_head_pin_arms_right_door (byte)8
#define pwm_head_pin_arms_right_extruder (byte)9
#define pwm_head_pin_arms_right_rotate (byte)10
#define pwm_head_pin_arms_right_extend (byte)11
#define pwm_head_pin_12 (byte)12
#define pwm_head_pin_13 (byte)13
#define pwm_head_pin_14 (byte)14
#define pwm_head_pin_15 (byte)15

class ChopperDome
{
public:
    ChopperDome(Adafruit_PWMServoDriver *pwm, bool debug);
    
    void setup();
    void loop();

    void setPeriscopeLift(uint8_t liftValue);
    void setPeriscopeRotation(int8_t rotationValue);

    bool rightArmIsReady = false;
    bool leftArmIsReady = false;

    double current_rotateRightArm = 90;
    double current_rotateLeftArm = 0;
    double current_extendRightArm = 160;
    double current_extendLeftArm = 0;

    void setLeftArmExtend(double extend);
    void setRightArmExtend(double extend);

private:
    bool _debug = false;
    Adafruit_PWMServoDriver *_pwm_dome;

    double _minPeriscopeLift = 80;
    double _maxPeriscopeLift = 165;
    double _minPeriscopeRotation = 160;
    double _maxPeriscopeRotation = 0;

    int16_t _liftPeriscope = 0;
    int16_t _rotationPeriscope = 0;

    // Doors
    double _leftArmDoor_min = 170;
    double _leftArmDoor_max = 0;
    double _rightArmDoor_min = 0;
    double _rightArmDoor_max = 170;

    // Extruder
    double _leftArmExtruder_min = 180;
    double _leftArmExtruder_max = 50;
    double _rightArmExtruder_min = 35 - 5;
    double _rightArmExtruder_max = 165 - 5;

    // Extend
    double _leftArmExtend_target = 0;
    double _rightArmExtend_target = 160;

    JxTaskManager *_domeRightArmTaskManager;
    JxTaskManager *_domeLeftArmTaskManager;

    void setupRightArmTools();
    void setupLeftArmTools();


    // Servo Parameters
    uint16_t _SERVOMIN = 150;  // This is the 'minimum' pulse length count (out of 4096)
    uint16_t _SERVOMAX = 595;  // This is the 'maximum' pulse length count (out of 4096)
    uint16_t _SERVO_FREQ = 60; // Analog servos run at ~50 Hz updates

    void rotateServoToDegree(uint8_t servo, double degree);
};

#endif