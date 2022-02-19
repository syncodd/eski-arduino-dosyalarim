#include<VirtualWire.h>

void setup()
{
 Serial.begin(9600);
 Serial.println("Start");
  
 vw_set_tx_pin(2);
 vw_set_ptt_inverted(true);
 vw_setup(2000);
}

void loop()
{
 const char *msg="Selam abi";
 Serial.println(msg);
 
 digitalWrite(13,HIGH);
 vw_send((uint8_t *)msg,1);
 vw_wait_tx();
 digitalWrite(13,LOW);
 delay(1000);
}
