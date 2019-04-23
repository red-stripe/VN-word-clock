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
00  gio
05  gio Nam
10  gio muoi
15  gio muoi lam
20  gio hai muói
25  gio hai muói lam
30  ruoi
35  gio kem hai lam
40 gio kem hai muói
45 gio kem muói lam
50 gio kem Muoi
55  gio kem nam
*/
const int t_00[]  = {46, 47, 48}; //c
const int t_05[]  = {46, 47, 48, 49, 50, 51}; //c
const int t_10[]  = {46, 47, 48, 63, 64, 65, 66}; //c
const int t_15[]  = {46, 47, 48, 55, 56, 57, 58, 69, 70, 71}; //c
const int t_20[]  = {46, 47, 48, 52, 53, 54, 55, 56, 57, 58}; //c
const int t_25[]  = {46, 47, 48, 52, 53, 54, 55, 56, 57, 58, 69, 70, 71}; //c
const int t_30[]  = {39, 40, 41, 42}; //c
const int t_35[]  = {46, 47, 48, 43, 44, 45, 52, 53, 54, 69, 70, 71, 59, 60, 61, 62}; //c
const int t_40[]  = {46, 47, 48, 43, 44, 45, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62}; //c
const int t_45[]  = {46, 47, 48, 43, 44, 45, 55, 56, 57, 58, 69, 70, 71, 59, 60, 61, 62}; //c
const int t_50[]  = {46, 47, 48, 43, 44, 45, 63, 64, 65, 66, 59, 60, 61, 62}; //c
const int t_55[]  = {46, 47, 48, 43, 44, 45, 49, 50, 51, 59, 60, 61, 62}; //c

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
const int h_itis[]  = { 0,  1,  2, 3, 4, 5, 6, 7 }; //c
const int h_01[]    = { 12, 13, 14 }; //c
const int h_02[]    = { 15, 16, 17 }; //c
const int h_03[]    = { 27, 28 }; //c
const int h_04[]    = { 24, 25, 26 }; //c
const int h_05[]    = { 21, 22, 23 }; //c
const int h_06[]    = { 18, 19, 20 }; //c
const int h_07[]    = { 29, 30, 31 }; //c
const int h_08[]    = { 32, 33, 34 }; //c
const int h_09[]    = { 35, 36, 37, 38 }; //c
const int h_10[]    = { 8, 9, 10, 11 }; //c
const int h_11[]    = { 8, 9, 10, 11, 12, 13, 14 }; //c
const int h_12[]    = { 8, 9, 10, 11, 15, 16, 17 }; //c

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

const int t_morning[]   = {72, 73, 74, 75}; //04-10 sáng
const int t_midday[]    = {77, 78, 79, 70}; //10-13 Trúa
const int t_afternoon[] = {82, 83, 84, 85, 86}; //13-18 chiêu
const int t_evening[]   = {94, 95, 96}; //18-22 tôi
const int t_late[]      = {87, 88, 89}; //22-04 dem

ledLetters timeOfDay[] = {
  {sizeof(t_morning) / sizeof(t_morning[0]), t_morning},
  {sizeof(t_midday) / sizeof(t_midday[0]), t_midday},
  {sizeof(t_afternoon) / sizeof(t_afternoon[0]), t_afternoon},
  {sizeof(t_evening) / sizeof(t_evening[0]), t_evening},
  {sizeof(t_late) / sizeof(t_late[0]), t_late},
};



void textToWords(ledLetters words)
{
  Serial.print("\t\t\t");
  for(int x = 0; x < words.length; x++)
  {
    led_activate(words.values[x]);
    Serial.print(words.values[x]);
    Serial.print(" ");
  }
  Serial.println();
}


void daySuffix(int hours)
{
  if(hours >= 4 && hours < 10)
  {
    textToWords(timeOfDay[0]);
    Serial.println("morning");
  } else if(hours >= 10 && hours < 13)
  {
    textToWords(timeOfDay[1]);
    Serial.println("midday");
  } else if(hours >= 13 && hours < 18)
  {
    textToWords(timeOfDay[2]);
    Serial.println("afternoon");
  } else if(hours >= 18 && hours < 22)
  {
    textToWords(timeOfDay[3]);
    Serial.println("evening");
  } else if(hours >= 22 || hours < 4)
  {
    textToWords(timeOfDay[4]);
    Serial.println("late");
  }
}

