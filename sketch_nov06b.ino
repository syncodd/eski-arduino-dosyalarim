#include <Servo.h>

Servo s;

void setup() {
  
  s.attach(8);
  s.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  s.write(90);
}
