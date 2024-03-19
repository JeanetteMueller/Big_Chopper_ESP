
void setupDomeShake()
{
  uint16_t centerPosition = 57;
  uint16_t shakeRange = 30;

  domeShakeTaskManager.addTask(new InputTask(IBus, RC_SWITCH_LEFT_IN, 2000, -1));

  domeShakeTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_domeShake, centerPosition, centerPosition + shakeRange, 200));

  domeShakeTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_domeShake, centerPosition + shakeRange, centerPosition - shakeRange, 400));

  domeShakeTaskManager.addTask(new MoveServoTask(pwm_body, pwm_body_pin_domeShake, centerPosition - shakeRange, centerPosition, 200));
}