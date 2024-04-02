
int16_t domeRotateSpeed = 1500;

void loopDomeRotation()
{
    bool doIt = false;
    if (ibusVar02 >= 1500 && ibusVar02 <= 2000)
    {
        // signal for periscope
        if (domeRotateSpeed != 1500)
        {
            domeRotateSpeed = 1500;
            doIt = true;
        }
    }
    else
    {
        if (ibusVar03 != 0)
        {
            if (domeRotateSpeed != ibusVar03)
            {
                domeRotateSpeed = ibusVar03;
                doIt = true;
            }
        }
        else
        {
            if (domeRotateSpeed != webServer->domeRotate)
            {
                domeRotateSpeed = webServer->domeRotate;
                doIt = true;
            }
        }
    }
    if (doIt == true)
    {
        if (debug)
        {
            Serial.print("domeRotateSpeed: ");
            Serial.println(domeRotateSpeed);
        }

        domeRotation->updateMotorWith(domeRotateSpeed, 25);
    }
}
