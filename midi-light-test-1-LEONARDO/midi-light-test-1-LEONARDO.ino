#include "MIDIUSB.h"
#include <FastLED.h>
#define NUM_LEDS    10
#define LED_PIN     9
CRGB leds[NUM_LEDS];

byte note = 0;
byte velocity = 0; //doesnt appear to be used
byte noteToCheck = 60;
unsigned long lastCheckTime = {0};

void setup(){
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(38400);
  for (int i = 0; i <= NUM_LEDS; i++) {
    leds[i] = CRGB ( 0, 5, 5 );
    FastLED.show();   
  }
}   

void loop(){
  checkForNote();
}

void checkForNote(){

  midiEventPacket_t rx = MidiUSB.read();
  switch (rx.header) {
    case 0:
      break; //No pending events
      
    case 0x9:
      Serial.print("Note On");
      note = rx.byte2;
      velocity = rx.byte3;
//      noteOn(
//        rx.byte1 & 0xF,  //channel
//        rx.byte2,        //pitch
//        rx.byte3         //velocity
//      );
      break;
      
    case 0x8:
      Serial.print("Note Off");
      note = rx.byte2;
      velocity = 0;
//      noteOff(
//        rx.byte1 & 0xF,  //channel
//        rx.byte2,        //pitch
//        rx.byte3         //velocity
//      );
      break;
      
    default:
      Serial.print("Unhandled MIDI message: ");
      Serial.print(rx.header, HEX);
      Serial.print("-");
      Serial.print(rx.byte1, HEX);
      Serial.print("-");
      Serial.print(rx.byte2, HEX);
      Serial.print("-");
      Serial.println(rx.byte3, HEX);
  }

  if (note == 64){
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i] = CRGB ( velocity, 0, 0 );
      FastLED.show();   
    }
  }

//  if ((millis() - lastCheckTime) > 5){ 
//      lastCheckTime = millis();
//      if(midiUSB.read(2)){
//        //// NOTE listener
//        if (MIDI.getType()==144){ //144 = note on
//          note = MIDI.getData1();
//          velocity = MIDI.getData2();
//          if (note == 64){
//            for (int i = 0; i <= NUM_LEDS; i = i++) {
//              leds[i] = CRGB ( velocity, 0, 0 );
//              FastLED.show();   
//            }
//          }
//        }
//        if (MIDI.getType()==176){ //176 = control
//          analogWrite(LED_PIN, MIDI.getData2());
//
//        }
//      }
//    }
}
