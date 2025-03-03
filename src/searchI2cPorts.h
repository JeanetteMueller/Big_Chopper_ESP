bool searchI2CPorts()
{
	byte error, address; // variable for error and I2C address
	int nDevices;

	Serial.println(F("Scanning..."));

	nDevices = 0;
	for (address = 1; address < 127; address++)
	{
		// The i2c_scanner uses the return value of
		// the Write.endTransmisstion to see if
		// a device did acknowledge to the address.
		Wire.beginTransmission(address);
		error = Wire.endTransmission();

		if (error == 0)
		{
			Serial.print(F("I2C device found at address 0x"));
			if (address < 16)
			{
				Serial.print(F("0"));
			}
			Serial.print(address, HEX);
			Serial.println(F("  !"));
			nDevices++;
		}
		else if (error == 4)
		{
			Serial.print(F("Unknown error at address 0x"));
			if (address < 16)
			{
				Serial.print(F("0"));
			}
			Serial.println(address, HEX);
		}
	}

	if (nDevices == 0)
	{
		Serial.println(F("No I2C devices found"));
		delay(3000);
		return false;
	}
	else
	{
		Serial.println(F("done"));
		return true;
	}

	// wait 3 seconds for the next I2C scan
}

bool searchI2CPorts2()
{

	//   while (!Serial) // Waiting for serial connection
	//     {
	//     }

	Serial.println();
	Serial.println("I2C scanner. Scanning ...");
	byte count = 0;

	Wire.begin();
	for (byte i = 8; i < 120; i++)
	{
		Wire.beginTransmission(i);
		if (Wire.endTransmission() == 0)
		{
			Serial.print("Found address: ");
			Serial.print(i, DEC);
			Serial.print(" (0x");
			Serial.print(i, HEX);
			Serial.println(")");
			count++;
			delay(1); // maybe unneeded?
		} // end of good response
	} // end of for loop
	Serial.println("Done.");

	if (count > 0)
	{
		Serial.print("Found ");
		Serial.print(count, DEC);
		Serial.println(" device(s).");
		return true;
	}
	else
	{
		Serial.println(F("No I2C devices found"));
		delay(3000); // wait 3 seconds for the next I2C scan
		return false;
	}
}