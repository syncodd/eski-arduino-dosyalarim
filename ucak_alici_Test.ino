#include <PinChangeInterruptHandler.h>
#include <RFReceiver.h>

// Listen on digital pin 2
RFReceiver receiver(2);

void setup() {
  Serial.begin(9600);
  receiver.begin();
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
  Serial.print("J1X : ");
  Serial.println(j1x);
  Serial.print("J1Y : ");
  Serial.println(j1y);
  Serial.print("J2X : ");
  Serial.println(j2x);
  Serial.print("J2Y : ");
  Serial.println(j2y);
}
