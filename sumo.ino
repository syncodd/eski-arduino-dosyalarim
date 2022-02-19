#include <QTRSensors.h>

#define OnSensor A3
#define SagSensor A2
#define SagCizgi A4
#define SolCizgi A5

#define MotorR1 6
#define MotorL1 7
#define MotorR2 8
#define MotorL2 9

int l,r;

QTRSensorsRC qtrrc((unsigned char[]) {SolCizgi, SagCizgi},2, 2500, QTR_NO_EMITTER_PIN);
unsigned int sensorValues[2];

void setup() {
  pinMode(OnSensor, INPUT);
  pinMode(SagSensor, INPUT);
  pinMode(SagCizgi, INPUT);
  pinMode(SolCizgi, INPUT);

  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);
  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);

  Serial.begin(9600);

  while (digitalRead(OnSensor) == 1);

}

void loop() {
  qtrrc.read(sensorValues);             //Sensorleri okuma
  Serial.print("Left: ");
  l = sensorValues[0];
  Serial.print(l);
  Serial.print("\t Right: ");
  r = sensorValues[1];
  Serial.println(r);
  //delay(1000);
  
  Serial.println("Sag Cizgi");
  Serial.println(digitalRead(SagCizgi));
  Serial.println("Sol Cizgi");
  Serial.println(digitalRead(SolCizgi));
  Serial.println("On Sensor");
  Serial.println(digitalRead(OnSensor));
  Serial.println("Sag Sensor");
  Serial.println(digitalRead(SagSensor));
  //delay(1000);

    if(l <= 1500 or r <= 1500) {
      Serial.println("Beyaz");
      if(digitalRead(OnSensor) == 1 && digitalRead(SagSensor) == 1){
        ileri();
      }
      if(digitalRead(OnSensor) == 0 && digitalRead(SagSensor) == 0){
        ileri();
      }
      if(digitalRead(OnSensor) == 1 && digitalRead(SagSensor) == 0){
        sag();
        delay(500);
      }
      if(digitalRead(OnSensor) == 0 && digitalRead(SagSensor) == 1){
        ileri();
      }
    } else if(l > 1500 or r > 1500) {
      Serial.println("Siyah");
      digitalWrite(MotorR1, LOW);
      digitalWrite(MotorR2, LOW);
      digitalWrite(MotorL1, LOW);
      digitalWrite(MotorL2, LOW);
      geri();
      delay(1000);
      sag();
      delay(500);
    }
    
}

void ileri() {
  Serial.println("İleri");
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, HIGH);

  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, LOW);

}

void geri() {
  Serial.println("Geri");
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, LOW);

  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, HIGH);

}

void sag() {
  Serial.println("Sag");
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);

  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, HIGH);

}

void sol() {
  Serial.println("Sol");
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, HIGH);

  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);

}
