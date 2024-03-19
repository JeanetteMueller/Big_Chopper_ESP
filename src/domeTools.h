
// Doors
double leftArmDoor_min = 170;
double leftArmDoor_max = 0;
double rightArmDoor_min = 0;
double rightArmDoor_max = 170;

// Extruder
double leftArmExtruder_min = 180;
double leftArmExtruder_max = 50;
double rightArmExtruder_min = 35-5;
double rightArmExtruder_max = 165-5;

// Rotate
double rightArmRotate_min = 90;
double rightArmRotate_max = 0;
double rightArmRotate_doorsafe = 73;
double leftArmRotate_min = 12;
double leftArmRotate_max = 90;
double leftArmRotate_doorsafe = 32;

double current_rotateRightArm = 90;
double current_rotateLeftArm = 0;

//Extend
double leftArmExtend_min = 0;
double leftArmExtend_max = 160;
double rightArmExtend_min = 160;
double rightArmExtend_max = 0;

double current_extendRightArm = 160;
double current_extendLeftArm = 0;


void setupRightArmTools()
{
  rotateServoToDegree(pwm_head, pwm_head_pin_arms_right_door, rightArmDoor_min);
  rotateServoToDegree(pwm_head, pwm_head_pin_arms_right_rotate, rightArmRotate_doorsafe);
  rotateServoToDegree(pwm_head, pwm_head_pin_arms_right_extruder, rightArmExtruder_min);
  rotateServoToDegree(pwm_head, pwm_head_pin_arms_right_extend, rightArmExtend_min);

  // check if swith is active
  domeRightArmTaskManager.addTask(new InputTask(IBus, RC_TURN_RIGHT, 1010, 2010));
  // open door
  domeRightArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_right_door, rightArmDoor_min, rightArmDoor_max, 300, 100));
  // rotate arm to hole
  domeRightArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_right_rotate, rightArmRotate_doorsafe, rightArmRotate_min, 300, 200));
  // bring arm out
  domeRightArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_right_extruder, rightArmExtruder_min, rightArmExtruder_max, 800, 500));
  // stretch arm to max
  domeRightArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_right_extend, rightArmExtend_min, current_extendRightArm, 400)); // 110

  // wait here to bring right arm in and close doors
  // check if arm is vertical
  domeRightArmTaskManager.addTask(new InputTask(IBus, RC_TURN_RIGHT, 1000));
  // stretch arm to min
  domeRightArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_right_extend, current_extendRightArm, rightArmExtend_min, 500));
  // rotate arm to center
  domeRightArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_right_rotate, current_rotateRightArm, rightArmRotate_min , 500));
  // bring arm in
  domeRightArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_right_extruder, rightArmExtruder_max, rightArmExtruder_min, 800, 200));
  // rotate arm away from hole
  domeRightArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_right_rotate, rightArmRotate_min, rightArmRotate_doorsafe, 300, 200));
  // close door
  domeRightArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_right_door, rightArmDoor_max, rightArmDoor_min, 300, 200));
}

void setupLeftArmTools()
{
  rotateServoToDegree(pwm_head, pwm_head_pin_arms_left_door, leftArmDoor_min);
  rotateServoToDegree(pwm_head, pwm_head_pin_arms_left_rotate, leftArmRotate_doorsafe);
  rotateServoToDegree(pwm_head, pwm_head_pin_arms_left_extruder, leftArmExtruder_min);
  rotateServoToDegree(pwm_head, pwm_head_pin_arms_left_extend, leftArmExtend_min);

  // check if swith is active
  domeLeftArmTaskManager.addTask(new InputTask(IBus, RC_TURN_LEFT, 1010, 2010));
  // open door
  domeLeftArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_left_door, leftArmDoor_min, leftArmDoor_max, 300, 100));
  // rotate arm to hole
  domeLeftArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_left_rotate, leftArmRotate_doorsafe, leftArmRotate_min, 300, 200));
  // bring arm out
  domeLeftArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_left_extruder, leftArmExtruder_min, leftArmExtruder_max, 800, 500));
  // stretch arm to max
  domeLeftArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_left_extend, leftArmExtend_min, current_extendLeftArm, 400)); // 110

  // wait here to bring left arm in and close doors
  // check if arm is vertical
  domeLeftArmTaskManager.addTask(new InputTask(IBus, RC_TURN_LEFT, 1000));
  // stretch arm to min
  domeLeftArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_left_extend, current_extendLeftArm, leftArmExtend_min, 500));
  // rotate arm to center
  domeLeftArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_left_rotate, current_rotateLeftArm, leftArmRotate_min, 500));
  // bring arm in
  domeLeftArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_left_extruder, leftArmExtruder_max, leftArmExtruder_min, 800, 200));
  // rotate arm away from hole
  domeLeftArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_left_rotate, leftArmRotate_min, leftArmRotate_doorsafe, 300, 200));
  // close door
  domeLeftArmTaskManager.addTask(new MoveServoTask(pwm_head, pwm_head_pin_arms_left_door, leftArmDoor_max, leftArmDoor_min, 300, 200));
}
void setupDomeTools()
{
  setupRightArmTools();
  setupLeftArmTools();
}
void loopDomeArms()
{
  if (ibusVar05 >= 1200 && ibusVar05 <= 2000)
  {
    current_extendRightArm = map(ibusVar05, 1200, 2005, rightArmExtend_min, rightArmExtend_max);
    rotateServoToDegree(pwm_head, pwm_head_pin_arms_right_extend, current_extendRightArm);
  }

  if (ibusVar04 >= 1200 && ibusVar04 <= 2000)
  {
    current_extendLeftArm = map(ibusVar04, 1200, 2005, leftArmExtend_min, leftArmExtend_max);
    rotateServoToDegree(pwm_head, pwm_head_pin_arms_left_extend, current_extendLeftArm);
  }


  // if (ibusVar09 >= 1500 && ibusVar09 <= 2000)
  // {
  //   int16_t rotateRightArm = map(ibusVar05, 1000, 2000, 20, 95);
  //   rotateServoToDegree(pwm_head, pwm_head_pin_arms_right_rotate, rotateRightArm);
  // }

  // if (ibusVar06 >= 1500 && ibusVar06 <= 2000)
  // {
  //   int16_t rotateLeftArm = map(ibusVar04, 1000, 2000, 80, 5);
  //   rotateServoToDegree(pwm_head, pwm_head_pin_arms_left_rotate, rotateLeftArm);
  // }
}