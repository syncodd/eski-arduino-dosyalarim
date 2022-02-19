#define echo 12
#define trig 13

void setup() {
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  delay(1000);
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  Serial.println(pulseIn(echo, HIGH)/60);
}
