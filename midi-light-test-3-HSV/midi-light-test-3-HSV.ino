#include <MIDI.h>
#include <FastLED.h>
#define NUM_LEDS    10
#define LED_PIN     11
#define MIDI_CHAN   2


CRGB leds[NUM_LEDS];

MIDI_CREATE_DEFAULT_INSTANCE(); //remove this if using the leonardo instead

int LED_PIN1 = 9;
int LED_PIN2 = 3;
int ledState = LOW;
bool lightOn = false;

byte note = 0;
byte velocity = 0; //doesnt appear to be used
unsigned long lastCheckTime = {0};
unsigned long lastBlinkTime = {0};

//light up led at pin 13 when receiving noteON message with note = 60

void setup(){
//  MIDI.begin(MIDI_CHANNEL_OMNI); 
  Serial.begin(9600); //Serial.begin(115200); //Serial.begin(9600); 
  pinMode(LED_PIN1,OUTPUT);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  delay(200);
}   

void loop(){
  checkForNote();
}

void checkForNote(){

  if (ledState == HIGH){
    if ((millis() - lastBlinkTime) > 60) {
      digitalWrite(LED_PIN1, LOW);
      ledState = LOW;
//      for (int i = 0; i <= NUM_LEDS; i++) {
//        leds[i] = CRGB ( 0, 0, 0);
//        FastLED.show();
//        lightOn = false;
//      }
    }
  } 

  if ((millis() - lastCheckTime) > 5){
    lastCheckTime = millis();
    if(MIDI.read(MIDI_CHAN)){
      //// NOTE listener
      if (MIDI.getType() == (144) and MIDI.getData2() != 0){ //144 = note on
        note = MIDI.getData1();
        velocity = MIDI.getData2();
        //// LED that flashes when a change happens
        if (ledState == LOW){
          digitalWrite(LED_PIN1, HIGH);
          lastBlinkTime = millis();
          ledState = HIGH;
        }
        if (note == 66){
          leds[1] = CHSV (0, 255, 50);
          FastLED.show();
          lightOn = false;
        }
        if (note == 68){
          leds[2] = CHSV (32, 255, 50);
          FastLED.show();
          lightOn = false;       
        }
        if (note == 70){
          leds[3] = CHSV (64, 255, 50);
          FastLED.show();
          lightOn = false;       
        }
        if (note == 73){
          leds[4] = CHSV (96, 255, 50);
          FastLED.show();
          lightOn = false;       
        }
        if (note == 75){
          leds[5] = CHSV (160, 255, 50);
          FastLED.show();
          lightOn = false;       
        }
        if (note == 78){
          leds[6] = CHSV (192, 255, 50);
          FastLED.show();
          lightOn = false;       
        }   
        if (note == 80){
          leds[7] = CHSV (218, 255, 50);
          FastLED.show();
          lightOn = false;       
        } 
      }                                   
      if (MIDI.getType() == (128) or (MIDI.getType()== (144) and MIDI.getData2() == 0)){ //128 = note off
        note = MIDI.getData1();
        velocity = MIDI.getData2();
        //// LED that flashes when a change happens
        if (ledState == LOW){
          digitalWrite(LED_PIN1, HIGH);
          lastBlinkTime = millis();
          ledState = HIGH;
        }
        if (note == 66){
          leds[1] = CRGB (0, 0, 0);
          FastLED.show();
          lightOn = true;
        }
        if (note == 68){
          leds[2] = CRGB (0, 0, 0);
          FastLED.show();
          lightOn = true;       
        }
        if (note == 70){
          leds[3] = CRGB (0, 0, 0);
          FastLED.show();
          lightOn = true;       
        }
        if (note == 73){
          leds[4] = CRGB (0, 0, 0);
          FastLED.show();
          lightOn = true;       
        }
        if (note == 75){
          leds[5] = CRGB (0, 0, 0);
          FastLED.show();
          lightOn = true;       
        }
        if (note == 78){
          leds[6] = CRGB (0, 0, 0);
          FastLED.show();
          lightOn = true;       
        }   
        if (note == 80){
          leds[7] = CRGB (0, 0, 0);
          FastLED.show();
          lightOn = true;                                     
        }  
      }
    }
  }
}
