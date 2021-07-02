/*
  HSI to RGB test

  Reads three potentiometers and maps them to hue (360-point range),
  saturation (100-point range), and intensity (100-point range),
  then sets the pixels of a strip.

  This assumes you're using Sparkfun's Illumenati boards for the APA102s,
  and that you're using the built-in SPI SCLK and MOSI pins for control.


  Uses Adafruit's NeoPixel library:
  https://github.com/adafruit/Adafruit_NeoPixel

  created 10 Jan 2018
  by Tom Igoe
*/
#include <Adafruit_DotStar.h>
#include <ColorConverter.h>

const int neoPixelPin = 5;  // control pin
const int pixelCount = 8;    // number of pixels

// set up strip:
Adafruit_DotStar strip = Adafruit_DotStar(pixelCount, DOTSTAR_BGR);
ColorConverter converter;

void setup() {
  strip.begin();    // initialize pixel strip
  strip.clear();    // turn all LEDs off
  strip.show();     // refresh strip
  Serial.begin(9600);
}

void loop() {
  // read:
  int hue = analogRead(A0) * 360 / 1024;
  delay(1);
  int sat = analogRead(A1) * 100 / 1024;
  delay(1);
  int intensity = analogRead(A2) * 100 / 1024;

  //convert:
  RGBColor color;
  color = converter.HSItoRGB(hue, sat, intensity);
  // print the two color spaces:
  Serial.print("H: ");
  Serial.print(hue);
  Serial.print(", S: ");
  Serial.print(sat);
  Serial.print(", I: ");
  Serial.println(intensity);

  Serial.print("R: ");
  Serial.print(color.red);
  Serial.print(", G: ");
  Serial.print(color.green);
  Serial.print(", B: ");
  Serial.println(color.blue);
  Serial.println();

  // loop over all the pixels:
  for (int pixel = 0; pixel < pixelCount; pixel++) {
    // set the color for this pixel:
    strip.setPixelColor(pixel, color.red, color.green, color.blue);
  }
  strip.show();    // refresh the strip
}
