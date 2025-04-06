/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/

#ifdef L298_MOTOR_DRIVER
  #define RIGHT_MOTOR_DIR D25
  #define RIGHT_MOTOR_DRIVE  D26

  #define LEFT_MOTOR_DIR  D32
  #define LEFT_MOTOR_DRIVE   D33
  // #define RIGHT_MOTOR_ENABLE GPIO_14
  // #define LEFT_MOTOR_ENABLE GPIO_13
#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);
