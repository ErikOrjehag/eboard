#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

void setPwmFrequency(int pin, int divisor);

int msg[1];
RF24 radio(9, 10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

int PWM_PIN = 5;

void setup(void) {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
  pinMode(PWM_PIN, OUTPUT);
  setPwmFrequency(PWM_PIN, 1024); // 62500/1024 = 61 Hz
}

void loop(void) {

  digitalWrite(PWM_PIN, 0);
  
  /*if (radio.available()) {
    bool done = false;
    while (!done) {
      done = radio.read(msg, 1);
      Serial.println(msg[0]);
      if (msg[0] == 111) {
        //delay(10);
        digitalWrite(LED1, HIGH);
      }
      else {
        digitalWrite(LED1, LOW);
      }
      //delay(10);
    }
  }
  else {
    Serial.print(".");
  }*/
}





void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}


