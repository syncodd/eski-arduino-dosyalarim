//Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Define pins & variables etc.
#define JS1X      A0
#define JS1Y      A1
#define JS2X      A2
#define JS2Y      A3

int j1x, j1y, j2x, j2y;

RF24 rf(9, 8); //CE, CSN pins

const byte addresses[2][6] = {"00249", "00367"}; //Master & Slave addresses

void setup() {
  //Start serial communication
  Serial.begin(9600);
  Serial.println("setup\nKUMANDA");

  //Define pinModes
  pinMode(JS1X, INPUT);
  pinMode(JS1Y, INPUT);
  pinMode(JS2X, INPUT);
  pinMode(JS2Y, INPUT);

  //Open pipe for both side communication
  rf.begin();
  rf.openWritingPipe(addresses[1]);
  rf.openReadingPipe(1, addresses[0]);

  rf.setPALevel(RF24_PA_MIN);
}

void loop() {
  //Read analog(Joystick) inputs
  j1x = analogRead(JS1X) + 3378;
  j1y = analogRead(JS1Y) + 4026;
  j2x = analogRead(JS2X) + 2298;
  j2y = analogRead(JS2Y) + 3928;

  //Combine all inputs and make a single message
  String message = (String)j1x + j1y + j2x + j2y;

  sendMessage(message);
  getMessage();
  Serial.println("Sending...");
}

void sendMessage(String mess) {
  char charBuffer[17];

  //Make the rf a transmitter
  rf.stopListening(); 

  //Send message
  mess.toCharArray(charBuffer, 17);
  rf.write(&charBuffer, sizeof(charBuffer));
  Serial.println("Sended : " + mess);
  delay(5);
}

//GPS KOMUTUNA GÖRE AŞAĞIYI DÜZENLE!

void getMessage() {
  //Make the rf a reciever
  rf.startListening();

  //If rf get message read it
  if(rf.available()) {
    char input[17] = {0};
    rf.read(&input, sizeof(input));

    Serial.println("Message : \n" + (String)input);
  }
  delay(5);
}
