#define OnSensor A3
#define SagSensor A2
#define SagCizgi A4
#define SolCizgi A5

#define MotorR1 6
#define MotorL1 7
#define MotorR2 8
#define MotorL2 9


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
  Serial.println("Sag Cizgi");
  Serial.println(digitalRead(SagCizgi));
  Serial.println("Sol Cizgi");
  Serial.println(digitalRead(SolCizgi));
  Serial.println("On Sensor");
  Serial.println(digitalRead(OnSensor));
  Serial.println("Sag Sensor");
  Serial.println(digitalRead(SagSensor));
  delay(1000);

    if(digitalRead(SolCizgi) == 1 && digitalRead(SagCizgi) == 0) {
      if(digitalRead(OnSensor) == 0 && digitalRead(SagSensor) == 0){
        ileri();
      }
      if(digitalRead(OnSensor) == 1 && digitalRead(SagSensor) == 0){
        sag();
      }
      if(digitalRead(OnSensor) == 0 && digitalRead(SagSensor) == 1){
        ileri();
      }
    }
}

void ileri() {
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, HIGH);

  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, LOW);

}

void geri() {
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, LOW);

  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, HIGH);

}

void sag() {
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);

  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, HIGH);

}

void sol() {
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, HIGH);

  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);

}
