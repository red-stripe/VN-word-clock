#include <Arduino.h>
#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS1307.h>

#include "config.h"
// CONNECTIONS:
// DS1307 SDA --> SDA
// DS1307 SCL --> SCL
// DS1307 VCC --> 5v
// DS1307 GND --> GND


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



void timeToText(const RtcDateTime& dt){
  Serial.print(dt.Hour());
  Serial.println(dt.Minute());
  unsigned char hoursNow = dt.Hour();
  int hours = hoursNow;
  unsigned char minutesNow = dt.Minute();
  int minutes = minutesNow;
//int hours = 1;
  //dt.Second())
//int hours = dt.Hour().toInt();
//unsigned int hours = atoi (dt.Hour());

//TODO: Fix time offsets for "25 minutes TO three... etc"
switch (hours) {
  case 12:
  case 0:
    Serial.print("Muoi Hai");
    break;
  case 11:
  case 23:
    Serial.print("Muoi Mot");
    break;
  case 10:
  case 22:
    Serial.print("Muoi");
    break;
  case 9:
  case 21:
    Serial.print("Chin");
    break;
  case 8:
  case 20:
    Serial.print("Tam");
    break;
  case 7:
  case 19:
  Serial.print("Bay");
    break;
  case 6:
  case 18:
    Serial.print("Sau");
    break;
  case 5:
  case 17:
    Serial.print("Nam");
    break;
  case 4:
  case 16:
    Serial.print("Bon");
    break;
  case 3:
  case 15:
    Serial.print("Ba");
    break;
  case 2:
  case 14:
    Serial.print("Hai");
    break;
  case 1:
  case 13:
    Serial.print("Mot");
    break;
    default:
      Serial.println("woops");

}

if( minutes < 5){
  Serial.print("giờ");
}
else if( minutes >= 5 && minutes < 10){
  Serial.print("năm");
}
else if( minutes >= 10 && minutes < 15){
  Serial.print("muoi");
}
else if( minutes >= 15 && minutes < 20){
  Serial.print("muoi");
  Serial.print("lam");
}
else if( minutes >= 20 && minutes < 25){
  Serial.print("giờ");
  Serial.print("hai");
  Serial.print("muoi");
}
else if( minutes >= 25 && minutes < 30){
  Serial.print("giờ");
  Serial.print("hai");
  Serial.print("muoi");
  Serial.print("lam");
}
else if( minutes >= 30 && minutes < 35){
  Serial.print("ruoi");
}
else if( minutes >= 35 && minutes < 40){
  Serial.print("giờ");
  Serial.print("kem");
  Serial.print("hai");
  Serial.print("lam");
  Serial.print("phut");
}
else if( minutes >= 40 && minutes < 45){
  Serial.print("giờ");
  Serial.print("kem");
  Serial.print("hai");
  Serial.print("muoi");
  Serial.print("phut");
}
else if( minutes >= 45 && minutes < 50){
  Serial.print("giờ");
  Serial.print("kem");
  Serial.print("muoi");
  Serial.print("lam");
}
else if( minutes >= 50 && minutes < 55){
  Serial.print("giờ");
  Serial.print("kem");
  Serial.print("muoi");
  Serial.print("phut");
}
else if( minutes >= 55){
  Serial.print("giờ");
  Serial.print("kem");
  Serial.print("nam");
  Serial.print("phut");
}

Serial.println();
/*
Minutes
00  gio
05  Nam
10  muoi
15  muoi lam
20  gio hai muoi
25  gio hai muoi lam
30  ruoi
35  gio kem hai lam
40 gio kem hai muoi
45 gio kem muoi lam
50 gio kem Muoi
55  gio kem nam

*/

  /*
    The time is = bay gio la
    ten         = Muoi
    eleven      = Muoi Mot
    twelve      = Muoi Hai
    one         = Mot
    two         = Hai
    three       = Ba
    four        = Bon
    five        = Nam
    six         = Sau
    seven       = Bay
    eight       = Tam
    nine        = Chin


  */

}



void rtc_setup()
{
  Wire.begin();
  Rtc.Begin();

  //Print time code was compiled
  Serial.print("compiled: ");
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  printDateTime(compiled);
  Serial.println();

  if (!Rtc.IsDateTimeValid())
  {
      if (Rtc.LastError() != 0)
      {
          // we have a communications error
          // see https://www.arduino.cc/en/Reference/WireEndTransmission for
          // what the number means
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
          // it will also reset the valid flag internally unless the Rtc device is
          // having an issue

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
  else if (now > compiled)
  {
      Serial.println("RTC is newer than compile time. (this is expected)");

  }
  else if (now == compiled)
  {
      Serial.println("RTC is the same as compile time! (not expected but all is fine)");
  }

  // never assume the Rtc was last configured by you, so
  // just clear them to your needed state
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
          // what the number means
          Serial.print("RTC communications error = ");
          Serial.println(Rtc.LastError());
      }
      else
      {
          // Common Cuases:
          //    1) the battery on the device is low or even missing and the power line was disconnected
          Serial.println("RTC lost confidence in the DateTime!");
      }
  }

  RtcDateTime now = Rtc.GetDateTime();

  printDateTime(now);
  Serial.println();
  timeToText(now);
  Serial.println();

}