void hourOffset(int hours, int minutes)
{
  if(minutes >= 35)
  {
    hours = hours ++;
  }
  if(hours == 0 || hours == 24 || hours == 12)
  {
    textToWords(hourWord[12]);
//    Serial.print("12");
  } else if(hours == 1 || hours == 13)
  {
    textToWords(hourWord[1]);
  //  Serial.print("1");
  } else if(hours == 2 || hours == 14)
  {
    textToWords(hourWord[2]);
    Serial.print("2");
  } else if(hours == 3 || hours == 15)
  {
    textToWords(hourWord[3]);
  //  Serial.print("3");
  } else if(hours == 4 || hours == 16)
  {
    textToWords(hourWord[4]);
  //  Serial.print("4");
  } else if(hours == 5 || hours == 17)
  {
    textToWords(hourWord[5]);
  //  Serial.print("5");
  } else if(hours == 6 || hours == 18)
  {
    textToWords(hourWord[6]);
  //  Serial.print("6");
  } else if(hours == 7 || hours == 19)
  {
    textToWords(hourWord[7]);
  //  Serial.print("7");
  } else if(hours == 8 || hours == 20)
  {
    textToWords(hourWord[8]);
  //  Serial.print("8");
  } else if(hours == 9 || hours == 21)
  {
    textToWords(hourWord[9]);
  //  Serial.print("9");
  } else if(hours == 10 || hours == 22)
  {
    textToWords(hourWord[10]);
  //  Serial.print("10");
  } else if(hours == 11 || hours == 23)
  {
    textToWords(hourWord[11]);
  //  Serial.print("11");
  }

}

void timeToText(int hours, int minutes){
  Serial.print("hours:");
  Serial.print(hours);
  Serial.print(" min:");
  Serial.println(minutes);
  textToWords(hourWord[0]);
  hourOffset(hours, minutes);
  daySuffix(hours);

  if( minutes < 5){
    textToWords(minuteWord[0]);
//    Serial.print("giờ");
//    Serial.print(" (oclock) ");
  }
  else if( minutes >= 5 && minutes < 10){
    textToWords(minuteWord[1]);
//    Serial.print("năm");
//    Serial.print(" (5 past) ");
  }
  else if( minutes >= 10 && minutes < 15){
    textToWords(minuteWord[2]);
//    Serial.print("muoi");
//    Serial.print(" (10 past) ");
  }
  else if( minutes >= 15 && minutes < 20){
    textToWords(minuteWord[3]);
//    Serial.print("muoi ");
//    Serial.print("lam");
//    Serial.print(" (15 past) ");
  }
  else if( minutes >= 20 && minutes < 25){
    textToWords(minuteWord[4]);
//    Serial.print("giờ ");
//    Serial.print("hai ");
//    Serial.print("muoi");
  //  Serial.print(" (20 past) ");
  }
  else if( minutes >= 25 && minutes < 30){
    textToWords(minuteWord[5]);
//    Serial.print("giờ ");
//    Serial.print("hai ");
//    Serial.print("muoi ");
//    Serial.print("lam");
//    Serial.print(" (25 past) ");
  }
  else if( minutes >= 30 && minutes < 35){
    textToWords(minuteWord[6]);
//    Serial.print("ruoi");
  //  Serial.print(" (half past) ");
  }
  else if( minutes >= 35 && minutes < 40){
    textToWords(minuteWord[7]);
//    Serial.print("giờ ");
//    Serial.print("kem ");
//    Serial.print("hai ");
//    Serial.print("lam ");
//    Serial.print("phut");
  //  Serial.print(" (25 to) ");
  }
  else if( minutes >= 40 && minutes < 45){
    textToWords(minuteWord[8]);
//    Serial.print("giờ ");
//    Serial.print("kem ");
//    Serial.print("hai ");
  //  Serial.print("muoi ");
//    Serial.print("phut");
//    Serial.print(" (20 to) ");
  }
  else if( minutes >= 45 && minutes < 50){
    textToWords(minuteWord[9]);
//    Serial.print("giờ ");
//    Serial.print("kem ");
//    Serial.print("muoi ");
//    Serial.print("lam");
//    Serial.print(" (15 to) ");
  }
  else if( minutes >= 50 && minutes < 55){
    textToWords(minuteWord[10]);
//    Serial.print("giờ ");
//    Serial.print("kem ");
//    Serial.print("muoi ");
//    Serial.print("phut");
//    Serial.print(" (10 to) ");
  }
  else if( minutes >= 55){
    textToWords(minuteWord[11]);
//    Serial.print("giờ ");
//    Serial.print("kem ");
//    Serial.print("nam ");
//    Serial.print("phut");
//    Serial.print(" (5 to) ");
  }

Serial.println();
}
