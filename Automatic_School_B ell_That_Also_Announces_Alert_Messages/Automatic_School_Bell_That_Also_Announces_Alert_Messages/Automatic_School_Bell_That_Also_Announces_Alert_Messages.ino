
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;
const int RlyPin =  11;      // the number of the RELAY pin
const int P_LPin =  12;      // the number of the ISD1820 module
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {
  pinMode(RlyPin, OUTPUT);// initialize the RELAY pin as an output:
  pinMode(P_LPin, OUTPUT);// initialize the ISD1820 module as an output:
  while (!Serial); // for Leonardo/Micro/Zero
  Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
 rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // july 21, 2021 at 10:00 am )
//rtc.adjust(DateTime(2021, 7, 21, 10, 0, 0));
  }
}

void loop () {
  DateTime now = rtc.now();
   
  if (now.hour() == 9 && now.minute() == 30 && now.second() <=15 ) ////////////////1 session start 
  {
    // turn ISD1820 module/relay on:
    digitalWrite(RlyPin, HIGH);
    delay(5000);// 5 sec dealy  for relay ON.
    digitalWrite(RlyPin, LOW);
    digitalWrite(P_LPin, HIGH);
    delay(17000);// delay provided  to keep the pulse HIGH and to make the  ISD1820 module play back till tne end of message
  } else {
    // turn ISD1820 module/relay off:
    digitalWrite(RlyPin, LOW);
    digitalWrite(P_LPin, LOW);
  }
  
   if (now.hour() == 10 && now.minute() == 00 && now.second() <=15 )//////////////////////   1 session end, 2 session start 
  {
    // turn ISD1820 module/relay  on:
    digitalWrite(RlyPin, HIGH);
    delay(5000);
    digitalWrite(RlyPin, LOW);
    digitalWrite(P_LPin, HIGH);
    delay(17000);
  } else {
    // turn ISD1820 module/relay off:
    digitalWrite(RlyPin, LOW);
    digitalWrite(P_LPin, LOW);
  }
  
 if (now.hour() == 10 && now.minute() == 30 && now.second() <=15 )//////////////////////    session end, break start 
  {
    // turn ISD1820 module/relay on:
    digitalWrite(RlyPin, HIGH);
    delay(5000);
    digitalWrite(RlyPin, LOW);
    digitalWrite(P_LPin, HIGH);
    delay(17000);
  } else {
    // turn ISD1820 module/relay off:
    digitalWrite(RlyPin, LOW);
    digitalWrite(P_LPin, LOW);
  }
  
 if (now.hour() == 10 && now.minute() == 40 && now.second() <=15 )//////////////////////   break end, 3 session start 
  {
   // turn ISD1820 module/relay on:
    digitalWrite(RlyPin, HIGH);
    delay(5000);
    digitalWrite(RlyPin, LOW);
    digitalWrite(P_LPin, HIGH);
    delay(17000);
  } else {
    // turn ISD1820 module/relay off:
    digitalWrite(RlyPin, LOW);
    digitalWrite(P_LPin, LOW);
  }
  
   if (now.hour() == 11 && now.minute() == 10 && now.second() <=30 )//////////////////////   3 session end, 4 session start 
  {
    // turn ISD1820 module/relay on:
    digitalWrite(RlyPin, HIGH);
    delay(5000);
    digitalWrite(RlyPin, LOW);
    digitalWrite(P_LPin, HIGH);
    delay(17000);
  } else {
    // turn ISD1820 module /relayoff:
    digitalWrite(RlyPin, LOW);
    digitalWrite(P_LPin, LOW);
  }
  
   if (now.hour() == 11 && now.minute() == 40 && now.second() <=30 )//////////////////////   4 session end,  
  {
    // turn ISD1820 module/relay on:
    digitalWrite(RlyPin, HIGH);
    delay(5000);
    digitalWrite(RlyPin, LOW);
    digitalWrite(P_LPin, HIGH);
    delay(17000);
  } else {
    // turn ISD1820 module/relay off:
    digitalWrite(RlyPin, LOW);
    digitalWrite(P_LPin, LOW);
  }

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  delay(1000);
}
