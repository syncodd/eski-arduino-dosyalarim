#include "Ultrasonic.h"
Ultrasonic ultrasonic(12,13);
void setup()
{
pinMode(11, OUTPUT);  /* Additional pin setting */
digitalWrite(11, HIGH); /* Additional pin setting */
Serial.begin( 9600 );
}
void loop()
{
Serial.print( ultrasonic.Ranging(CM) );
Serial.println( "cm" );
delay(1000);
}
