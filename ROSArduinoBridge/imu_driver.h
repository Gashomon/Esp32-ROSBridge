// IMU sensor reader 

#ifdef MPU6050_IMU_READER
  // IMU pins
//   #define IMU_VCC PINNAME  //VCC, power
//   #define IMU_GND PINNAME  //GND, ground
#define IMU_CLK GPIO_36  //SCL. clock
#define IMU_SDA GPIO_39   //SDA, reading data via I2C
//   #define IMU_XDA PINNAME  //XDA, auxillary data interfaced with other I2C modules (external sensors)
//   #define IMU_XCL PINNAME  //XCL, auxillary clock (external sensors)
//   #define IMU_XDA PINNAME  //ADD or AD0, address select pin to identify from other imu sensors 
//   #define IMU_INT PINNAME   //INT, interrupt pin to indicate MCU that data is available
#endif
   
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

long readIMU(int i);

