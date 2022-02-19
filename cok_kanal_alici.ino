void setup() {
  Serial.begin(9600);

  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  Serial.print(digitalRead(3));
  Serial.print(digitalRead(4));
  Serial.print(digitalRead(5));
  Serial.println(digitalRead(6));

  if(digitalRead(5) == 0) {
    digitalWrite(LED_BUILTIN, LOW);
  } else if(digitalRead(5) == 1) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
