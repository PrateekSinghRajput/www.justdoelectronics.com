
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define rxPin 2
#define txPin 3
SoftwareSerial sim800(rxPin, txPin);

#define led 13
#define buzzer 6


int sensorPin = A0;
int read_value;

void setup() {
  sim800.begin(115200);
  Serial.println("SIM800L initialize");
  sim800.println("AT");
  lcd.init();
  lcd.backlight();
  pinMode(sensorPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("   WELCOME To   ");
  lcd.setCursor(0, 1);
  lcd.print("  OUR Project ");
  delay(2000);
}

void loop() {
  read_value = digitalRead(sensorPin);

  if (read_value == 1) {
    lcd.setCursor(0, 0);
    lcd.print("   Not  Flame   ");
    lcd.setCursor(0, 1);
    lcd.print(".....Normal.....");
    digitalWrite(buzzer, LOW);
    digitalWrite(led, HIGH);
    delay(2000);

  } else {
    lcd.setCursor(0, 0);
    lcd.print("Fire is Detected");
    lcd.setCursor(0, 1);
    lcd.print("Alert....!!!    ");
    digitalWrite(buzzer, HIGH);
    digitalWrite(led, LOW);
    delay(200);
    sim800.println("AT+CMGF=1");
    delay(1000);
    sim800.println("AT+CMGS=\"+9188305848xx\"\r");
    delay(1000);
    sim800.println("SMS For Fire Alert");
    delay(100);
    sim800.println((char)26);
    delay(1000);
    Serial.println("SMS Send");
  }
}
