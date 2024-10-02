//Prateek
//wwwjustdoelectronics.com

#include <Filters.h> 
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 =8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
float testFrequency = 50;  
 
int Sensor = 0; 
int relay = 6;  
int yellow = 5; 
int green = 4;  
 
float intercept = 0.7; 
float slope = 0.04; 
float current_Volts; 
 
unsigned long printPeriod = 1000; 
unsigned long previousMillis = 0;
 
 
void setup()
{
 lcd.begin(16, 2);
  pinMode(relay, OUTPUT);
    pinMode(yellow, OUTPUT);
      pinMode(green, OUTPUT);
  lcd.print("Voltage:");
  delay(1000);
 
}
 
void loop()
{
  RunningStatistics inputStats;             
 
  while ( true )
  {
    Sensor = analogRead(A0); 
    inputStats.input(Sensor);  
 
    if ((unsigned long)(millis() - previousMillis) >= printPeriod)
    {
      previousMillis = millis();   
 
      current_Volts = intercept + slope * inputStats.sigma(); 
      current_Volts = current_Volts * (40.3231);             
 
      lcd.setCursor(9, 0);
      lcd.print(current_Volts);
      
      lcd.print("V");
    }

    if ( (current_Volts > 0)  &&  (current_Volts < 190) )
  {
    lcd.setCursor(0, 1);
    lcd.print("Under Voltage");
    digitalWrite(relay, LOW);
     digitalWrite(yellow, LOW);
      digitalWrite(green, HIGH);
  }
 
  if ( (current_Volts >= 190)  &&  (current_Volts <= 220) )
  {
    lcd.setCursor(0, 1);
    lcd.print("Normal Voltage");
    digitalWrite(relay, HIGH);
    digitalWrite(yellow, LOW);
      digitalWrite(green, LOW);
  }
 
  if ( current_Volts > 220 )
  {
    lcd.setCursor(0, 1);
    lcd.print("Over Voltage");
    digitalWrite(relay, LOW);
    digitalWrite(yellow, HIGH);
      digitalWrite(green, LOW);
  }
  }
}