#include <Arduino.h>
#include <Wire.h>
#include <RtcDS1307.h>

#include "clock.h"
#include "config.h"

RtcDS1307<TwoWire> Rtc(Wire);

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];
    snprintf_P(datestring,
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
}

void updateTime(const RtcDateTime& dt){
  unsigned char hoursNow = dt.Hour();
  int hours = hoursNow;
  unsigned char minutesNow = dt.Minute();
  int minutes = minutesNow;
  timeToText(hours, minutes);
}

void rtc_setup()
{
  Wire.begin();
  Rtc.Begin();

  Serial.print("compiled: ");
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  printDateTime(compiled);
  Serial.println();

  if (!Rtc.IsDateTimeValid())
  {
      if (Rtc.LastError() != 0)
      {
          // we have a communications error
          // see https://www.arduino.cc/en/Reference/WireEndTransmission
          Serial.print("RTC communications error = ");
          Serial.println(Rtc.LastError());
      }
      else
      {
          // Common Cuases:
          //    1) first time you ran and the device wasn't running yet
          //    2) the battery on the device is low or even missing
          Serial.println("RTC lost confidence in the DateTime!");
          // following line sets the RTC to the date & time this sketch was compiled
          // it will also reset the valid flag internally unless the Rtc device is having an issue
          Rtc.SetDateTime(compiled);
      }
  }
  if (!Rtc.GetIsRunning())
  {
      Serial.println("RTC was not actively running, starting now");
      Rtc.SetIsRunning(true);
  }
  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled)
  {
      Serial.println("RTC is older than compile time!  (Updating DateTime)");
      Rtc.SetDateTime(compiled);
  }
  Rtc.SetSquareWavePin(DS1307SquareWaveOut_Low);
}

void rtc_task()
{
  if (!Rtc.IsDateTimeValid())
  {
      if (Rtc.LastError() != 0)
      {
          // we have a communications error
          // see https://www.arduino.cc/en/Reference/WireEndTransmission for
          Serial.print("RTC communications error = ");
          Serial.println(Rtc.LastError());
      }
      else
      {
          Serial.println("RTC lost confidence in the DateTime!");
      }
  }
  RtcDateTime now = Rtc.GetDateTime();
  updateTime(now);
}
