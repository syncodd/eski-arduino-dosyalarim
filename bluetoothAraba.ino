char komut;
int i1=6;
int g1=7;
int i2=8;
int g2=9;
int i3=10;
int g3=11;
int i4=12;
int g4=13;

void _Ileri() { 
  digitalWrite(i1,HIGH);
  digitalWrite(g1,LOW);
  digitalWrite(i2,HIGH);
  digitalWrite(g2,LOW);
  digitalWrite(i3,HIGH);
  digitalWrite(g3,LOW);
  digitalWrite(i4,HIGH);
  digitalWrite(g4,LOW);
  Serial.println("Ileri!");
}
void _Geri() {
  digitalWrite(i1,LOW);
  digitalWrite(g1,HIGH);
  digitalWrite(i2,LOW);
  digitalWrite(g2,HIGH);
  digitalWrite(i3,LOW);
  digitalWrite(g3,HIGH);
  digitalWrite(i4,LOW);
  digitalWrite(g4,HIGH);
  Serial.println("Geri!");
}
void _Sol() {
  digitalWrite(i1,HIGH);
  digitalWrite(g1,LOW);
  digitalWrite(i2,LOW);
  digitalWrite(g2,HIGH);
  digitalWrite(i3,LOW);
  digitalWrite(g3,HIGH);
  digitalWrite(i4,HIGH);
  digitalWrite(g4,LOW);
  Serial.println("Sol!");
}
void _Sag() {
  digitalWrite(i1,LOW);
  digitalWrite(g1,HIGH);
  digitalWrite(i2,HIGH);
  digitalWrite(g2,LOW);
  digitalWrite(i3,HIGH);
  digitalWrite(g3,LOW);
  digitalWrite(i4,LOW);
  digitalWrite(g4,HIGH);
  Serial.println("Sag!");
}
void _Dur() {
  digitalWrite(i1,LOW);
  digitalWrite(g1,LOW);
  digitalWrite(i2,LOW);
  digitalWrite(g2,LOW);
  digitalWrite(i3,LOW);
  digitalWrite(g3,LOW);
  digitalWrite(i4,LOW);
  digitalWrite(g4,LOW);
  Serial.println("Dur!");
}


void setup() { 
  Serial.begin(9600);
  pinMode(i1,OUTPUT);
  pinMode(g1,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(g2,OUTPUT);
  pinMode(i3,OUTPUT);
  pinMode(g3,OUTPUT);
  pinMode(i4,OUTPUT);
  pinMode(g4,OUTPUT);
  _Dur();
}

void loop() { 
  komut=Serial.read();
  
  if(komut=='f') {
    _Ileri();
  }
  if(komut=='b') {
    _Geri();
  }
  if(komut=='l') {
    _Sol();
  }
  if(komut=='r') {
    _Sag();
  }
  if(komut=='s') {
    _Dur();
  }
  if(komut=='d') {
    Serial.println("D");
    delay(100);
    _Dur();
  }
}
