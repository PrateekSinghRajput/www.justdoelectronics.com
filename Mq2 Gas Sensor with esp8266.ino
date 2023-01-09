#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define BLYNK_TEMPLATE_ID "TMPLGTWHBe3U"
#define BLYNK_DEVICE_NAME "IoT Application"
#define BLYNK_AUTH_TOKEN "uSGu_jMyZNAB9dy9xwOtlLCd4tApOD"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "xxxxxxxxxx";  
char pass[] = "xxxxxxxxxx"; 

BlynkTimer timer;

#define MQ2 A0
#define GREEN D5
#define RED D6
#define buzzer D7
int MQ2_Val = 0;

WidgetLED led1(V1);
WidgetLED led2(V3);


void setup()  
{
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  Welcome To");
  lcd.setCursor(0, 1);
  lcd.print("JustDoElectronic");
  delay(3000);
  lcd.clear();
  Serial.begin(9600);  
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  //justdoelectronics
  Blynk.begin(auth, ssid, pass); 
  delay(2000);
  timer.setInterval(1000L, mySensor);
}

void loop()  
{
  Blynk.run();
  timer.run();
}

void mySensor() {
  MQ2_Val = analogRead(MQ2);
  for (int x = 0; x < 100; x++) {
    MQ2_Val = MQ2_Val + analogRead(MQ2);
  }
  MQ2_Val = MQ2_Val / 100.0;

  Blynk.virtualWrite(V0, MQ2_Val);
  Blynk.virtualWrite(V2, MQ2_Val);

  if (MQ2_Val > 900) {
    Blynk.notify("Gas Detected!");
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
    digitalWrite(buzzer, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("     Alert. ");
    Blynk.email("test@gmail.com", "Alert", "Gas Leakage Detected!");
    Blynk.logEvent("gas_alert", "Gas Leakage Detected");
    led1.on();
    led2.off();
  }

  else {
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
    digitalWrite(buzzer, LOW);
    lcd.setCursor(0, 1);
    lcd.print("     Normal  ");
    led1.off();
    led2.on();
  }
  Serial.print("MQ2 Level: ");
  lcd.setCursor(0, 0);
  lcd.print("Gas Level: ");
  lcd.print(MQ2_Val);
  Serial.println(MQ2_Val);
}