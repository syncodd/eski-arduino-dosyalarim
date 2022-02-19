#include <PinChangeInterruptHandler.h>
#include <RFReceiver.h>
#include <Servo.h>

Servo ESCMotor; // create servo object to control the ESC
Servo LWing;
Servo MWing;
Servo RWing;
int potValue;  // value from the analog pin
bool start = false;
bool firstStart = false;
bool UD, LR;

// Listen on digital pin 2
RFReceiver receiver(2);

void setup() {
  Serial.begin(9600);
  receiver.begin();

  // Attach the ESC on pin 9
  ESCMotor.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds)
  LWing.attach(11);
  MWing.attach(12);
  RWing.attach(13);
  
  Serial.println("Setup");
}

void loop() {
  char msg[MAX_PACKAGE_SIZE];
  byte senderId = 0;
  byte packageId = 0;
  byte len = receiver.recvPackage((byte *)msg, &senderId, &packageId);

  Serial.println("");
  Serial.print("Package: ");
  Serial.println(packageId);
  Serial.print("Sender: ");
  Serial.println(senderId);
  Serial.print("Message: ");
  Serial.println(msg);

  int j1x = (String(msg[0]) +  String(msg[1]) +  String(msg[2]) +  String(msg[3])).toInt() - 2000;
  int j1y = (String(msg[4]) +  String(msg[5]) +  String(msg[6]) +  String(msg[7])).toInt() - 2000;
  int j2x = (String(msg[8]) +  String(msg[9]) +  String(msg[10]) + String(msg[11])).toInt() - 2000;
  int j2y = (String(msg[12]) + String(msg[13]) + String(msg[14]) + String(msg[15])).toInt() - 2000;

  j1x = map(j1x, 0, 1023, 0, 180)-29;
  j1y = map(j1y, 0, 1023, 0, 180)-22;
  j2x = map(j2x, 0, 1023, 0, 180)-33;
  j2y = 180-map(j2y, 0, 1023, 0, 180)+29;
  
  Serial.print("J1X : ");
  Serial.println(j1x);
  Serial.print("J1Y : ");
  Serial.println(j1y);
  Serial.print("J2X : ");
  Serial.println(j2x);
  Serial.print("J2Y : ");
  Serial.println(j2y);

  if(j1y <= 8.79) {
    start = false;
    firstStart = true;  
  } else if(j1y >= 9 && firstStart == true) {
    start = true;
  }

  if((80 < j2x < 100) && (80 > j2y or 100 < j2y)) {
    UD = true;
    LR = false;
  } else if((80 < j2y < 100) && (80 > j2x or 100 < j2x)) {
    UD = false;
    LR = true;
  }
  
  if(start == true) {
    Engine(j1y);
    ServoM(j1x);
    if(LR == true) {
      Movement(j2x, j2x);
    } else if (UD == true) {
      Movement(j2y, 180-j2y);
    }
  }
}

void Engine(int j1y_esc) {
  ESCMotor.write(j1y_esc);    // Send the signal to the ESC
}

void Movement(int j_moveL, int j_moveR) {
  LWing.write(j_moveL);
  RWing.write(j_moveR);
}

void ServoM(int j1x_m) {
  MWing.write(j1x_m);
}
