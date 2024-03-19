

void setupInput()
{

  IBus->begin(Serial, IBUSBM_NOTIMER);
}

void loopInput()
{

  IBus->loop();

  if (IBus->cnt_rec > 0)
  {
    ibusVar00 = IBus->readChannel(RC_STICK_RIGHT_H);    // Steer
    ibusVar01 = IBus->readChannel(RC_STICK_RIGHT_V);    // Drive
    ibusVar02 = IBus->readChannel(RC_STICK_LEFT_V);     //
    ibusVar03 = IBus->readChannel(RC_STICK_LEFT_H);     // Dome drehen
    ibusVar04 = IBus->readChannel(RC_TURN_LEFT);        // (drehregler links)
    ibusVar05 = IBus->readChannel(RC_TURN_RIGHT);       // (drehregler rechts)
    ibusVar06 = IBus->readChannel(RC_SWITCH_LEFT_OUT);  // (schalter links außen)
    ibusVar07 = IBus->readChannel(RC_SWITCH_LEFT_IN);   // (schalter links innen)
    ibusVar08 = IBus->readChannel(RC_SWITCH_RIGHT_IN);  // (schalter rechts innen)
    ibusVar09 = IBus->readChannel(RC_SWITCH_RIGHT_OUT); // (schalter rechts außen)

    driveValueHorizontal = ibusVar00;
    driveValueVertical = ibusVar01;

    headServoTarget = ibusVar02;
  }
}