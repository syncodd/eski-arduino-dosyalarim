#define pin       2

void setup() {

  Serial.begin(9600);
  
  pinMode(pin, INPUT);

}

void loop() {
  Serial.println(digitalRead(pin));
}
