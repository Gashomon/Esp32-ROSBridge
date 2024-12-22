
#ifdef USE_BASE
    #ifdef IMU_READER
        #include <Adafruit_MPU6050.h>
        #include <Adafruit_Sensor.h>
        #include <Wire.h>

        Adafruit_MPU6050 mpu;
        sensors_event_t a, g, t;

        void beginIMU(){
            mpu.begin();
            mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
            mpu.setGyroRange(MPU6050_RANGE_500_DEG);
            mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
        }

        void updateIMU(){
            mpu.getEvent(&a, &g, &t);
        }

        float getImu(int value){
            switch (value)
            {
            case accX
                return a.acceleration.x;
                break;
            case accY
                return a.acceleration.y;
                break;
            case accZ
                return a.acceleration.z;
                break;
            case rotcX
                return g.gyro.x;
                break;
            case rotY
                return g.gyro.y;
                break;
            case rotZ
                return g.gyro.z;
                break;    
            default:
                break;
            }
        }


    #endif
#endif