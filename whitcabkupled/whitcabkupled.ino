//#include <ColorConverter.h>
#include "MIDIUSB.h"
#include <FastLED.h>

#define LED_BLINKER 13

#define MIDI_CHAN   1


#define LED_PIN     11
#define NUM_LEDS    20
#define LED_SPACE   4
#define CHANGE_DELAY   1000

uint8_t WS2812_RED   = 200;
uint8_t WS2812_GREEN = 40;
uint8_t WS2812_BLUE  = 150;
uint8_t ledstep  = 4;
int ledOn = LOW;


bool ledOpe = false;

int wsled = 0;
int wsled_old = 0;

int ledState = LOW;
bool ledChange = false;

unsigned long lastBlinkTime = {0};
unsigned long lastUpdateTime = {0};

CRGB leds[NUM_LEDS];
void setup() {
  delay(600);
  pinMode(LED_BLINKER,OUTPUT);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);
}
    
void loop() {

//  if (ledState == HIGH){
//    if ((millis() - lastBlinkTime) > 60) {
//      digitalWrite(LED_BLINKER, LOW);
//      ledState = LOW;
//    }
//  }

//  delay(500);
//  Serial.println("oh hi");

  midiEventPacket_t rx = MidiUSB.read();

//
//  if ((millis() - lastBlinkTime) > 700) {
////    Serial.println("oh hi");
//    Serial.println(rx.byte2);
//    lastBlinkTime = millis();
//  }
  

  if(rx.header == 0x0B and (rx.byte1 & 0xF) == MIDI_CHAN){ // rx.byte1 & 0xF == 1 <-- rx.byte1 & 0xF is channel

//    Serial.println(rx.byte2);
    
//    if (ledState == LOW){
//      digitalWrite(LED_BLINKER, HIGH);
//      lastBlinkTime = millis();
//      ledState = HIGH;
//    }
    if (rx.byte2 == 39){
      wsled = int(rx.byte3);
        Serial.println("  ");
        Serial.println(" CHANGE ");
        Serial.println(rx.byte3);
        Serial.println("ssksks");
        if (wsled > 11){
          ledOn = HIGH;
        }else{
          ledOn = LOW;
        }
    }
    
//    switch(rx.byte2) {
//      case 39:
//        wsled = int(rx.byte3);
//        Serial.println("  ");
//        Serial.println(" CHANGE ");
//        Serial.println(rx.byte3);
//        if (wsled > 11){
//          Serial.println(wsled);
//          ledOn = HIGH;
//        }else{
//          ledOn = LOW;
//        }
//    }
    
    
  }


    

  if(ledOn == HIGH){

    //////1
    if (ledstep == 0) {
      for (int i = 1; i <= NUM_LEDS; i = i + 4) {
        leds[i] = CRGB ( 0, 0, 0);
        FastLED.show();
      }
      for (int i = 0; i <= NUM_LEDS; i = i + 4) {
        leds[i] = CRGB ( WS2812_RED, WS2812_GREEN, WS2812_BLUE); // max is 255
        FastLED.show();       
      }
      ledstep = 1;
      Serial.println(" ");
      Serial.println("step 1"); 
      Serial.println(ledOn);
      Serial.println(ledstep);
      Serial.println((millis() - lastUpdateTime));

      ///////2
    }else if ((millis() - lastUpdateTime) > CHANGE_DELAY and ledstep == 1) {
      for (int i = 3; i <= NUM_LEDS; i = i + 4) {
        leds[i] = CRGB ( 0, 0, 0);
        FastLED.show();
      }
      for (int i = 2; i <= NUM_LEDS; i = i + 4) {
        leds[i] = CRGB ( WS2812_RED, WS2812_GREEN, WS2812_BLUE);
        FastLED.show();   
      }
      ledstep = 2;
      Serial.println(" ");
      Serial.println("step 2");
      Serial.println(ledstep);
      Serial.println(ledOn);
      Serial.println((millis() - lastUpdateTime));

      ///////3
    }else if ((millis() - lastUpdateTime) > (CHANGE_DELAY*2) and ledstep == 2) {
      for (int i = 0; i <= NUM_LEDS; i = i + 4) {
        leds[i] = CRGB ( 0, 0, 0);
        FastLED.show();
      }
      for (int i = 1; i <= NUM_LEDS; i = i + 4) {
        leds[i] = CRGB ( WS2812_RED, WS2812_GREEN, WS2812_BLUE);
        FastLED.show();  
      }
      ledstep = 3;
      Serial.println(" ");
      Serial.println("step 3");
      Serial.println(ledOn);
      Serial.println(millis() - lastUpdateTime);
    
      ///////4
    }else if ((millis() - lastUpdateTime) > (CHANGE_DELAY*3) and ledstep == 3) {
      Serial.println("step 4");
      for (int i = 2; i <= NUM_LEDS; i = i + 4) {
        leds[i] = CRGB ( 0, 0, 0);
        FastLED.show();
      }
      for (int i = 3; i <= NUM_LEDS; i = i + 4) {
        leds[i] = CRGB ( WS2812_RED, WS2812_GREEN, WS2812_BLUE);
        FastLED.show();       
      }
      Serial.println(millis() - lastUpdateTime);
      Serial.println(CHANGE_DELAY*3);
      ledstep = 4;

     ///////reset
    }else if ((millis() - lastUpdateTime) > (CHANGE_DELAY*4) and ledstep == 4) {
      lastUpdateTime = millis();
      ledstep = 0;
      Serial.println("ope2");
    }

    

    
  }else{
//    Serial.println(wsled);
    for (int i = 1; i <= NUM_LEDS; i = i + 1) {
      leds[i] = CRGB ( 0, 0, 0);
      FastLED.show();
      ledstep = 4;
    }
  }
  
}
