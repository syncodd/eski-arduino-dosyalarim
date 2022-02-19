#include <QTRSensors.h>         //Pololu QTR Sensor Kütüphanesi   

//***********Parametre Tanımlamaları*************************
#define Solsensor    2    //Sol sensör tanımlama
#define Sagsensor    3    //Sag sensör tanımlama 
//*******************************************************

//Nesneyi Takip eden QTR Sensör Hattının Kurulumu
QTRSensorsRC qtrrc((unsigned char[]) {Solsensor, Sagsensor},2, 2500, QTR_NO_EMITTER_PIN);
unsigned int sensorValues[2];

void setup()
{
  Serial.begin(9600);    //Denemelerimizi görmek için serial portu açalım
}

void loop()
{
  qtrrc.read(sensorValues);             //Sensorleri okuma
  Serial.print("Left: ");
  Serial.print(sensorValues[0]);
  Serial.print("\t Right: ");
  Serial.println(sensorValues[1]);
  delay(1000);
}
