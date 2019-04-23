#include <Arduino.h>
#include <FastLED.h>
#include "config.h"

CRGB leds[NUM_LEDS];
int activeLed[NUM_LEDS];

void led_reset()
{
  for(int x = 0; x < NUM_LEDS; x++)
  {
    activeLed[x] = 0;
  }
}

void led_setup()
{
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  led_reset();

}

void led_activate(int ledID)
{
  activeLed[ledID] = 1;
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

void led_update()
{

  for(int i = 0; i < NUM_LEDS; i++) {
    if(activeLed[i] == 1){
      leds[i] = CRGB::White;
    } else {
      leds[i] = CRGB::Black;
    }
  }
  FastLED.show();

}
