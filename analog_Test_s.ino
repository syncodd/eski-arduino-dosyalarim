#define pin         A0

void setup() {
  pinMode(pin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(pin));
  delay(100);
}
