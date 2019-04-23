#include <Arduino.h>
#include "rtc.h"
#include "leds.h"
#include "clock.h"
#include "config.h"


void setup ()
{
    Serial.begin(57600);
    delay(3000);
    rtc_setup();
    led_setup();
}

void loop ()
{
  rtc_task();
  led_update();
  delay(10000);
  led_reset();
//led_task();
/*
  for(int i = 1; i < 13; i++)
  {
    for(int x = 0; x < 12; x++)
    {
      textToWords(hourWord[0]);
      textToWords(hourWord[i]);
      textToWords(minuteWord[x]);
      led_update(activeLed);
      delay(500);
      resetLed();
    }
  }*/
}
