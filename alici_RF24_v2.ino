#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

//define Servo pins
#define SB        7
#define SF        3
#define SU        4
#define ESCPin    10

RF24 radio(9, 8);  // CE, CSN

//Servos
Servo servoB, servoF, servoU, ESC;

//RF
const byte address[6] = "00249"; //address

//var
String mess;
bool firstStart = false;
bool start = false;
bool locked = true;
int coolDown, radioAvailable;
int j1x, j1y, j2x, j2y;

void setup() {
  //serialBegin
  while (!Serial);
    Serial.begin(9600);
    Serial.println("setup");

  //Reciever
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();

  //Servos
  servoB.attach(SB);
  servoF.attach(SF);
  servoU.attach(SU);
  
  ESC.attach(ESCPin, 1000, 2000);
  
  servoB.write(90);
  servoF.write(90);
  servoU.write(90);
  
  firstStart = false;
  start = false;
  locked = true;
}

void loop() {
  //Get Message
  if(radio.available()) {
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    //Serial.println(text);

    mess = (String)text;
    
    j1x = map(((String(mess[0]) + String(mess[1]) + String(mess[2]) + String(mess[3])).toInt() - 3378), 0, 1023, 0, 180);
    j1y = map(((String(mess[4]) + String(mess[5]) + String(mess[6]) + String(mess[7])).toInt() - 4026), 0, 1023, 0, 180);
    j2x = map(((String(mess[8]) + String(mess[9]) + String(mess[10]) + String(mess[11])).toInt() - 2298), 0 , 1023, 0, 180);
    j2y = map(((String(mess[12]) + String(mess[13]) + String(mess[14]) + String(mess[15])).toInt() - 3928), 0, 1023, 0, 180);
  
    radioAvailable-=150;
    if(radioAvailable < 0) {
      radioAvailable = 0;
    }
    Serial.println(radioAvailable);
  }
  
  if(radio.available() == false) {
    radioAvailable++;
    if(radioAvailable > 110) {
      locked = true;
      start = false;
      j1x = 90;
      //j1y = 11;
      j2x = 90;
      j2y = 90;
    
      servoMove(j1x, j2x);
      servoBack(j2y);
      Engine(j1y);
      Serial.println(radioAvailable);
      killEngine();
      Serial.println("DEATH!");
    } else {
      j1x = map(((String(mess[0]) + String(mess[1]) + String(mess[2]) + String(mess[3])).toInt() - 3378), 0, 1023, 0, 180);
      j1y = map(((String(mess[4]) + String(mess[5]) + String(mess[6]) + String(mess[7])).toInt() - 4026), 0, 1023, 0, 180);
      j2x = map(((String(mess[8]) + String(mess[9]) + String(mess[10]) + String(mess[11])).toInt() - 2298), 0 , 1023, 0, 180);
      j2y = map(((String(mess[12]) + String(mess[13]) + String(mess[14]) + String(mess[15])).toInt() - 3928), 0, 1023, 0, 180);
      //radioAvailable--;
      Serial.println((String)j1x + j1y + j2x + j2y);
    }
  }
  
  //Inputs to Int
  
  if(coolDown < 3) {
    Serial.println("CoolDown " + (String)(3-coolDown) + "!");
    coolDown++;
    delay(1000);
    if(coolDown == 3) {
      Serial.println("CoolDown END!");
    }
  } else {
    if(j1y <= 9 && firstStart == false) {
      Serial.println("DOWN!");
      start = false;
      firstStart = true;
    }

    if(j1y >= 9 && firstStart == true && start == false) {
      Serial.println("UP!");
      start = true;
      locked = false;
    }
  
    if(firstStart == true && start == true && locked == false) {
      Serial.println(String(j1x) + " " + String(j1y) + " " + String(j2x) + " " + String(j2y));
      
      servoMove(j1x, j2x);
      servoBack(j2y);
      Engine(j1y);
    }
  }
}

void servoBack(int value) {
  servoB.write(value);
  Serial.println("UNLOCKED! J1Y : " + (String)j1y);
}

void servoMove(int value1, int value2) {
  servoU.write(180-value1);
  servoF.write(value2);
}

void killEngine() {
  for(j1y; j1y > 0; j1y--) {
    Serial.println(j1y);
    delay(100);
    ESC.write(j1y);
  }
  locked = true;
  start = false;
  firstStart = false;
}
void Engine(int value) {
  ESC.write(value);
}
