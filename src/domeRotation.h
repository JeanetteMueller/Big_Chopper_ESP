
void loopDomeRotation()
{
  if (ibusVar02 >= 1500 && ibusVar02 <= 2000)
  {
    // signal for periscope
  }
  else
  {
    domeRotation->updateMotorWith(ibusVar03, 5);
  }
}
