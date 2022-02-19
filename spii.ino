#include <SPI.h>

#define pin 2

int a, b;
int t0, t1;
int per = 2;
int bolum = 150;
int bbb = 1500;
double dodge = .34;
String out, sbD, genOut, THELASTOUT;
bool SB, setFirstBinary;
bool first = false;

void setup() {
  pinMode(pin, INPUT);

  Serial.begin(9600);

  SPI.begin();
}

void loop() { 
  
  while(a <= bbb) {
    out = out + String(digitalRead(pin));
    
    sbD = sbD + String(digitalRead(pin));
    
    if(sbD.length() == per) {
      //Serial.println(genOut);
      for(int i = 0; i < per; i++) {
        b = b + (String(sbD[i])).toInt();
      }
      if(b/per >= .5) {
        //Serial.println("BİR");
        t1 += 1;
        
        if(first == true) {
          changeOne(t1);
          SB = true;
        }
      } else if(b/per <.5) {
        //Serial.println("SIFIR");
        t0 += 1;

        if(first == true) {
          changeZero(t0);
          SB = false;
          first = false;
        }
      }

      if((b/per >= .5) && (SB == false)) {
        changeZero(t0);         
        
      } else if((b/per <.5) && (SB == true)) {
        changeOne(t1);        
      }
      //Serial.println(out);
      sbD = "";
      //Serial.println(b);
      b = 0; 
    }
    
    //Serial.println(out);
    a++;
    if(a == bbb) {
      //Serial.println(out);
      Serial.println(genOut);
      Serial.println("(0 (" + String(t0) + "), 1 (" + String(t1) + ")) |||");
      Serial.println(setFirstBinary + THELASTOUT);
      bynaryToText(setFirstBinary + THELASTOUT);
    }
    Serial.println(digitalRead(pin));
  } 
}

void changeZero(int t0) {
  if((SB == false) && (first == false)) {
    int SAYI = (int)((double(t0)/bolum)+dodge);
    genOut = genOut + " ||| " + SAYI + " <- SIFIR ";

    bynaryDatas(SAYI);
    
    t0 = 0;
    SB = true;
  }
  if(first == true) {
    genOut = genOut + "SIFIR (1.) ";

    setFirstBinary = false;
    
    t0 = 0;
    first = false;
  }
}

void changeOne(int t1) {
  if((SB == true) && (first == false)) {
    int SAYI = (int)((double(t1)/bolum)+dodge);
    genOut = genOut + " ||| " + SAYI + " <- BİR ";

    bynaryDatas(SAYI);
    
    t1 = 0;
    SB = false;
  }
  if(first == true) {
    genOut = genOut + "BİR (1.) ";

    setFirstBinary = true;
    
    t1 = 0;
    first = false;
  }
}

void bynaryDatas(int SAYI) {
  THELASTOUT = THELASTOUT + SAYI;
}

void bynaryToText(String datas) {
  int firstBin = (int)datas[0];
  String reallyLastOut;
  
  for(int i = 1; i < datas.length(); i++) {
    reallyLastOut = reallyLastOut + "asd";
    for(int l = 0; (l < (int)datas[i]) && ((String)firstBin == "0"); l++) {
      reallyLastOut = reallyLastOut + "0";
    }

    for(int l = 0; (l < (int)datas[i]) && ((String)firstBin == "1"); l++) {
      reallyLastOut = reallyLastOut + "1";
    }
  }
  Serial.println(reallyLastOut);
}
