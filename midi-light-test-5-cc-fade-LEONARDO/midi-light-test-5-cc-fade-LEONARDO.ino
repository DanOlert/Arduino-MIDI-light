#include <ColorConverter.h>
#include "MIDIUSB.h"

#define RED_LED_PIN 9
#define GRE_LED_PIN 6
#define BLU_LED_PIN 3

#define LED_BLINKER 13

#define MIDI_CHAN   1


int ledState = LOW;
bool ledChange = false;

uint8_t hue = 200;
uint8_t sat = 255;
uint8_t bri = 30;
uint8_t hueOld = 200;
uint8_t satOld = 255;
uint8_t briOld = 30;

uint16_t hueConversionScaled = 0;
uint8_t satConversionScaled = 0;
uint8_t briConversionScaled = 0;

unsigned long lastBlinkTime = {0};
unsigned long lastUpdateTime = {0};

ColorConverter HSBConverter;

//light up led at pin 13 when receiving noteON message with note = 60

void setup(){
  delay(600);
//  Serial.begin(38400); //Serial.begin(115200); //Serial.begin(9600); 
  pinMode(LED_BLINKER,OUTPUT);

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

// ///DEBUGGING
//  if ((millis() - lastUpdateTime) > 2000){
//    Serial.println(hue);
//    Serial.println(" ");
//    lastUpdateTime = millis();
//    hueConversionScaled = floor(hue*(360.0/255.0));
//    satConversionScaled = floor(sat*(100.0/255.0));
//    briConversionScaled = floor(bri*(100.0/255.0));
//    Serial.println(" ");
//    Serial.print(hueConversionScaled);
//    Serial.print(" ");
//    Serial.print(satConversionScaled);
//    Serial.print(" ");
//    Serial.print(briConversionScaled);
//    Serial.println(" ");
//    /// convert hue to 0-360, sat 0-100, bri to 0-100
//    RGBColor light1Color = HSBConverter.HSItoRGB(hueConversionScaled, satConversionScaled, briConversionScaled);
//    Serial.println(light1Color.red);
//    Serial.println(light1Color.green);
//    Serial.println(light1Color.blue);
//    Serial.println(" ");
//    
//  }

  if ((millis() - lastUpdateTime) > 9 and ledChange == true){
    lastUpdateTime = millis();
    /// convert hue to 0-360, sat 0-100, bri to 0-100
    hueConversionScaled = floor(hue*(360.0/255.0));
    satConversionScaled = floor(sat*(100.0/255.0));
    briConversionScaled = floor(bri*(100.0/255.0)); 
       
    RGBColor light1Color = HSBConverter.HSItoRGB(hueConversionScaled, satConversionScaled, briConversionScaled);

    analogWrite(BLU_LED_PIN,light1Color.blue);
    analogWrite(RED_LED_PIN,light1Color.red);
    analogWrite(GRE_LED_PIN,light1Color.green);

//    // Debug
//    Serial.print("R G B - ");
//    Serial.print(light1Color.red);
//    Serial.print(" ");
//    Serial.print(light1Color.green);
//    Serial.print(" ");
//    Serial.print(light1Color.blue);
//    Serial.println(" ");
 
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
