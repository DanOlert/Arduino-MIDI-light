// These constants won't change. They're used to give names to the pins used:

#include <PWMFreak.h>

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;         // value read from the pot
int lastSensorValue = 0;    // previous value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {

  // initialize serial communications at 9600 bps:
  setPwmFrequency(9, 2);
  Serial.begin(9600);
}

void loop() {

  // read the analog in value:

  if ( abs(analogRead(analogInPin) - sensorValue) > 2) {
    sensorValue = analogRead(analogInPin);

  }
  // map it to the range of the analog out:

  outputValue = map(sensorValue, 0, 1023, 0, 255);

  // change the analog out value:

  analogWrite(analogOutPin, outputValue);

  // print the results to the Serial Monitor:

  if (lastSensorValue != sensorValue){

    Serial.print("sensor = ");
  
    Serial.print(sensorValue);
  
    Serial.print("\t output = ");
  
    Serial.println(outputValue);

    lastSensorValue = sensorValue;

  }

  // wait 2 milliseconds before the next loop for the analog-to-digital

  // converter to settle after the last reading:

  delay(2);
}
