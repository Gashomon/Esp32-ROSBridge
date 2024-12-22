#ifdef IMU_READER
  #define IMUSCL D21
  #define IMUSDA D22
#endif

// functions to get imu
void beginIMU();
void updateIMU();
float getImu(int value);