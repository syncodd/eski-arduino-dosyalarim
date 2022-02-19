#define OnSensor 3
#define SolSensor 2
#define SagCizgi 4
#define SolCizgi 5

#define MotorR1 6
#define MotorR2 8
#define MotorL1 7
#define MotorL2 9


void setup() {

  pinMode(OnSensor, INPUT);
  pinMode(SolSensor, INPUT);
  pinMode(SagCizgi, INPUT);
  pinMode(SolCizgi, INPUT);

  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);
  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);
  
  //Serial.begin(9600);

  while(digitalRead(OnSensor) == 1);
 
}

void loop() {

 
  if(digitalRead(SagCizgi) == 0 && digitalRead(SolCizgi) == 0){

    if(digitalRead(OnSensor) == 0 && digitalRead(SolSensor) == 1){
      ileri();
    }
    if(digitalRead(OnSensor) == 1 && digitalRead(SolSensor) == 0){
      sol();
    }
    if(digitalRead(OnSensor) == 1 && digitalRead(SolSensor) == 1){
      ileri();
    }
    
  }
  else{

    geri();
    delay(1000);
    sol();
    delay(400);
    
  }
  
}

void ileri(){
    digitalWrite(MotorR1, HIGH);
    digitalWrite(MotorR2, LOW);

    digitalWrite(MotorL1, HIGH);
    digitalWrite(MotorL2, LOW);
  
}

void geri(){
    digitalWrite(MotorR1, LOW);
    digitalWrite(MotorR2, HIGH);

    digitalWrite(MotorL1, LOW);
    digitalWrite(MotorL2, HIGH);
  
}

void sol(){
    digitalWrite(MotorR1, HIGH);
    digitalWrite(MotorR2, LOW);

    digitalWrite(MotorL1, LOW);
    digitalWrite(MotorL2, HIGH);
  
}

void sag(){
    digitalWrite(MotorR1, LOW);
    digitalWrite(MotorR2, HIGH);

    digitalWrite(MotorL1, HIGH);
    digitalWrite(MotorL2, LOW);
  
}
