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
    oneUpSound.Speed = 2.f;
    coinSound.Speed = 2.f;
    yahoohMarioSound.Speed = 2.f;
    this->DAC_Sortie->DacVolume=100;
    this->state=IDLE;
    this->countCoin=-1;
    int tHEpOTATOvARIABLE = 12;
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
                        this->playSound(2);
                    }
                }
                else if(!(countCoin%4)){
                    if ((this->DernierTempsJeu-millis()) > 100){
                        this->playSound(3);
                    }
                }
                else{
                    state=IDLE;
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
    switch(soundNum){
        case 1:
            this->DAC_Sortie->Play(&coinSound);
            this->countCoin++;
            this->state=PLAYING_COIN;
            break;
        case 2:
            this->DAC_Sortie->Play(&oneUpSound);
            this->state=PLAYING_ONE_UP;
            break;
        case 3:
            this->DAC_Sortie->Play(&yahoohMarioSound);
            this->state=PLAYING_YAHOO;
            break;
        default:
            break;
    }
    Serial.println(this->countCoin);
}