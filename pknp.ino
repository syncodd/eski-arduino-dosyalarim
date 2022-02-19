#include <I2Cdev.h>
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif
MPU6050 OBJ_1(0x69);
bool VAR_1 = false ;uint8_t mpuIntStatus_OBJ_1 ;uint8_t devStatus_OBJ_1 ;uint16_t packetSize_OBJ_1 ;uint16_t fifoCount_OBJ_1 ;uint8_t fifoBuffer_OBJ_1[64];;Quaternion q_OBJ_1;VectorFloat gravity_OBJ_1; volatile bool mpuInterrupt_OBJ_1 = false ;void dmpDataReady_OBJ_1(){ mpuInterrupt_OBJ_1 = true;}
int16_t ax_OBJ_1, ay_OBJ_1, az_OBJ_1;
int16_t gx_OBJ_1, gy_OBJ_1, gz_OBJ_1;
float wx = 0;
float wy = 0;
float wz = 0;
void setup()
{
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
Wire.begin();
TWBR = 24;
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
Fastwire::setup(400, true);
#endif
Serial.begin(9600);
OBJ_1.initialize();
OBJ_1.dmpInitialize();
if (devStatus_OBJ_1 == 0)
{
OBJ_1.setDMPEnabled(true);
attachInterrupt(0, dmpDataReady_OBJ_1, RISING);
mpuIntStatus_OBJ_1 = OBJ_1.getIntStatus();
VAR_1 = true;
packetSize_OBJ_1 = OBJ_1.dmpGetFIFOPacketSize();
}
for( int dummy_3d2a = 0 ; dummy_3d2a<10 ; dummy_3d2a ++ )
{
delay(500);
for( int dummy_3d2a = 0 ; dummy_3d2a<20 ; dummy_3d2a ++ )
{
OBJ_1.resetFIFO();
fifoCount_OBJ_1 = 0;
while (fifoCount_OBJ_1 < _packetSize_OBJ_1)
{ fifoCount_OBJ_1 = OBJ_1.getFIFOCount();}
OBJ_1.getFIFOBytes(fifoBuffer_OBJ_1, packetSize_OBJ_1);OBJ_1.getMotion6(&ax_OBJ_1, &ay_OBJ_1, &az_OBJ_1, &gx_OBJ_1, &gy_OBJ_1, &gz_OBJ_1);
wx=wx+gx_OBJ_1;
wy=wy+gy_OBJ_1;
wz=wz+gz_OBJ_1;
}
wx=wx/20;
wy=wy/20;
wz=wz/20;
OBJ_1.setXGyroOffset(OBJ_1.getXGyroOffset()-wx);
OBJ_1.setYGyroOffset(OBJ_1.getYGyroOffset()-wy);
OBJ_1.setZGyroOffset(OBJ_1.getZGyroOffset()-wz);
Serial.print(" set_wx= ");
Serial.print(OBJ_1.getXGyroOffset());
Serial.print(" set_wy= ");
Serial.print(OBJ_1.getYGyroOffset());
Serial.print(" set_wz= ");
Serial.println(OBJ_1.getZGyroOffset());
for( int dummy_3d2a = 0 ; dummy_3d2a<20 ; dummy_3d2a ++ )
{
OBJ_1.resetFIFO();
fifoCount_OBJ_1 = 0;
while (fifoCount_OBJ_1 < _packetSize_OBJ_1)
{ fifoCount_OBJ_1 = OBJ_1.getFIFOCount();}
OBJ_1.getFIFOBytes(fifoBuffer_OBJ_1, packetSize_OBJ_1);OBJ_1.getMotion6(&ax_OBJ_1, &ay_OBJ_1, &az_OBJ_1, &gx_OBJ_1, &gy_OBJ_1, &gz_OBJ_1);
wx=wx+gx_OBJ_1;
wy=wy+gy_OBJ_1;
wz=wz+gz_OBJ_1;
}
wx=wx/20;
wy=wy/20;
wz=wz/20;
Serial.print(" err_wx= ");
Serial.print(wx);
Serial.print(" err_wy= ");
Serial.print(wy);
Serial.print(" err_wz= ");
Serial.println(wz);
Serial.println(" ");
Serial.println(" ");
}
}
void loop()
{
}
