
// TIME
unsigned long currentMillis; // time current
unsigned long previousMillis_005 = 0;
unsigned long previousMillis_020 = 0;
unsigned long previousMillis_100 = 0;
unsigned long previousMillis_200 = 0;

// RC values coming from the iBUS RC-Reciever
IBusBM *IBus = new IBusBM();
uint16_t ibusVar00 = 0;
uint16_t ibusVar01 = 0;
uint16_t ibusVar02 = 0;
uint16_t ibusVar03 = 0;
uint16_t ibusVar04 = 0;
uint16_t ibusVar05 = 0;
uint16_t ibusVar06 = 0;
uint16_t ibusVar07 = 0;
uint16_t ibusVar08 = 0;
uint16_t ibusVar09 = 0;

#define RC_STICK_RIGHT_H (byte)0
#define RC_STICK_RIGHT_V (byte)1
#define RC_STICK_LEFT_V (byte)2
#define RC_STICK_LEFT_H (byte)3
#define RC_TURN_LEFT (byte)4
#define RC_TURN_RIGHT (byte)5
#define RC_SWITCH_LEFT_OUT (byte)6
#define RC_SWITCH_LEFT_IN (byte)7
#define RC_SWITCH_RIGHT_IN (byte)8
#define RC_SWITCH_RIGHT_OUT (byte)9

// Task Managers
TaskManager domeRightArmTaskManager = TaskManager();
TaskManager domeLeftArmTaskManager = TaskManager();
TaskManager domeShakeTaskManager = TaskManager();
TaskManager bodyLeftArmTaskManager = TaskManager();
TaskManager bodyRightArmTaskManager = TaskManager();
TaskManager bodyUtilityArmTaskManager = TaskManager();
TaskManager bodyUtilityArmGripperTaskManager = TaskManager();

// Servo Parameters
#define SERVOMIN 150  // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 595  // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 60 // Analog servos run at ~50 Hz updates

// Servo Shield in Body
Adafruit_PWMServoDriver pwm_body = Adafruit_PWMServoDriver(0x40);
#define pwm_body_pin_0 (byte)0
#define pwm_body_pin_1 (byte)1
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

// Servo Shield in Dome
Adafruit_PWMServoDriver pwm_head = Adafruit_PWMServoDriver(0x60);
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

// Motors
CytronMD Motor_Dive_Right(PWM_DIR, 13, 15);
CytronMD Motor_Dive_Left(PWM_DIR, 14, 12);
CytronMD Motor_Dive_Dome(PWM_DIR, 0, 2);

int16_t leftMotorSpeedTarget = 0;
int16_t rightMotorSpeedTarget = 0;
uint16_t driveValueHorizontal = 1500;
uint16_t driveValueVertical = 1500;
int16_t joystickX = 0;
int16_t joystickY = 0;
int16_t leftMotorSpeed = 0;
int16_t rightMotorSpeed = 0;

// Dome Rotation
#define deadzoneDomeXY 50 // original value is 20, this will give the motors enough power to move, add eliminate centering jitter
bool shakeHead = false;
const byte shakeCenter = 22; // 32 //26
const byte shakeDistance = 3;
byte shakeHeadPosition = 1;
byte redBarPosition = 0;
bool redBarFull = false;
int16_t headServoTarget = 1500;

// Lights
Adafruit_NeoPixel *neoPixelLights;
neoPixelType pixelFormat = NEO_GRB + NEO_KHZ800;
#define neoPixelLightsPin (byte)1

// Audio
// SoftwareSerial mySerial(6,5); // RX, TX
// DFPlayerMini_Fast player;
// bool directStart = true;
// uint16_t audioPause = 2000;
// uint16_t audioItemCount = 0;
