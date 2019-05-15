#include <Arduino.h>
#include <FastLED.h>
#include "leds.h"
#include "config.h"

typedef struct ledLetters {
  int length;
  const int* values;
}
ledLetters;

/*
Minutes
Hai giờ Năm phút           0205
Hai giờ mười    phút       0210
Hai giờ mười Lām phút      0215
Hai giờ Hai mươi phút      0220
Hai giờ hai Lām phút       0225
Hai rưỡi                   0230
Ba giờ kém hai Lām phút    0235
Ba giờ kém hai mươi phút   0240
Ba giờ kém mười Lām phút   0245
Ba giờ kém mười phút       0250
Ba giờ kém nām phút        0255
Ba giờ                     0300
*/

const int t_00[]  = {40, 39, 38}; //giờ
const int t_05[]  = {40, 39, 38, 41, 42, 43, 54, 53, 52, 51}; //giờ Năm phút
const int t_10[]  = {40, 39, 38, 47, 48, 49, 50, 54, 53, 52, 51}; //giờ mười phút
const int t_15[]  = {40, 39, 38, 47, 48, 49, 50, 62, 61, 60, 54, 53, 52, 51}; //giờ mười Lām phút
const int t_20[]  = {40, 39, 38, 44, 45, 46, 59, 58, 57, 56, 54, 53, 52, 51}; //giờ Hai mươi phút
const int t_25[]  = {40, 39, 38, 44, 45, 46, 62, 61, 60, 54, 53, 52, 51}; //giờ hai Lām phút
const int t_30[]  = {37, 36, 35, 34}; //rưỡi
const int t_35[]  = {40, 39, 38, 33, 32, 31, 44, 45, 46, 62, 61, 60, 54, 53, 52, 51}; //giờ kém hai Lām phút
const int t_40[]  = {40, 39, 38, 33, 32, 31, 44, 45, 46, 59, 58, 57, 56, 54, 53, 52, 51}; //giờ kém hai mươi phút
const int t_45[]  = {40, 39, 38, 33, 32, 31, 47, 48, 49, 50, 62, 61, 60, 54, 53, 52, 51}; //giờ kém mười Lām phút
const int t_50[]  = {40, 39, 38, 33, 32, 31, 47, 48, 49, 50, 54, 53, 52, 51}; //giờ kém mười phút
const int t_55[]  = {40, 39, 38, 33, 32, 31, 41, 42, 43, 54, 53, 52, 51}; //giờ kém nām phút

ledLetters minuteWord[] = {
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
const int h_itis[]  = { 0 }; //c
const int h_01[]    = { 7, 8, 9 }; //c
const int h_02[]    = { 14, 13, 12 }; //c
const int h_03[]    = { 10, 11 }; //c
const int h_04[]    = { 28, 29, 30 }; //c
const int h_05[]    = { 20, 19, 18 }; //c
const int h_06[]    = { 17, 16, 15 }; //c
const int h_07[]    = { 25, 26, 27 }; //c
const int h_08[]    = { 4, 5, 6 }; //c
const int h_09[]    = { 21, 22, 23, 24 }; //c
const int h_10[]    = { 0, 1, 2, 3, 7, 8, 9 }; //c
const int h_11[]    = { 0, 1, 2, 3, 7, 8, 9 }; //c
const int h_12[]    = { 0, 1, 2, 3, 14, 13, 12 }; //c

ledLetters hourWord[] = {
  {sizeof(h_itis) / sizeof(h_itis[0]), h_itis},
  {sizeof(h_01) / sizeof(h_01[0]), h_01},
  {sizeof(h_02) / sizeof(h_02[0]), h_02},
  {sizeof(h_03) / sizeof(h_03[0]), h_03},
  {sizeof(h_04) / sizeof(h_04[0]), h_04},
  {sizeof(h_05) / sizeof(h_05[0]), h_05},
  {sizeof(h_06) / sizeof(h_06[0]), h_06},
  {sizeof(h_07) / sizeof(h_07[0]), h_07},
  {sizeof(h_08) / sizeof(h_08[0]), h_08},
  {sizeof(h_09) / sizeof(h_09[0]), h_09},
  {sizeof(h_10) / sizeof(h_10[0]), h_10},
  {sizeof(h_11) / sizeof(h_11[0]), h_11},
  {sizeof(h_12) / sizeof(h_12[0]), h_12},
};

void textToWords(ledLetters words)
{
  for(int x = 0; x < words.length; x++)
  {
    led_activate(words.values[x]);
  }
}

void minutesToWords(int minutes)
{
  if( minutes < 5){
    textToWords(minuteWord[0]);
  }
  else if( minutes >= 5 && minutes < 10){
    textToWords(minuteWord[1]);
  }
  else if( minutes >= 10 && minutes < 15){
    textToWords(minuteWord[2]);
  }
  else if( minutes >= 15 && minutes < 20){
    textToWords(minuteWord[3]);
  }
  else if( minutes >= 20 && minutes < 25){
    textToWords(minuteWord[4]);
  }
  else if( minutes >= 25 && minutes < 30){
    textToWords(minuteWord[5]);
  }
  else if( minutes >= 30 && minutes < 35){
    textToWords(minuteWord[6]);
  }
  else if( minutes >= 35 && minutes < 40){
    textToWords(minuteWord[7]);
  }
  else if( minutes >= 40 && minutes < 45){
    textToWords(minuteWord[8]);
  }
  else if( minutes >= 45 && minutes < 50){
    textToWords(minuteWord[9]);
  }
  else if( minutes >= 50 && minutes < 55){
    textToWords(minuteWord[10]);
  }
  else if( minutes >= 55){
    textToWords(minuteWord[11]);
  }
}

void hourOffset(int hours, int minutes)
{
  if(minutes >= 35)
  {
    hours += 1;
  }
  if(hours == 0 || hours == 24 || hours == 12)
  {
    textToWords(hourWord[12]);
  } else if(hours == 1 || hours == 13)
  {
    textToWords(hourWord[1]);
  } else if(hours == 2 || hours == 14)
  {
    textToWords(hourWord[2]);
  } else if(hours == 3 || hours == 15)
  {
    textToWords(hourWord[3]);
  } else if(hours == 4 || hours == 16)
  {
    textToWords(hourWord[4]);
  } else if(hours == 5 || hours == 17)
  {
    textToWords(hourWord[5]);
  } else if(hours == 6 || hours == 18)
  {
    textToWords(hourWord[6]);
  } else if(hours == 7 || hours == 19)
  {
    textToWords(hourWord[7]);
  } else if(hours == 8 || hours == 20)
  {
    textToWords(hourWord[8]);
  } else if(hours == 9 || hours == 21)
  {
    textToWords(hourWord[9]);
  } else if(hours == 10 || hours == 22)
  {
    textToWords(hourWord[10]);
  } else if(hours == 11 || hours == 23)
  {
    textToWords(hourWord[11]);
  }
}

void timeToText(int hours, int minutes){

  Serial.print("hours:");
  Serial.print(hours);
  Serial.print(" min:");
  Serial.println(minutes);

  hourOffset(hours, minutes);
  minutesToWords(minutes);
}
