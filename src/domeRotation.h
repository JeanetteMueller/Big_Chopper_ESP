void setupDomeRotation()
{
  domeRotation->stop();
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
      
      domeRotation->updateMotorWith(ibusVar03, 5);
    }
    else
    {
      domeRotation->stop();
    }
  }
}
