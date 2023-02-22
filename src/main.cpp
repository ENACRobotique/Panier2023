#include <Arduino.h>
#include "../ressource/SoundData.h"
#include <XT_DAC_Audio.h>
XT_DAC_Audio_Class DacAudio (25,0);
XT_Wav_Class Sound(sample);
void setup() {
  // put your setup code here, to run once:
  
  Sound.Speed = 2;
  DacAudio.DacVolume=100 ;
  DacAudio.FillBuffer();
  if (!Sound.Playing){
    DacAudio.Play(&Sound);
  }
  
}

void loop() {
  DacAudio.FillBuffer();
}