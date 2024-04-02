int16_t driveValueHorizontal = 1500;
int16_t driveValueVertical = 1500;

void loopDrive()
{
    bool doIt = false;

    if (ibusVar00 != 0 && ibusVar01 != 0)
    {
        if (driveValueHorizontal != ibusVar00)
        {
            driveValueHorizontal = ibusVar00;
            doIt = true;
        }
        if (driveValueVertical != ibusVar01)
        {
            driveValueVertical = ibusVar01;
            doIt = true;
        }
    }
    else
    {
        int16_t newX = map(webServer->joy1_x, -100, 100, 1000, 2000);
        if (driveValueHorizontal != newX)
        {
            driveValueHorizontal = newX;
            doIt = true;
        }
        int16_t newY = map(webServer->joy1_y, -100, 100, 1000, 2000);
        if (driveValueVertical != newY)
        {
            driveValueVertical = newY;
            doIt = true;
        }
    }

    if (doIt == true)
    {
        if (debug)
        {
            Serial.print("updateMotorsWith: ");
            Serial.print(driveValueHorizontal);
            Serial.print(" - ");
            Serial.println(driveValueVertical);
        }

        drive->updateMotorsWith(driveValueHorizontal, driveValueVertical, 5, 150);
    }
}