#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 rf(9, 8); //CE, CSN pins

const byte addresses[2][6] = {"00249", "00367"}; //Master & Slave addresses

void setup() {
  Serial.begin(9600);
  Serial.println("setup/nUÇAK");

  rf.begin();
  rf.openWritingPipe(addresses[0]);
  rf.openReadingPipe(1, addresses[1]);

  rf.setPALevel(RF24_PA_MIN);
}

void loop() {
  String message = "1234567890123456";
  
  getMessage();
  sendMessage(message);
}

void getMessage() {
  rf.startListening();

  if(rf.available()) {
    char input[17] = {0};
    rf.read(&input, sizeof(input));

    Serial.println("Message : \n" + (String)input);
  }
  delay(5);
}

void sendMessage(String mess) {
  char charBuffer[17];

  rf.stopListening();

  mess.toCharArray(charBuffer, 17);
  rf.write(&charBuffer, sizeof(charBuffer));
  Serial.println("Sended : " + mess);
  delay(5);
}
