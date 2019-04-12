#include <Arduino.h>

// CONNECTIONS:
// DS1307 SDA --> SDA
// DS1307 SCL --> SCL
// DS1307 VCC --> 5v
// DS1307 GND --> GND

#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS1307.h>
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
//int hours = 1;
  //dt.Second())
//int hours = dt.Hour().toInt();
//unsigned int hours = atoi (dt.Hour());

switch (hours) {
  case 12:
    Serial.println("Muoi Hai");
    break;
  case 11:
    Serial.println("Muoi Mot");
    break;
  case 10:
    Serial.println("Muoi");
    break;
  case 9:
    Serial.println("Chin");
    break;
  case 8:
    Serial.println("Tam");
    break;
  case 7:
    Serial.println("Bay");
    break;
  case 6:
    Serial.println("Sau");
    break;
  case 5:
    Serial.println("Nam");
    break;
  case 4:
    Serial.println("Bon");
    break;
  case 3:
    Serial.println("Ba");
    break;
  case 2:
    Serial.println("Hai");
    break;
  case 1:
    Serial.println("Mot");
    break;
    default:
      Serial.println("woops");

}



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


void setup ()
{
    Serial.begin(57600);
    delay(3000);

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

void loop ()
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

    delay(10000); // ten seconds
}
