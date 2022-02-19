#define D0 2
#define D1 3
#define D2 4
#define D3 5

const unsigned int pulseLength = 100;
byte state = LOW;

void setup() {
  Serial.begin(9600);

  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);

  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
}

void loop() {
  send0(D1);
  send1(D1);
  send0(D1);
  send1(D1);
  send0(D1);
  send1(D1);
  send0(D1);
  send1(D1);
  send0(D1);
  send1(D1);
  delay(1000);
}

void send0(int pin) {
  state = !state;
  digitalWrite(pin, state);
  delayMicroseconds(pulseLength << 1);
}

void send1(int pin) {
  digitalWrite(pin, state);
  delayMicroseconds(pulseLength);
  digitalWrite(pin, !state);
  delayMicroseconds(pulseLength);
}

void send10(int pin) {
  send1(pin);
  send0(pin);
}

void send01(int pin) {
  send1(pin);
  delayMicroseconds(pulseLength << 1);
}

void send00(int pin) {
  send0(pin);
  delayMicroseconds(pulseLength << 1);
}

void send11(int pin) {
  send1(pin);
  send1(pin);
}
