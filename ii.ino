#include <SPI.h>

#define pin 2

byte output, input;

void setup() {

  Serial.begin(9600);

  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  
  SPI.begin();
}

void loop() {

  while(Serial.available() > 0) {
    output = Serial.read();
    input = spi(output);
    Serial.write(input);
  }

}

byte spi(byte dout) {
  byte din;
  digitalWrite(pin, LOW);
  delay(1);
  din = SPI.transfer(dout);
  digitalWrite(pin, HIGH);
  return din;
}
