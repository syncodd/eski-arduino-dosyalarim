#include <MaxMatrix.h>

#define DIN 10
#define CLK 11
#define CS 12

  int b = 0;

MaxMatrix matrix(DIN, CS, CLK, 2);

char A[] = {4, 8,
            B01111110,
            B00010001,
            B00010001,
            B01111110,
           };
           
char dick1[] = {8, 16,
                  B00000000,
                  B00000000,
                  B00011000,
                  B00100100,
                  B00100100,
                  B00100100,
                  B01000010,
                  B01000010,
                  B00000000,
                  B00000000,
                  B00011000,
                  B00100100,
                  B00100100,
                  B00100100,
                  B01000010,
                  B01000010
                 };
char dick2[] = {8, 8,
                  B00011000,
                  B00100100,
                  B00100100,
                  B00100100,
                  B00100100,
                  B01000010,
                  B01011010,
                  B01111110,
                 };

void setup() {
  matrix.init();
  matrix.setIntensity(8); 
}

void loop() {
  matrix.setDot(0,9,true);

  //matrix.clear();
  for(int b=0;b<4;b++) {
    for(int i=0;i<7-2*b;i++) {
      matrix.setDot(i+b,0+b,true);
      matrix.setDot(7-b,i+b,true);
      matrix.setDot(7-i-b,7-b,true);
      matrix.setDot(0+b,7-i-b,true);
      delay(1000);
    }
    matrix.clear();
  }
}
