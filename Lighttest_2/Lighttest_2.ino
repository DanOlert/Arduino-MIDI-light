#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE(); //remove this if using the leonardo instead

int LED_PIN = 9;
int LED_PIN2 = 3;
int ledState = LOW;
int ledState2 = LOW;

byte note = 0;
byte velocity = 0; //doesnt appear to be used
byte noteToCheck = 60;
unsigned long lastCheckTime = {0};
unsigned long lastBlinkTime = {0};

//light up led at pin 13 when receiving noteON message with note = 60

void setup(){
//  MIDI.begin(MIDI_CHANNEL_OMNI); 
  Serial.begin(9600); //Serial.begin(115200);
  pinMode(LED_PIN,OUTPUT);
  pinMode(LED_PIN2,OUTPUT);
}   

void loop(){
  checkForNote();
}

void checkForNote(){

  if (ledState == HIGH){
    if ((millis() - lastBlinkTime) > 60) {
      digitalWrite(LED_PIN, LOW);
      ledState = LOW;
    }
    } 

  if ((millis() - lastCheckTime) > 5){ 
      lastCheckTime = millis();
      if(MIDI.read(2)){
        //// NOTE listener
        if (MIDI.getType()==144){ //144 = note on
          note = MIDI.getData1();
          velocity = MIDI.getData2();
        }
        if (MIDI.getType()==176){ //176 = control
          analogWrite(LED_PIN2, MIDI.getData2());

        }
        //// LED that flashes when a change happens
        if (ledState == LOW){
          digitalWrite(LED_PIN, HIGH);
          lastBlinkTime = millis();
          ledState = HIGH;
        }
      }
    }
}
