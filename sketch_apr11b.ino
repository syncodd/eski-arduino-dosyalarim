#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
pinMode(6,OUTPUT);
digitalWrite(6,HIGH);

lcd.begin(16,2);
lcd.setCursor(1,0);

delay(100);
lcd.print("helaaaaaa");
pinMode(6,OUTPUT);
digitalWrite(6,HIGH);
lcd.setCursor(2,0);
delay(100);
lcd.print("aaaaa");
}

void loop() {
  digitalWrite(6,HIGH);
}
