
double minPeriscopeRotation = 70 * 2;
double maxPeriscopeRotation = 0;

double minPeriscopeLift = 78;
double maxPeriscopeLift = 170;

void setupDomePeriscope()
{

}

void loopDomePeriscope()
{

  if (ibusVar02 >= 1500 && ibusVar02 <= 2000)
  {
    int16_t liftPeriscope = map(ibusVar02, 1500, 2000, minPeriscopeLift, maxPeriscopeLift);

    if (liftPeriscope < minPeriscopeLift)
    {
      liftPeriscope = minPeriscopeLift;
    }

    rotateServoToDegree(pwm_head, pwm_head_pin_periscope_lift, liftPeriscope);

    if (ibusVar03 >= 1000 && ibusVar03 <= 2000)
    {
      int16_t rotationPeriscope = map(ibusVar03, 1000, 2000, minPeriscopeRotation, maxPeriscopeRotation);
      rotateServoToDegree(pwm_head, pwm_head_pin_periscope_rotate, rotationPeriscope);
    }

    domeRotation->stop();
  }
  else
  {
    rotateServoToDegree(pwm_head, pwm_head_pin_periscope_lift, minPeriscopeLift);
    rotateServoToDegree(pwm_head, pwm_head_pin_periscope_rotate, 70);
  }
}
