#ifndef ChopperAudio_h
#define ChopperAudio_h

#include "DYPlayerEsp32SoftwareSerial.h"

class ChopperAudio
{
public:
    ChopperAudio(DY::PlayerEsp32SoftwareSerial *player, bool debug);

    void setup();
    void loop();

private:
    bool _debug = false;

    // TIME
    unsigned long _currentMillis; // time current
    unsigned long _previousMillis_100 = 0;

    // AUDIO
    DY::PlayerEsp32SoftwareSerial *_player;
    unsigned long _previousAudioMillis = 0;
    uint16_t _currentPlayingNumber = 0;
    DY::PlayState _playerState;
    uint16_t _soundFilesCount = 0;
    uint16_t _wait = 100;
};

#endif