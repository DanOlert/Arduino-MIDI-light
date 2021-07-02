void setup() {
  pinMode(9, OUTPUT);    // sets the digital pin 13 as output
}

void loop() {
  digitalWrite(9, HIGH); // sets the digital pin 13 on
  delay(1000);            // waits for a second
  digitalWrite(9, LOW);  // sets the digital pin 13 off
  delay(1000);            // waits for a second
}
