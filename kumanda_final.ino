void setup() {

  pinMode(OUTPUT, 2);
  pinMode(OUTPUT, 3);
  pinMode(OUTPUT, 4);
  pinMode(OUTPUT, 5);

}

void loop() {

  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);

  delay(1);

  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
}
