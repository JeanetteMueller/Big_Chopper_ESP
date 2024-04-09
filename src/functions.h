
void rotateServoToDegree(Adafruit_PWMServoDriver pwm, uint8_t servo, double degree)
{
	uint16_t servoMin = 150;
	uint16_t servoMax = 595;
	uint16_t pulselength = map(degree, 0, 180, servoMin, servoMax); //  Calibrate the positive range (see below)
	/*
	Serial.print(F("rotateServoToDegree Servo: "));
	Serial.print(servo);
	Serial.print(F(" to Degree: "));
	Serial.print(degree);
	Serial.print(F(" with Pulselength: "));
	Serial.println(pulselength);
	*/
	pwm.setPWM(servo, 0, pulselength);
}

void lightOn(Adafruit_PWMServoDriver pwm, uint8_t pinNumer)
{
	pwm.setPWM(pinNumer, 4096, 0);
}
void lightOff(Adafruit_PWMServoDriver pwm, uint8_t pinNumer)
{
	pwm.setPWM(pinNumer, 0, 4096);
}

void randomRotateServo(Adafruit_PWMServoDriver pwm, uint8_t servo, uint16_t minValue, uint16_t maxValue)
{
	uint16_t randomDegree = random(minValue, maxValue);

	rotateServoToDegree(pwm, servo, randomDegree);
}
