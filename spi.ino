#include <SPI.h>

#define pin 2

int pls = 100;
byte state = LOW;

void setup() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);

  Serial.begin(9600);

  SPI.begin();
}

void loop() {
  
  String mess1;
  mess1 = messageToByte("L");
  sendMessage(mess1);
  delay(1000);  
}

void sendMessage(String message) {
  //Serial.println("send message " + message);
  
  String out = byteTurn(message);

  for(int i = 0; i < out.length(); i++) {
    String state;
    state = out[i];
    Serial.print(String(state));

    if(state == "a") {
      send00();
      delay(25);
    } else if(state == "b") {
      send01();
      delay(25);
    } else if(state == "c") {
      send10();
      delay(25);
    } else if(state == "d") {
      send11();
      delay(25);
    }
  }
  Serial.println();
  
}

String byteTurn(String message) {
  //Serial.println("byte turn " + message);

  String outMessage, bm, state;

  for(int i = 0; i < message.length(); i+=2) {

    bm = "" + String(message[i]) + String(message[i+1]);
    outMessage = outMessage + message[i] + message[i+1];
    //Serial.println(outMessage);
    //Serial.println(bm);

    if(bm == "00") {
      state = state + "a";
    } else if(bm == "01") {
      state = state + "b";
    } else if(bm == "10") {
      state = state + "c";
    } else if(bm == "11") {
      state = state + "d";
    }
  }
  
  return state;
  //Serial.println(outMessage);
}
String messageToByte(String message) {

  String byteString;
  byte bytes;
  
  for(int i=0; i<message.length(); i++){

   char chr = message.charAt(i);
    
   for(int i=7; i>=0; i--){
     bytes = bitRead(chr,i);
     byteString = byteString + String(bytes);
     //Serial.print(bytes, BIN); 
     //Serial.print(byteString);     
   }
   
   //Serial.println("");
   
  }
  return byteString;
}
void send0() {
  state = !state;
  digitalWrite(pin, state);
  delayMicroseconds(pls << 1);
}

void send1() {
  digitalWrite(pin, state);
  delayMicroseconds(pls);
  digitalWrite(pin, !state);
  delayMicroseconds(pls);
}

void send01() {
  send0();
  send1();
}

void send10() {
  send1();
  delay(10);
  send0();
}

void send00() {
  send0();
  delayMicroseconds(pls);
}

void send11() {
  send1();
  send1();
}
