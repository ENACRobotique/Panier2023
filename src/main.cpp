#include <Arduino.h>
#include <XT_DAC_Audio.h>
#include <iostream>
#include <string>
#include "dj.h"
#include "digipos.h"

#define SOUND_PIN 25
#define COUNT_BUTTON 39

char test[] = "test0";
int buttonPressed =0;
uint32_t lastPressedTimeStamp =0;
XT_DAC_Audio_Class dacAudio(SOUND_PIN,0);
DJukeBox soundPlayer(&dacAudio);
WD202A display;
char buffer[14];
int cherryNumber=-1;

void gainCherry(void){
  cherryNumber++;

  soundPlayer.playSound(1);
  sprintf(buffer,"Cerises : %d",cherryNumber);
  display.clearDisplay();

  display.moveLine(0,1);
  display.write(buffer, ((cherryNumber >=10) ? 12 : 11));
}
void setup() {
  pinMode(25,OUTPUT);
  soundPlayer.init();
  display.init(&Serial2, RX_pin, TX_pin);
  display.clearDisplay();
  pinMode(COUNT_BUTTON,INPUT);
  delay(100);
  gainCherry();
  // put your setup code here, to run once:

}


void loop() {
  soundPlayer.update();
  if (!digitalRead(COUNT_BUTTON)){
    lastPressedTimeStamp = millis();
    buttonPressed = 1;
  }
  else if(buttonPressed && (millis() - lastPressedTimeStamp)>5){
    buttonPressed=0;
    gainCherry();
  }
  
}

