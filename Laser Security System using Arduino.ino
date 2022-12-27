
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);




const int ldrPin = A0;
const int ledPin1 = 3;
const int buzzer = 4;



int ldrValue = 0;
int ldrlevel1 = 400;



void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Welcome To ");
    lcd.setCursor(0, 1);
  lcd.print("  Our Project ");
  pinMode(ledPin1, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  ldrValue = analogRead(ldrPin);
  Serial.println(ldrValue);
  if (ldrValue < ldrlevel1) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(buzzer, HIGH);
      lcd.setCursor(0, 0);
  lcd.print(" Laser Security ");
    lcd.setCursor(0,1);
  lcd.print(" Alarm Activated");
  } else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(buzzer, LOW);
     lcd.setCursor(0, 0);
  lcd.print(" Laser Security ");
    lcd.setCursor(0,1);
  lcd.print(" Alarm Normal...");
  }
}
