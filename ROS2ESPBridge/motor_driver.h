/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/

#ifdef L298_MOTOR_DRIVER
  #define RIGHT_MOTOR_BACKWARD D26
  #define RIGHT_MOTOR_FORWARD  D25

  #define LEFT_MOTOR_BACKWARD  D33
  #define LEFT_MOTOR_FORWARD   D32
  // #define RIGHT_MOTOR_ENABLE GPIO_14
  // #define LEFT_MOTOR_ENABLE GPIO_13
#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);
