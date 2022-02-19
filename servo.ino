#include <Servo.h>

Servo s;

int i,d = 0;

void setup() {  
  s.attach(8);  
  s.write(d);

}

void loop() {
  for(i=0;i<10;i++) {
    if(d == 180) {
      d=0;
    } else {
      d+=10;
    }
    s.write(d);
    delay(100);
  }
}
