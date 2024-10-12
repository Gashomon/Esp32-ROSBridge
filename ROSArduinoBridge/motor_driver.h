/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/

#ifdef L298_MOTOR_DRIVER
  #define RIGHT_MOTOR_BACKWARD GPIO_26
  #define LEFT_MOTOR_BACKWARD  GPIO_33
  #define RIGHT_MOTOR_FORWARD  GPIO_25
  #define LEFT_MOTOR_FORWARD   GPIO_32
  #define RIGHT_MOTOR_ENABLE GPIO_14
  #define LEFT_MOTOR_ENABLE GPIO_13
#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);
