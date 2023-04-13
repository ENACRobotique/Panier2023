#include "dj.h"
#include <XT_DAC_Audio.h>
#include "./ressource/oneUpSoundData.h"
#include "./ressource/marioCoinSoundData.h"
//#include "/ressource/windowsXPSoundData.h"
#include "./ressource/yahooMarioSoundData.h"
XT_Wav_Class coinSound(marioCoin_wav);
XT_Wav_Class oneUpSound(oneUpMario_wav);
XT_Wav_Class yahoohMarioSound(yahooMario_wav);
DJukeBox::DJukeBox(XT_DAC_Audio_Class* DAC_HautParleur){
    this->DAC_Sortie = DAC_HautParleur;
}
void DJukeBox::init(void){
    oneUpSound.Speed = 2;
    coinSound.Speed = 2;
    this->DAC_Sortie->DacVolume=50;
    this->state=IDLE;
    this->countCoin=0;
}
void DJukeBox::update(void){
    this->DAC_Sortie->FillBuffer();
    switch (this->state){
        case IDLE:
            break;
        case PLAYING_COIN:
            if (!coinSound.Playing){
                if (!(countCoin%10)){//si nombre de cerises divisible par 10
                    if ((this->DernierTempsJeu-millis()) > 100){
                        this->state=PLAYING_ONE_UP;
                        this->playSound(2);
                    }
                }
                else if(!(random(1025))%5){
                    if ((this->DernierTempsJeu-millis()) > 100){
                        this->state=PLAYING_YAHOO;
                        this->playSound(3);
                    }
                }
                
            }
            else{
                this->DernierTempsJeu = millis();
                }
            break;
        case PLAYING_YAHOO:
            if (!yahoohMarioSound.Playing){
                state=IDLE;
            }
            break;
        case PLAYING_ONE_UP:
            if (!oneUpSound.Playing){
                state=IDLE;
            }
            break;
    }
    
}

void DJukeBox::playSound(int soundNum){
    soundNum %=4;
    switch(soundNum){
        case 1:
            this->DAC_Sortie->Play(&coinSound);
            break;
        case 2:
            this->DAC_Sortie->Play(&oneUpSound);
            break;
        case 3:
            this->DAC_Sortie->Play(&yahoohMarioSound);
            break;
        default:
            break;
    }
}