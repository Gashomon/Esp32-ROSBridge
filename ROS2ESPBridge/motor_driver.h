/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/

#ifdef L298_MOTOR_DRIVER
  #define RIGHT_MOTOR_DIR D17
  #define RIGHT_MOTOR_DRIVE  D16

  #define LEFT_MOTOR_DIR  D19
  #define LEFT_MOTOR_DRIVE   D18
  // #define RIGHT_MOTOR_ENABLE GPIO_14
  // #define LEFT_MOTOR_ENABLE GPIO_13
#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);
