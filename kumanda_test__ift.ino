#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define led 2
RF24 radio(9, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
String input;
void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00001
  radio.openReadingPipe(1, addresses[0]); // 00002
  radio.setPALevel(RF24_PA_MIN);
}
void loop() {
  delay(5);
  radio.stopListening();
  String joyDeger = "Gönder";
  Serial.println(joyDeger );
  radio.write(&joyDeger , sizeof(joyDeger ));
  delay(5);
  radio.startListening();
  while (!radio.available());
  radio.read(&input, sizeof(input));
  Serial.println((String)input);
}
