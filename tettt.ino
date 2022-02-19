bool lock;

void setup() {
  pinMode(2,OUTPUT);
}

void loop() {
  digitalWrite(2, HIGH);
  while(lock == true) {
    //digitalWrite(2, HIGH);
    delay(1);
    digitalWrite(2, LOW);
    delay(1);
    digitalWrite(2, HIGH);
    delay(1);
    lock = false;
  }
}

void send0() {
  state = !state;
  digitalWrite(2, state);
  delayMicroseconds();
}

void send1() {
  
}
