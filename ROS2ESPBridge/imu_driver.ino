
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

        double getImu(int value){
            switch (value)
            {
            case ACCX:
                return a.acceleration.x;
                break;
            case ACCY:
                return a.acceleration.y;
                break;
            case ACCZ:
                return a.acceleration.z;
                break;
            case ROTX:
                return g.gyro.x;
                break;
            case ROTY:
                return g.gyro.y;
                break;
            case ROTZ:
                return g.gyro.z;
                break;    
            default:
                break;
            }
        }


    #endif
#endif