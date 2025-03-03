#include "Chopper.h"

ChopperAudio::ChopperAudio(DY::PlayerEsp32SoftwareSerial *player, bool debug)
{
  _debug = debug;

  _player = player;
}

void ChopperAudio::setup()
{
  _player->setVolume(30);

  _soundFilesCount = _player->getSoundCount();
}

void ChopperAudio::loop()
{
  _currentMillis = millis();

  if (_previousAudioMillis + _wait < _currentMillis)
  {

    _previousAudioMillis = _currentMillis;
    _wait = (random(3, 10 + 1) * 1000);

    _playerState = _player->checkPlayState();

    if (_playerState != DY::PlayState::Playing)
    {

      if (_debug)
      {
        Serial.print("Player state: ");
        switch (_playerState)
        {
        case DY::PlayState::Fail:
          Serial.print("Fail");
          return;
          break;
        case DY::PlayState::Stopped:
          Serial.print("Stopped");
          break;
        case DY::PlayState::Playing:
          Serial.print("Playing ");
          Serial.print(_currentPlayingNumber);
          break;
        case DY::PlayState::Paused:
          Serial.print("Paused");
          break;
        }
        Serial.print(" ");
      }

      uint16_t randomSoundFileNumber = _currentPlayingNumber;
      while (randomSoundFileNumber == _currentPlayingNumber)
      {
        randomSoundFileNumber = random(1, _soundFilesCount + 1);
      }

      _currentPlayingNumber = randomSoundFileNumber;

      if (_debug)
      {
        Serial.print("SoundFilesCount: ");
        Serial.print(_soundFilesCount);

        Serial.print(" - Start audio file number ");
        Serial.print(randomSoundFileNumber);
      }

      _player->playSpecified(randomSoundFileNumber);
    }
    if (_debug)
    {
      Serial.println("");
    }
  }
}