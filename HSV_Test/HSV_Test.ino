 
/* chsvtest by Andrew Tuline
 
This test is to show that when setting CHSV brightness to less than 16, the LED's remain dark if:
 
- FastLED.show() is performed only in setup.
- FastLED.show() is performed within EVERY_N_MILLISECONDS loop at ~20 ms.
 
It works as expected if:
 
- FastLED.show() performed directly inside loop().
 
 
Environment is:
 
- FastLED 3.1 from July 16, 2015
- Windows 8.1
- Arduino 1.6.3
- Arduino Nano
- 12 LED's of APA102 or WS2812 powered by the Nano both exhibit the same effect.
- Nano powered by USB
 
*/
 
 
#include "FastLED.h"                                          // FastLED library.
 
#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif
 
// Fixed definitions cannot change on the fly.
#define LED_DT 11                                             // Data pin to connect to the strip.
#define LED_CK 11
#define COLOR_ORDER GRB                                       // It's GRB for WS2812B and BGR for APA102.
#define LED_TYPE WS2812B                                       // What kind of strip are you using (WS2801, WS2812B or APA102)?
#define NUM_LEDS 10                                          // Number of LED's.
 
// Initialize changeable global variables.
uint8_t max_bright = 255;                                     // Overall brightness definition. It can be changed on the fly.
 
struct CRGB leds[NUM_LEDS];                                   // Initialize our LED array.
 
uint8_t bgbri = 40;                                           // Nothing shows up when 15, but turns on at 16. if showing LED's just in setup
 
 
void setup() {
  delay(3000);
  Serial.begin(57600);
 
  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);        // Use this for WS2812B
//  LEDS.addLeds<LED_TYPE, LED_DT, LED_CK, COLOR_ORDER>(leds, NUM_LEDS);  // Use this for WS2801 or APA102
 
  FastLED.setBrightness(max_bright);
  for (int i = 0; i < NUM_LEDS; i++) {leds[i] = CHSV(20, 255, bgbri); Serial.print(leds[0].r); Serial.print(":"); Serial.print(leds[0].g); Serial.print(":"); Serial.println(leds[0].b); }
 
} // setup()
 
 
void loop () {
  EVERY_N_MILLISECONDS(20) {                                  // FastLED based non-blocking delay to update/display the sequence.
    FastLED.show();
  }
//  FastLED.show();                                             // Uncomment this line and the LED's will display while bgbri < 15.
} // loop()
