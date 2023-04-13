#ifndef DIGIPOS_H
#define DIGIPOS_H

#include <Arduino.h>
#include <HardwareSerial.h>


#define RX_pin 16
#define TX_pin 17



class WD202A {
        private:
        unsigned int posX;
        unsigned int posY;
        unsigned int nbCerise;
        HardwareSerial *serial;
        
        public:

        void init(HardwareSerial* ser, int pin_rx, int pin_tx){
            serial = ser;
            serial->begin (9600, SERIAL_8N1, pin_rx, pin_tx);
            
        }
        void clearDisplay(){
            this->serial->write(0x0C);
        }
        
        void moveLine(uint8_t column, uint8_t line){
            uint8_t buf[4]={0x1F,0x24,column,line};

            if( ((column>1)||(column < 20)) && ((line>=1)||(line<=2)) ){
                this->serial->write(buf,4);
            }
            
        }
        void displayOverwrite(){
            this->serial->write(0x1F01);
            this->serial->write(0x1F03); 
        }

        void write(char* buf, size_t len) {
            serial->write(buf, len);
        }
};

//SW setup 1-OFF 2-ON 3-ON 4-OFF 5-ON 6-ON 7-ON 8-OFF 9-ON 10-ON 11-ON 12-ON 

//Baudrate 9600
//Bit de parité impaire ; 8 bits DATA
//Character set FRANCE -- Code table PC-858(Euro)
//Self-test & demo function selection -> Enable

//TRAME (BITS) 1 START -- 8 DATA(odd) -- 1 STOP

// ESC/pos STD COMMAND LIST

//0x08 Move cursor left
//0x09 Move cursor right
//0x0A Move cursor down
//0x1F0A Move cursor up
//0x0B Move cursor to home position
//0x1F24 x y Set position ---- 1 ≦x≦ 20 ,row position // 1 ≦y≦ 2 ,column position
//0x0C clear display
//0X1B40 Initialize display

#endif //DIGIPOS_H