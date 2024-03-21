
void setupAudio()
{
	mySerial.begin(9600);

	Serial.println(F("Initializing DFPlayer ... "));

	previousMillisAudio = currentMillis + 5000;
	player.begin(mySerial, false);

	delay(1000);

	// if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
	//	Serial.println(F("Please remove and insert the SD card again!"));
	// }
	Serial.println(F("DFPlayer Mini online."));
}

void loopAudio()
{
	// Serial.println(F("loopAudio start"));

	if (currentMillis < previousMillisAudio)
	{
		previousMillisAudio = 0;
	}

	if (ibusVar05 >= 1000 && ibusVar05 <= 2000)
	{
		uint16_t newVolume = map(ibusVar05, 1000, 2000, 30, 15);
		player.volume(newVolume);
	}
	else
	{
		//----Set volume----
		player.volume(8); // Set volume value (0~30).
	}

	if (player.isPlaying())
	{
		Serial.println(F("player is playing"));
		domeShake->shakeStart();

		previousMillisAudio = currentMillis;
	}
	else
	{
		domeShake->shakeStop();
	}

	if (ibusVar06 > 1750 || ibusVar06 == 0)
	{
		if (currentMillis - previousMillisAudio >= audioPause || directStart)
		{
			Serial.println(F("currentMillis right || directStart"));
			// player.printError();

			if (!player.isPlaying())
			{
				Serial.println(F("player is NOT playing"));

				directStart = false;
				previousMillisAudio = currentMillis;

				if (audioItemCount == 0)
				{
					int count = player.numSdTracks();
					if (count > 0)
					{
						audioItemCount = count;
					}
				}

				if (audioItemCount > 0)
				{
					uint16_t randomItemNumber = random(1, audioItemCount + 1);

					Serial.print(F("Play item Number "));
					Serial.print(randomItemNumber);
					Serial.print(F(" of "));
					Serial.print(audioItemCount);
					Serial.println(F(" Items "));

					player.play(randomItemNumber);

					audioPause = 2000 + (random(10, 50) * 100);

					domeShake->shakeStart();
				}
			}
		}
	}
	else if (directStart != true)
	{
		directStart = true;
	}
}
