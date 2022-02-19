#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define JS1X      A0
#define JS1Y      A1
#define JS2X      A2
#define JS2Y      A3

int j1x, j1y, j2x, j2y;

RF24 radio(9, 8);  // CE, CSN

const byte address[6] = "00249"; //address

void setup() {
  //Transmitter
  radio.begin();
  radio.openWritingPipe(address);
  radio.stopListening();

  //pinModes
  pinMode(JS1X, INPUT);
  pinMode(JS1Y, INPUT);
  pinMode(JS2X, INPUT);
  pinMode(JS2Y, INPUT);

  //Serial Begin
  Serial.begin(9600);
  Serial.println("setup - Transmitter");
}

void loop() {
  //Joystick Inputs
  j1x = analogRead(JS1X) + 3378;
  j1y = analogRead(JS1Y) + 4026;
  j2x = analogRead(JS2X) + 2298;
  j2y = analogRead(JS2Y) + 3928;

  String out = (String)j1x + j1y + j2x + j2y;
  char charBuf[17];

  Serial.println(out);
  
  out.toCharArray(charBuf, 17);
  radio.write(&charBuf, sizeof(charBuf));
  delay(100);
}
