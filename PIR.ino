#include <Servo.h>

Servo servo;
int girdi, aci;

void setup() {
  pinMode(8, INPUT);  
  servo.attach(9);
  
  Serial.begin(9600);
}

void loop() {
  girdi = digitalRead(8);
  if(girdi == 1) {
    aci = 180;
  } else if(girdi == 0) {
    aci = 0;
  }
  Serial.println(girdi);
  servo.write(aci);
}
