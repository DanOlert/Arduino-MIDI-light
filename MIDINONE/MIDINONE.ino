//variables setup
#include <MIDIUSB.h>

byte incomingByte;

int led = 11;   // select the pin for the monostable
int channel = 1; // MIDI channel to respond to (in this case channel 2) chnage this to change the channel number
                 // MIDI channel = the value in 'channel' + 1

//setup: declaring iputs and outputs and begin serial 
void setup() {
  //start serial with MIDI baudrate 31250 or 38400 for debugging
  Serial.begin(38400); //  Serial.begin(31250);          
}

//loop: wait for serial data, and interpret the message 
void loop () {

  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
//      case 0:
    // look for as status-byte, our channel, note on
    if (incomingByte== (144 | channel)){ 
         Serial.print("Note On");
        }
    // look for as status-byte, our channel, note off
    if (incomingByte== (128 | channel)){ 
         Serial.print("Note Off");
        }

    // look for as status-byte, our channel, cc change
    if (incomingByte== (176 | channel)){ 
         Serial.print("C C");
        }
        
//       case 1:
//       // get the note to play or stop
//       if(incomingByte < 128) {
//          note=incomingByte;
//          state=2;
//       }
//       else{
//       state = 0;  // reset state machine as this should be a note number
//       }
//       break;
//       
//       case 2:
//       // get the velocity
//       if(incomingByte < 128) {
//         playNote(note, incomingByte, noteDown); // fire off the solenoid
//       }
//         state = 0;  // reset state machine to start            
//     }
  }
}

//void playNote(byte note, byte velocity, int down){
//  // if velocity = 0 on a 'Note ON' command, treat it as a note off
//  if ((down == HIGH) && (velocity == 0)){
//      down = LOW; 
//  }
// //since we can't play all notes we only action notes between 36 & 49
// if(note>=baseNote && note<(baseNote + 13)){
//   byte myPin=playArray[note-baseNote]; // to get a pin number between 2 and 9
//   if(myPin != 0) {
//     digitalWrite(myPin, down); // play it if it is one of our notes
//     if(down == HIGH) digitalWrite(strobe, HIGH); // strobe high to monostable for note on
//   }
// } 
//
//}
