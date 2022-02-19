#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 mpu;

#define OUTPUT_READABLE_YAWPITCHROLL

#define INTERRUPT_PIN 2  // use pin 2 on Arduino Uno & most boards
#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };



// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

//define Servo pins
#define SB        7
#define SF        3
#define ESCPin    10

RF24 radio(9, 8);  // CE, CSN

//Servos
Servo servoB, servoF, ESC;

//RF
const byte address[6] = "00249"; //address

//var
String mess;
bool firstStart = false;
bool start = false;
bool locked = true;
int coolDown, radioAvailable;
int j1x, j1y, j2x, j2y;

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
    Serial.begin(115200);
    while (!Serial);
    Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();
    pinMode(INTERRUPT_PIN, INPUT);
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
    Serial.println(F("\nSend any character to begin DMP programming and demo: "));
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788);

    if (devStatus == 0) {

        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        mpu.PrintActiveOffsets();
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        Serial.print(F("Enabling interrupt detection (Arduino external interrupt "));
        Serial.print(digitalPinToInterrupt(INTERRUPT_PIN));
        Serial.println(F(")..."));
        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }

    radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();

  //Servos
  servoB.attach(SB);
  servoF.attach(SF);

  ESC.attach(ESCPin, 1000, 2000);
  
  servoB.write(90);
  servoF.write(90);

  firstStart = false;
  start = false;
  locked = true;
  
    pinMode(LED_PIN, OUTPUT);
}



// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {
    if (!dmpReady) return;

    while (!mpuInterrupt && fifoCount < packetSize) {
        if (mpuInterrupt && fifoCount < packetSize) {
          // try to get out of the infinite loop 
          fifoCount = mpu.getFIFOCount();
        }  
    }

    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    fifoCount = mpu.getFIFOCount();
  if(fifoCount < packetSize){

  }

    else if ((mpuIntStatus & _BV(MPU6050_INTERRUPT_FIFO_OFLOW_BIT)) || fifoCount >= 1024) {

        mpu.resetFIFO();
        Serial.println(F("FIFO overflow!"));
    } else if (mpuIntStatus & _BV(MPU6050_INTERRUPT_DMP_INT_BIT)) {
  while(fifoCount >= packetSize){
    mpu.getFIFOBytes(fifoBuffer, packetSize);
    fifoCount -= packetSize;
  }
        #ifdef OUTPUT_READABLE_QUATERNION
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            Serial.print("quat\t");
            Serial.print(q.w);
            Serial.print("\t");
            Serial.print(q.x);
            Serial.print("\t");
            Serial.print(q.y);
            Serial.print("\t");
            Serial.println(q.z);
        #endif

        #ifdef OUTPUT_READABLE_EULER
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetEuler(euler, &q);
            Serial.print("euler\t");
            Serial.print(euler[0] * 180/M_PI);
            Serial.print("\t");
            Serial.print(euler[1] * 180/M_PI);
            Serial.print("\t");
            Serial.println(euler[2] * 180/M_PI);
        #endif

        #ifdef OUTPUT_READABLE_YAWPITCHROLL
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            Serial.print("ypr\t");
            Serial.print(ypr[0] * 180/M_PI);
            Serial.print("\t");
            Serial.print(ypr[1] * 180/M_PI);
            Serial.print("\t");
            Serial.println(ypr[2] * 180/M_PI);

            if(radio.available()) {
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    //Serial.println(text);

    mess = (String)text;
    
    j1x = map(((String(mess[0]) + String(mess[1]) + String(mess[2]) + String(mess[3])).toInt() - 3378), 0, 1023, 0, 180);
    j1y = map(((String(mess[4]) + String(mess[5]) + String(mess[6]) + String(mess[7])).toInt() - 4026), 0, 1023, 0, 180);
    j2x = map(((String(mess[8]) + String(mess[9]) + String(mess[10]) + String(mess[11])).toInt() - 2298), 0 , 1023, 0, 180);
    j2y = map(((String(mess[12]) + String(mess[13]) + String(mess[14]) + String(mess[15])).toInt() - 3928), 0, 1023, 0, 180);
  
    radioAvailable-=150;
    if(radioAvailable < 0) {
      radioAvailable = 0;
    }
    Serial.println(radioAvailable);
  }
  
  if(radio.available() == false) {
    radioAvailable++;
    if(radioAvailable > 110) {
      locked = true;
      start = false;
      j1x = 90;
      //j1y = 11;
      j2x = 90;
      j2y = 90;
    
      servoMove(j2x);
      servoBack(j2y);
      Engine(j1y);
      Serial.println(radioAvailable);
      killEngine();
      Serial.println("DEATH!");
    } else {
      j1x = map(((String(mess[0]) + String(mess[1]) + String(mess[2]) + String(mess[3])).toInt() - 3378), 0, 1023, 0, 180);
      j1y = map(((String(mess[4]) + String(mess[5]) + String(mess[6]) + String(mess[7])).toInt() - 4026), 0, 1023, 0, 180);
      j2x = map(((String(mess[8]) + String(mess[9]) + String(mess[10]) + String(mess[11])).toInt() - 2298), 0 , 1023, 0, 180);
      j2y = map(((String(mess[12]) + String(mess[13]) + String(mess[14]) + String(mess[15])).toInt() - 3928), 0, 1023, 0, 180);
      //radioAvailable--;
      Serial.println((String)j1x + j1y + j2x + j2y);
    }
  }
  
  //Inputs to Int
  
  if(coolDown < 3) {
    Serial.println("CoolDown " + (String)(3-coolDown) + "!");
    coolDown++;
    delay(1000);
    if(coolDown == 3) {
      Serial.println("CoolDown END!");
    }
  } else {
    if(j1y <= 9 && firstStart == false) {
      Serial.println("DOWN!");
      start = false;
      firstStart = true;
    }

    if(j1y >= 9 && firstStart == true && start == false) {
      Serial.println("UP!");
      start = true;
      locked = false;
    }
  
    if(firstStart == true && start == true && locked == false) {
      Serial.println(String(j1x) + " " + String(j1y) + " " + String(j2x) + " " + String(j2y));
      
      servoMove(j2x);
      servoBack(j2y);
      Engine(j1y);
    }
  }
        #endif

        #ifdef OUTPUT_READABLE_REALACCEL
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetAccel(&aa, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
            Serial.print("areal\t");
            Serial.print(aaReal.x);
            Serial.print("\t");
            Serial.print(aaReal.y);
            Serial.print("\t");
            Serial.println(aaReal.z);
        #endif

        #ifdef OUTPUT_READABLE_WORLDACCEL
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetAccel(&aa, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
            mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
            Serial.print("aworld\t");
            Serial.print(aaWorld.x);
            Serial.print("\t");
            Serial.print(aaWorld.y);
            Serial.print("\t");
            Serial.println(aaWorld.z);
        #endif
    
        #ifdef OUTPUT_TEAPOT

            teapotPacket[2] = fifoBuffer[0];
            teapotPacket[3] = fifoBuffer[1];
            teapotPacket[4] = fifoBuffer[4];
            teapotPacket[5] = fifoBuffer[5];
            teapotPacket[6] = fifoBuffer[8];
            teapotPacket[7] = fifoBuffer[9];
            teapotPacket[8] = fifoBuffer[12];
            teapotPacket[9] = fifoBuffer[13];
            Serial.write(teapotPacket, 14);
            teapotPacket[11]++; //
        #endif

        blinkState = !blinkState;
        digitalWrite(LED_PIN, blinkState);
    }
}

void servoBack(int value) {
  servoB.write(value);
  Serial.println("UNLOCKED! J1Y : " + (String)j1y);
}

void servoMove(int value) {
  servoF.write(180-value+((int)(ypr[0] * 180/M_PI)));
  Serial.println(180-value+((int)ypr[0]));
  Serial.println(ypr[0]);

  delay(100);
}

void killEngine() {
  for(j1y; j1y > 0; j1y--) {
    Serial.println(j1y);
    delay(100);
    ESC.write(j1y);
  }
  locked = true;
  start = false;
  firstStart = false;
}
void Engine(int value) {
  ESC.write(value);
}
