#define MotorR1 6
#define MotorL1 7
#define MotorR2 8
#define MotorL2 9

void setup() {
  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);
  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  ileri();
  delay(2000);
  geri();
  delay(2000);
  sag();
  delay(2000);
  sol();
  delay(2000);

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
