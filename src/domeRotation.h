void setupDomeRotation()
{
  Motor_Dive_Dome.setSpeed(0);
}
void loopDomeRotation()
{

  // ibusVar03 = 1000;

  if (ibusVar02 >= 1500 && ibusVar02 <= 2000)
  {
    // signal for periscope
  }
  else
  {
    if (ibusVar03 >= 1000 && ibusVar03 <= 2000)
    {

      int16_t rotationSpeed = map(ibusVar03, 1000, 2000, 255, -255);

      Motor_Dive_Dome.setSpeed(rotationSpeed);
    }
    else
    {
      Motor_Dive_Dome.setSpeed(0);
    }
  }
}
