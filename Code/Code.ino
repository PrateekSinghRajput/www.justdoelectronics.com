
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int enA = 9;
int in1 = 8;
int in2 = 7;

int buttonC = 3;
int buttonA = 4;

bool buttonCState = false;
bool buttonAState = false;

int motorSpeed = 255;

void setup() {

  lcd.init();
  lcd.backlight();
  delay(2000);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(buttonC, INPUT_PULLUP);
  pinMode(buttonA, INPUT_PULLUP);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void loop() {

  buttonCState = digitalRead(buttonC);
  buttonAState = digitalRead(buttonA);

  if (buttonCState == LOW) {
    lcd.setCursor(0, 0);
    lcd.print("  Forward ");
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, motorSpeed);
  } else if (buttonAState == LOW) {
    lcd.setCursor(0, 0);
    lcd.print("  Backward ");
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, motorSpeed);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(enA, 0);
    lcd.setCursor(0, 0);
    lcd.print("  Robot Gripper ");
    lcd.setCursor(4, 1);
    lcd.print("Control");
  }
  delay(700);
}