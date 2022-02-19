#include<VirtualWire.h>

void setup()
{
 Serial.begin(9600);
 Serial.println("setup");
 
 //recieving
 vw_set_rx_pin(2);
 vw_set_ptt_inverted(true);
 vw_setup(2000);
 vw_rx_start();
}

void loop()
{
 uint8_t buf[VW_MAX_MESSAGE_LEN];
   uint8_t buflen = VW_MAX_MESSAGE_LEN;

   if (vw_get_message(buf, &buflen)) // Non-blocking
   {
int i;

       //digitalWrite(13, HIGH); // Flash a light to show received good message
// Message with a good checksum received, print it.
Serial.print("Got: ");

for (i = 0; i < buflen; i++)
{
   Serial.print(buf, HEX);
   Serial.print(' ');
}
Serial.println();
       digitalWrite(13, LOW);
   }
}
