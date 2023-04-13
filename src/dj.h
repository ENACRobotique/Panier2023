#ifndef DJUKEBOX_H
#define DJUKEBOX_H

#include <Arduino.h>
#include <XT_DAC_Audio.h>
#include "./ressource/oneUpSoundData.h"
#include "./ressource/marioCoinSoundData.h"
//#include "./ressource/windowsXPSoundData.h"
#include "./ressource/yahooMarioSoundData.h"
typedef enum {
  IDLE,
//  PLAYING_START_SOUND,
  PLAYING_COIN,
  PLAYING_YAHOO,
  PLAYING_ONE_UP
}DJState_t;
//XT_Wav_Class startSound(windowsXP_wav);//   0
extern XT_Wav_Class coinSound;//      1
extern XT_Wav_Class oneUpSound;//    2
extern XT_Wav_Class yahoohMarioSound;// 3

class DJukeBox{
    private:
        DJState_t state;
        XT_DAC_Audio_Class* DAC_Sortie;
        int countCoin;
        long DernierTempsJeu;
    public:
        DJukeBox(XT_DAC_Audio_Class* DAC_HautParleur);
        void init(void);
        void update(void);
        void playSound(int soundNumber);
};

#endif //DJUKEBOX_H
