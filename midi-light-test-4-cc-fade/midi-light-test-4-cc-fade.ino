#include <MIDI.h>
#include <FastLED.h>
#define NUM_LEDS    10
#define LED_PIN     11
#define MIDI_CHAN   2

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif


struct CRGB leds[NUM_LEDS]; 

MIDI_CREATE_DEFAULT_INSTANCE(); //remove this if using the leonardo instead

int LED_PIN1 = 9;
int LED_PIN2 = 3;
int ledState = LOW;
bool ledChange = false;


byte note = 0;
byte velocity = 0;
uint8_t hue = 200;
uint8_t sat = 255;
uint8_t bri = 30;
uint8_t hueOld = 200;
uint8_t satOld = 255;
uint8_t briOld = 30;
unsigned long lastCheckTime = {0};
unsigned long lastBlinkTime = {0};
unsigned long lastUpdateTime = {0};

//light up led at pin 13 when receiving noteON message with note = 60

void setup(){
  delay(600);
//  MIDI.begin(MIDI_CHANNEL_OMNI); 
  Serial.begin(19200); //Serial.begin(115200); //Serial.begin(9600); 
  pinMode(LED_PIN1,OUTPUT);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  delay(200);
}   

void loop(){
  checkForControlChange();
}

void checkForControlChange(){

  if (ledState == HIGH){
    if ((millis() - lastBlinkTime) > 60) {
      digitalWrite(LED_PIN1, LOW);
      ledState = LOW;
    }
  } 

  if ((millis() - lastUpdateTime) > 9 and ledChange == true){
    lastUpdateTime = millis();
    for (int i = 0; i < NUM_LEDS; i++) {leds[i] = CHSV(hue, 255, 50);}
    FastLED.show();
    ledChange = false; 
    if (ledState == LOW){
      digitalWrite(LED_PIN1, HIGH);
      lastBlinkTime = millis();
      ledState = HIGH;
    }
  }

//  if ((millis() - lastCheckTime) > 0){
    lastCheckTime = millis();
    if(MIDI.read(MIDI_CHAN)){
      
      //// CC listener
      if (MIDI.getType() == (176)){ //176 = cc
        if (MIDI.getData1() == 14){
//          Serial.println(MIDI.getData2());
//          if (ledState == LOW){
//            digitalWrite(LED_PIN1, HIGH);
//            lastBlinkTime = millis();
//            ledState = HIGH;
//          }
          hue = MIDI.getData2();
        }  
        if( abs(hue - hueOld) > 2 or abs(sat - satOld) > 3 or abs(bri - briOld) > 2){
          ledChange = true; 
        }
      }  
    }
//  }
}
