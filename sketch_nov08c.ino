#include <PinChangeInterruptHandler.h>
#include <RFReceiver.h>

RFReceiver receiver(2);

void setup() {
  Serial.begin(9600);
  receiver.begin();
  Serial.println("set"); 
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

}
