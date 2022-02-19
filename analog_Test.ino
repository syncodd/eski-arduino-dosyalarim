#define pin         A0

void setup() {
  pinMode(pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  for(int i = 0; i < 255; i+=25) {
    analogWrite(pin, i);
    delay(1000);
  }  
}
