#include "MIDIUSB.h"
#include <FastLED.h>
#define LED_TYPE WS2812B
#define NUM_LEDS    19
#define LED_BLINKER 11
#define LED_PIN     9
#define MIDI_CHAN   1

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif


struct CRGB leds[NUM_LEDS]; 

int ledState = LOW;
bool ledChange = false;

uint8_t hue = 200;
uint8_t sat = 255;
uint8_t bri = 30;
uint8_t hueOld = 200;
uint8_t satOld = 255;
uint8_t briOld = 30;
unsigned long lastBlinkTime = {0};
unsigned long lastUpdateTime = {0};

//light up led at pin 13 when receiving noteON message with note = 60

void setup(){
  delay(600);
  Serial.begin(38400); //Serial.begin(115200); //Serial.begin(9600); 
  pinMode(LED_BLINKER,OUTPUT);
  FastLED.addLeds<LED_TYPE, LED_PIN, GRB>(leds, NUM_LEDS);
  delay(200);
}   

void loop(){
  checkForControlChange();
}

void checkForControlChange(){

  if (ledState == HIGH){
    if ((millis() - lastBlinkTime) > 60) {
      digitalWrite(LED_BLINKER, LOW);
      ledState = LOW;
    }
  } 

  if ((millis() - lastUpdateTime) > 9 and ledChange == true){
    lastUpdateTime = millis();
    for (int i = 0; i < NUM_LEDS; i++) {leds[i] = CHSV(hue, sat, bri);}
    FastLED.show();
    ledChange = false; 
    if (ledState == LOW){
      digitalWrite(LED_BLINKER, HIGH);
      lastBlinkTime = millis();
      ledState = HIGH;
    }
  }


  midiEventPacket_t rx = MidiUSB.read();

  if(rx.header == 0x0B and (rx.byte1 & 0xF) == MIDI_CHAN){ // rx.byte1 & 0xF == 1 <-- rx.byte1 & 0xF is channel
    if (ledState == LOW){
      digitalWrite(LED_BLINKER, HIGH);
      lastBlinkTime = millis();
      ledState = HIGH;
    }
    switch(rx.byte2) {
      case 14:
        hue = (rx.byte3 * 2);
        break;
      case 15:
        sat = (rx.byte3 * 2);
        break;
      case 16:
        bri = (rx.byte3 * 2);
        break;
    }
    if( abs(hue - hueOld) > 2 or abs(sat - satOld) > 3 or abs(bri - briOld) > 2){
      ledChange = true; 
    }
  }
//  switch (rx.header) {
//    case 0:
//      break; //No pending events
//      
//    case 0x0B:
//      if(rx.byte2 == 14){
//        Serial.println("Control Change on Ch. 14");
//        hue = rx.byte3;
//      }
//      break;
//  }
}
