#include <MIDI.h>
#include <FastLED.h>
#define NUM_LEDS    10
#define LED_PIN     11
CRGB leds[NUM_LEDS];

MIDI_CREATE_DEFAULT_INSTANCE(); //remove this if using the leonardo instead

byte note = 0;
byte velocity = 0; //doesnt appear to be used
byte noteToCheck = 60;
unsigned long lastCheckTime = {0};

//light up led at pin 13 when receiving noteON message with note = 60

void setup(){
//  MIDI.begin(MIDI_CHANNEL_OMNI); 
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);
  for (int i = 0; i <= NUM_LEDS; i++) {
    leds[i] = CRGB ( 0, 0, 0 );
    FastLED.show();   
  }
}   

void loop(){
  checkForNote();
}

void checkForNote(){

  if ((millis() - lastCheckTime) > 5){ 
      lastCheckTime = millis();
      if(MIDI.read(2)){
        //// NOTE listener
        if (MIDI.getType()==144){ //144 = note on
          note = MIDI.getData1();
          velocity = MIDI.getData2();
          if (note == 64){
            for (int i = 0; i <= NUM_LEDS; i = i++) {
              leds[i] = CRGB ( velocity, 0, 0 );
              FastLED.show();   
            }
          }
        }
//        if (MIDI.getType()==176){ //176 = control
//          analogWrite(LED_PIN, MIDI.getData2());
//
//        }

      }
    }
}
