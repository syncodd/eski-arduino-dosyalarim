#define pin       2

int pls = 460;

void setup() {

  SPI.begin();
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  
}

void loop() {
  send0();
  send1();
  send0();
  send1();
  delay(1000);
}

void send0() {
  digitalWrite(pin, HIGH);
  delayMicroseconds(pls);
  digitalWrite(pin, LOW);
  delayMicroseconds(pls*3);
}

void send1() {
  digitalWrite(pin, HIGH);
  delayMicroseconds(pls*3);
  digitalWrite(pin, LOW);
  delayMicroseconds(pls);
}
