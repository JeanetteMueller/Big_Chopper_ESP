
uint8_t eyeBrightness = 128;

uint32_t offColor = neoPixelLights->Color(0, 0, 0);

// grün, rot, blau
uint32_t frontBodyLightColor = neoPixelLights->Color(0, 255, 0);
uint32_t backBodyLightColor = neoPixelLights->Color(255, 0, 0);

// rot, grün, blau
uint32_t rightEyeColor = neoPixelLights->Color(0, 0, eyeBrightness);
uint32_t centerEyeColor = neoPixelLights->Color(0, 0, eyeBrightness);
uint32_t leftEyeColor = neoPixelLights->Color(0, 0, eyeBrightness);

// grün, rot, blau
uint32_t periscopeColor = neoPixelLights->Color(0, 255, 0);

void setupLights()
{
  neoPixelLights = new Adafruit_NeoPixel(2 + 7 + 7 + 7 + 1, neoPixelLightsPin, pixelFormat);
  neoPixelLights->setBrightness(0);
  neoPixelLights->begin();
}

enum Light
{
  bodyBack,
  bodyFront,
  rightEye,
  centerEye,
  leftEye,
  periscope
};

void updateLight(Light light, uint32_t color)
{
  uint16_t startIndex = 0;
  uint16_t length = 1;

  switch (light)
  {
  case bodyBack:
    startIndex = 0;
    length = 1;
    break;
  case bodyFront:
    startIndex = 1;
    length = 1;
    break;
  case rightEye:
    startIndex = 1 + 1;
    length = 7;
    break;
  case centerEye:
    startIndex = 1 + 1 + 7;
    length = 7;
    break;
  case leftEye:
    startIndex = 1 + 1 + 7 + 7;
    length = 7;
    break;
  case periscope:
    startIndex = 1 + 1 + 7 + 7 + 7;
    length = 1;
    break;
  }

  for (uint16_t i = startIndex; i < (startIndex + length); i++)
  {
    neoPixelLights->setPixelColor(i, color);
  }
}

void loopPeriscopeLight()
{
  if (ibusVar02 >= 1650 && ibusVar02 <= 2000)
  {
    updateLight(periscope, periscopeColor);
  }
  else
  {
    updateLight(periscope, offColor);
  }
}

void loopLights()
{
  updateLight(bodyBack, backBodyLightColor);
  updateLight(bodyFront, frontBodyLightColor);

  updateLight(rightEye, rightEyeColor);
  updateLight(centerEye, centerEyeColor);
  updateLight(leftEye, leftEyeColor);

  loopPeriscopeLight();

  neoPixelLights->setBrightness(150);
  neoPixelLights->show();
}
