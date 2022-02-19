int laserPin = 13;

void setup() {                
  pinMode(laserPin, OUTPUT);  // Define the digital output interface pin 13 
  Serial.begin(9600);
}

void loop() {
  yak();
  delay(250); // Delay one/
  sondur();
  delay(250); 
}

void yak() {
  digitalWrite(laserPin, HIGH);
  Serial.println("YANDI!");
}

void sondur() {
  digitalWrite(laserPin, LOW);
  Serial.println("SÖNDÜR!");
}
