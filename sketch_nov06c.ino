#include <Servo.h>
Servo s;

void setup() {
  s.attach(8);
}

void loop() {
  s.write(0);
  delay(3000);
  s.write(90);
  delay(3000);
  s.write(180);
  delay(3000);
}
