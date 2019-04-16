#include <Arduino.h>
#include "rtc.h"
#include "leds.h"
#include "config.h"

int activeLed[NUM_LEDS];

void setup ()
{
    Serial.begin(57600);
    delay(3000);
    rtc_setup();
    led_setup();
    for(int x = 0; x < NUM_LEDS; x++)
    {
      activeLed[x] = 0;
    }
}

typedef struct letters {
  int length;
  const int* values;
}
letters;


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
const int t_00[]  = {39, 40, 41};
const int t_05[]  = {49, 50, 51};
const int t_10[]  = {62, 63, 64, 65};
const int t_15[]  = {55, 56, 57, 58, 59, 60, 61};
const int t_20[]  = {39, 40, 41, 52, 53, 54, 62, 63, 64, 65};
const int t_25[]  = {39, 40, 41, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61};
const int t_30[]  = {45, 46, 47, 48};
const int t_35[]  = {39, 40, 41, 42, 43, 44, 52, 53, 54, 59, 60, 61};
const int t_40[]  = {39, 40, 41, 42, 43, 44, 52, 53, 54, 62, 63, 64, 65};
const int t_45[]  = {39, 40, 41, 42, 43, 44, 55, 56 ,57, 58, 59, 60, 61};
const int t_50[]  = {39, 40, 41, 42, 43, 44, 62, 63, 64, 65};
const int t_55[]  = {39, 40, 41, 42, 43, 44, 49, 50, 51};

letters minuteWord[] = {
  {sizeof(t_00) / sizeof(t_00[0]), t_00},
  {sizeof(t_05) / sizeof(t_00[0]), t_05},
  {sizeof(t_10) / sizeof(t_00[0]), t_10},
  {sizeof(t_15) / sizeof(t_00[0]), t_15},
  {sizeof(t_20) / sizeof(t_00[0]), t_20},
  {sizeof(t_25) / sizeof(t_00[0]), t_25},
  {sizeof(t_30) / sizeof(t_00[0]), t_30},
  {sizeof(t_35) / sizeof(t_00[0]), t_35},
  {sizeof(t_40) / sizeof(t_00[0]), t_40},
  {sizeof(t_45) / sizeof(t_00[0]), t_45},
  {sizeof(t_50) / sizeof(t_00[0]), t_50},
  {sizeof(t_55) / sizeof(t_00[0]), t_55},
};

const int minuteResolution = sizeof(minuteWord) / sizeof(minuteWord[0]);

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
/*
const int t_itis[8] =       { 0,  1,  2, 3, 4, 5, 6, 7 };
const int t_ten[4] =        { 8, 9, 10, 11};
const int t_eleven =        { 8, 9, 10, 11, 12, 13, 14};
const int t_twelve =        { 8, 9, 10, 11, 15, 16, 17};
const int t_one =           { 12, 13, 14 };
const int t_two =           { 15, 16, 17 };
const int t_three =         { 18, };
*/


void resetLed()
{
  for(int x = 0; x < NUM_LEDS; x++)
  {
    activeLed[x] = 0;
  }
}

void textToWords(letters minuteLed)
{
  for(int x = 0; x < minuteLed.length; x++)
  {
    activeLed[minuteLed.values[x]] = 1;
  }
}

void loop ()
{
  rtc_task();
  resetLed();
//led_task();
  for(int x = 0; x < 12; x++)
  {
    textToWords(minuteWord[x]);
    led_update(activeLed);
    delay(1000);
  }


  delay(10000); // ten seconds
}
