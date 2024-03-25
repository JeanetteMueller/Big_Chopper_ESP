
void setupLeftBodyArm()
{
  // Left
  double default_door_left = 15;
  double max_door_left = 82;
  double default_toollift_left = 70;
  double max_toollift_left = 20;
  double default_action_left = 10;
  double max_action_left = 120;

  bodyLeftArmTaskManager.addTask(new InputTask(IBus, RC_SWITCH_LEFT_OUT, 2000, -1));
  // Door Open
  bodyLeftArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_left_door, default_door_left, max_door_left, 200, 200));
  // Bring Tool out
  bodyLeftArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_left_toollift, default_toollift_left, max_toollift_left, 800));
  // Use Tool
  bodyLeftArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_left_action, default_action_left, max_action_left, 200, 400));
  bodyLeftArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_left_action, max_action_left, default_action_left, 200, 400));
  bodyLeftArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_left_action, default_action_left, max_action_left, 200, 400));

  // react on Switch to Bring all in
  bodyLeftArmTaskManager.addTask(new InputTask(IBus, RC_SWITCH_LEFT_OUT, 1000));
  // move tool to retracted position
  bodyLeftArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_left_action, max_action_left, default_action_left, 200, 400));
  // Bring Tool in
  bodyLeftArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_left_toollift, max_toollift_left, default_toollift_left, 300, 500));
  // Door close
  bodyLeftArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_left_door, max_door_left, default_door_left, 200, 200));
}

void setupRightBodyArm()
{
  // Right
  double default_door_right = 120;
  double max_door_right = 15;
  double default_toollift_right = 10;
  double max_toollift_right = 50;
  double default_action_right = 67;
  double max_action_right = 140;

  // check if swith is active
  bodyRightArmTaskManager.addTask(new InputTask(IBus, RC_SWITCH_RIGHT_OUT, 2000));
  // open door
  bodyRightArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_right_door, default_door_right, max_door_right, 200, 200));
  // bring tool out
  bodyRightArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_right_toollift, default_toollift_right, max_toollift_right, 300, 600));
  // Use tool, rotate Saw
  bodyRightArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_right_action, default_action_right, max_action_right, 200, 200));

  // react on switch to bring all in
  bodyRightArmTaskManager.addTask(new InputTask(IBus, RC_SWITCH_RIGHT_OUT, 1000));
  // stop saw
  bodyRightArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_right_action, max_action_right, default_action_right, 200, 0));
  // bring tool in
  bodyRightArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_right_toollift, max_toollift_right, default_toollift_right, 300, 500));
  // close door
  bodyRightArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_right_door, max_door_right, default_door_right, 200, 200));
}

double default_utility_gripper = 120;
double max_utility_gripper = 65;

void setupUtilityArm()
{
  double default_utility_arm = 0;
  double max_utility_arm = 100;

  bodyUtilityArmTaskManager.addTask(new InputTask(IBus, RC_SWITCH_RIGHT_IN, 1500, 2000));
  // bring arm out
  bodyUtilityArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_utilityarm, default_utility_arm, max_utility_arm, 800));

  bodyUtilityArmTaskManager.addTask(new InputTask(IBus, RC_SWITCH_RIGHT_IN, 1000));
  // close gripper
  bodyUtilityArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_utilityarmgripper, default_utility_gripper, default_utility_gripper, 0, 50));
  // bring arm in
  bodyUtilityArmTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_utilityarm, max_utility_arm, default_utility_arm, 700));
}

void setupUtilityGripper()
{
  bodyUtilityArmGripperTaskManager.addTask(new InputTask(IBus, RC_SWITCH_RIGHT_IN, 2000));
  // open Gripper
  bodyUtilityArmGripperTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_utilityarmgripper, default_utility_gripper, max_utility_gripper, 300, 200));

  bodyUtilityArmGripperTaskManager.addTask(new InputTask(IBus, RC_SWITCH_RIGHT_IN, 1500));
  // close Gripper
  bodyUtilityArmGripperTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_utilityarmgripper, max_utility_gripper, default_utility_gripper, 300, 200));
}

void setupBodyTools()
{
  setupLeftBodyArm();
  setupRightBodyArm();
  setupUtilityArm();
  setupUtilityGripper();
}
