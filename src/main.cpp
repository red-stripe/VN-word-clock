#include <Arduino.h>
#include "rtc.h"
#include "leds.h"
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
  led_task();
  delay(10000); // ten seconds
}
