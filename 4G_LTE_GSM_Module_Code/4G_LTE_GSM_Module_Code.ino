//Prateek
//www.justdoelectronics.com

#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Wire.h>
SoftwareSerial mySerial(2, 3);
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int reedPin = 5;
const int ledPin = 13;
const int buzzer = 6;
bool switchState = HIGH;

void setup() {
  mySerial.begin(115200);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(reedPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(ledPin, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Welcome To  ");
  lcd.setCursor(0, 1);
  lcd.print("justdoelectronics");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DESIGN By :-");
  lcd.setCursor(0, 1);
  lcd.print("PRATEEK");
  delay(3000);
  lcd.clear();
}

void loop() {
  switchState = digitalRead(reedPin);
  if (switchState == HIGH) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzer, LOW);
    Serial.println("Reed Switch is Closed. LED is ON");
    //lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Switch Open");
    lcd.setCursor(0, 1);
    lcd.print("Is Normal");
    lcd.setCursor(10, 3);
    lcd.print("........");

  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzer, HIGH);
    Serial.println("Reed Switch Open. LED is OFF");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Switch Closed");
    lcd.setCursor(0, 1);
    lcd.print("SMS Sent");


    Serial.println("SMS Will send");
    mySerial.println("AT+CMGF=1");
    delay(1000);
    mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r");
    delay(1000);
    mySerial.println("Push Butoon Is Press");
    delay(100);
    mySerial.println((char)26);
    delay(1000);
  }
}
