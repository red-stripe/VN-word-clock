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

/*
  for(int i = 0; i < 24; i++)
  {
    for(int x = 0; x < 60; x += 5)
    {
      timeToText(i,x);
      led_update();
      delay(2000);
      led_reset();
    }
  }
  */
}
