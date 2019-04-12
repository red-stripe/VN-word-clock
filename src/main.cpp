#include <Arduino.h>
#include "RTC.h"
#include "config.h"

void setup ()
{
    Serial.begin(57600);
    delay(3000);
    rtc_setup();
}

void loop ()
{
  rtc_task();

    delay(10000); // ten seconds
}
