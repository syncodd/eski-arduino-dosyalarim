#include <PinChangeInterruptHandler.h>
#include <RFReceiver.h>

RFReceiver receiver(6);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  receiver.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
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
}
