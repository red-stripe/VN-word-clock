#include <Arduino.h>
#include <FastLED.h>
#include "config.h"

CRGB leds[NUM_LEDS];

void led_setup()
{
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
}


void led_task()
{
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red;
    FastLED.show();
    leds[i] = CRGB::Black;
    delay(100);
  }
}

void led_update(int words[NUM_LEDS])
{
  for(int i = 0; i < NUM_LEDS; i++) {
    if(words[i] == 1){
      leds[i] = CRGB::White;
    } else {
      leds[i] = CRGB::Black;
    }
    FastLED.show();
  }

}
