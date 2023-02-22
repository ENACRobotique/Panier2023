#include <Arduino.h>
#include "../ressource/oneUpSoundData.h"
#include "../ressource/marioCoinSoundData.h"
#include <XT_DAC_Audio.h>

typedef enum {
  IDLE,
  PLAYING_COIN,
  PLAYING_ONE_UP
}soundPlayerState_t;

XT_DAC_Audio_Class DacAudio (25,0);
XT_Wav_Class coinSound(marioCoin_wav);
XT_Wav_Class oneUpSound(oneUpMario_wav);
int cherryNumber=0;
soundPlayerState_t state=IDLE;

void setup() {
  // put your setup code here, to run once:
  
  oneUpSound.Speed = 2;
  coinSound.Speed = 2;
  DacAudio.DacVolume=100 ;
}

void gainCherry(void){
  cherryNumber++;
  state=PLAYING_COIN;
  DacAudio.Play(&coinSound);
}

void loop() {
  DacAudio.FillBuffer();
  switch(state){
    case IDLE:
      delay(500);
      gainCherry();//Code temporaire (à dégager quand on aura un compteur qui marche)
      break;
    case PLAYING_COIN:
      if(!coinSound.Playing){
        if (! (cherryNumber%10)){
          delay(100);
          state=PLAYING_ONE_UP;
          DacAudio.Play(&oneUpSound);
        }
        else{
          state=IDLE;
        }
      }
      break;
    case PLAYING_ONE_UP:
      if (!oneUpSound.Playing){
        state=IDLE;
      }
      break;
  }
}