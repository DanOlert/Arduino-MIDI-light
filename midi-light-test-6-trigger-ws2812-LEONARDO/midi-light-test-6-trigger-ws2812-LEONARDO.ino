#include "MIDIUSB.h"
#include <FastLED.h>

#define LED_BLINKER 13

#define MIDI_CHAN   1

#define LED_PIN     11
#define NUM_LEDS    50
#define LED_SPACE   6
#define CHANGE_DELAY   135

uint8_t WS2812_RED   = 210;
uint8_t WS2812_GREEN = 50;
uint8_t WS2812_BLUE  = 170;
uint8_t ledstep  = 4;

uint8_t wsled = 0;

int ledState = LOW;
bool ledChange = false;

unsigned long lastUpdateTime = {0};

CRGB leds[NUM_LEDS];

void setup() {
  delay(600);
  pinMode(LED_BLINKER,OUTPUT);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);
}
    
void loop() {

  midiEventPacket_t rx = MidiUSB.read();

  if(rx.header == 0x0B and (rx.byte1 & 0xF) == MIDI_CHAN){ // rx.byte1 & 0xF == 1 <-- rx.byte1 & 0xF is channel

    switch(rx.byte2) {
      case 39:
        wsled = (rx.byte3);
//        Serial.println(rx.byte3);
    }    
    
  }


    

  if(wsled > 11){
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
      wsled = 50;
//      Serial.println(wsled);

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
      wsled = 50;
//      Serial.println(" ");
//      Serial.println("step 2");
//      Serial.println(wsled);
//      Serial.println((millis() - lastUpdateTime));

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
      wsled = 50;
//      Serial.println(" ");
//      Serial.println("step 3");
//      Serial.println(wsled);
//      Serial.println(millis() - lastUpdateTime);
//      Serial.println(wsled);
    
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
//      Serial.println(" ");
//      Serial.println("step 2");
      ledstep = 4; 
      wsled = 50;
//      Serial.println(wsled);

     ///////reset
    }else if ((millis() - lastUpdateTime) > (CHANGE_DELAY*4) and ledstep == 4) {
      lastUpdateTime = millis();
      ledstep = 0;
//      Serial.println("ope2");
    }

    

    
  }else{
//    Serial.println(wsled);
    for (int i = 0; i <= NUM_LEDS; i = i + 1) {
      leds[i] = CRGB ( 0, 0, 0);
      FastLED.show();
      ledstep = 4;
    }
  }
  
}




















//
//
//
//uint8_t hue = 200;
//uint8_t sat = 255;
//uint8_t bri = 30;
//uint8_t hueOld = 200;
//uint8_t satOld = 255;
//uint8_t briOld = 30;
//
//uint16_t hueConversionScaled = 0;
//uint8_t satConversionScaled = 0;
//uint8_t briConversionScaled = 0;
//
//
//ColorConverter HSBConverter;
//
////light up led at pin 13 when receiving noteON message with note = 60
//
//void setup(){
//  delay(600);
//
//  /////// THIS PART IS FOR THE NEW TRIGGER CC 39 THING ///
//  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
//  /////////////////////////////////////////////////////////
//  
////  Serial.begin(38400); //Serial.begin(115200); //Serial.begin(9600); 
//  pinMode(LED_BLINKER,OUTPUT);
//
//  delay(200);
//}   
//
//void loop(){
//  checkForControlChange();
//}
//
//void checkForControlChange(){
//
//  if (ledState == HIGH){
//    if ((millis() - lastBlinkTime) > 60) {
//      digitalWrite(LED_BLINKER, LOW);
//      ledState = LOW;
//    }
//  }
//
//
//
//
//
//
//  if ((millis() - lastUpdateTime) > 8 and ledChange == true){
//    lastUpdateTime = millis();
//    /// convert hue to 0-360, sat 0-100, bri to 0-10
////    // Debug
////    Serial.print("R G B - ");
////    Serial.print(light1Color.red);
////    Serial.print(" ");
////    Serial.print(light1Color.green);
////    Serial.print(" ");
////    Serial.print(light1Color.blue);
////    Serial.println(" ");
// 
//    ledChange = false;
//    if (ledState == LOW){
//      digitalWrite(LED_BLINKER, HIGH);
//      lastBlinkTime = millis();
//      ledState = HIGH;
//    }
//  }
//
//
//  midiEventPacket_t rx = MidiUSB.read();
//
//  if(rx.header == 0x0B and (rx.byte1 & 0xF) == MIDI_CHAN){ // rx.byte1 & 0xF == 1 <-- rx.byte1 & 0xF is channel
//    if (ledState == LOW){
//      digitalWrite(LED_BLINKER, HIGH);
//      lastBlinkTime = millis();
//      ledState = HIGH;
//    }
//    switch(rx.byte2) {
//      case 14:
//        hue = (rx.byte3 * 2);
//        break;
//      case 15:
//        sat = (rx.byte3 * 2);
//        break;
//      case 16:
//        bri = (rx.byte3 * 2);
//        break;
//      case 39:
//        wsled = (rx.byte3);
//    }
//    
//    if( abs(hue - hueOld) > 2 or abs(sat - satOld) > 3 or abs(bri - briOld) > 2 or abs(wsled - wsled_OLD) > 4 ){
//      ledChange = true; 
//    }
//    
//    
//  }
//}
