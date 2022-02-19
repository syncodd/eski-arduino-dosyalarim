#include <VirtualWire.h>
 
int RF_TX_PIN = 4;
 
void setup()
{
  vw_set_tx_pin(RF_TX_PIN); // Setup transmit pin
  vw_setup(2000); // Transmission speed in bits per second.
}
 
void loop()
{
  const char *msg = "1";
  vw_send(msg[0], strlen(msg));  // Send 'hello' every 400ms.
  delay(400);
 
}
