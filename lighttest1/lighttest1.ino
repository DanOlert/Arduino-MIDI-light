    #include <FastLED.h>
    #define LED_PIN     11
    #define NUM_LEDS    60
    #define LED_SPACE   4
    #define CHANGE_DELAY   2000

    #define WS2812_RED   200
    #define WS2812_GREEN 40
    #define WS2812_BLUE 150
    
    CRGB leds[NUM_LEDS];
    void setup() {
      FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
      Serial.begin(9600);
    }
    void loop() {
      for (int i = 1; i <= NUM_LEDS; i = i + 4) {
        leds[i] = CRGB ( 0, 0, 0);
        FastLED.show();
      }
      for (int i = 0; i <= NUM_LEDS; i = i + 4) {
        leds[i] = CRGB ( WS2812_RED, WS2812_GREEN, WS2812_BLUE); // max is 255
        FastLED.show();
          
      }
      delay(CHANGE_DELAY);

      for (int i = 3; i <= NUM_LEDS; i = i + 4) {
        leds[i] = CRGB ( 0, 0, 0);
        FastLED.show();
      }
      for (int i = 2; i <= NUM_LEDS; i = i + 4) {
        leds[i] = CRGB ( WS2812_RED, WS2812_GREEN, WS2812_BLUE);
        FastLED.show();
          
      }
      delay(CHANGE_DELAY);

      for (int i = 0; i <= NUM_LEDS; i = i + 4) {
        leds[i] = CRGB ( 0, 0, 0);
        FastLED.show();
      }
      for (int i = 1; i <= NUM_LEDS; i = i + 4) {
        leds[i] = CRGB ( WS2812_RED, WS2812_GREEN, WS2812_BLUE);
        FastLED.show();
          
      }
      delay(CHANGE_DELAY);

      for (int i = 2; i <= NUM_LEDS; i = i + 4) {
        leds[i] = CRGB ( 0, 0, 0);
        FastLED.show();
      }
      for (int i = 3; i <= NUM_LEDS; i = i + 4) {
        leds[i] = CRGB ( WS2812_RED, WS2812_GREEN, WS2812_BLUE);
        FastLED.show();
          
      }
      delay(CHANGE_DELAY);
//
//      for (int k = 0; k < LED_SPACE; k++){
//        Serial.println(k);
//        if (k == 0){
//          Serial.println("top");
//          for (int i = (LED_SPACE-1); i <= 10; i = i + LED_SPACE) { /// you can nest these in another for loop to control how far away the blips are
//          leds[i] = CRGB ( 0, 0, 0);
//          FastLED.show();   
//          }      
//        } else {
//          Serial.println("p");
//          for (int i = (k - 1); i <= 10; i = i + LED_SPACE) { /// you can nest these in another for loop to control how far away the blips are
//          leds[i] = CRGB ( 0, 0, 0);
//          FastLED.show();
//          }
//        }
//        for (int i = k; i <= 10; i = i + LED_SPACE) {
//          leds[i] = CRGB ( 15, 0, 15);
//          FastLED.show();
//            
//        }
//        delay(200); 
//          
//      }


    }
