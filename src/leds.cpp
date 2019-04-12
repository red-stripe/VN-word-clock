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
