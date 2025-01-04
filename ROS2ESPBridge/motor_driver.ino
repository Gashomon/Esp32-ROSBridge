/***************************************************************
   Motor driver definitions
   
   Add a "#elif defined" block to this file to include support
   for a particular motor driver.  Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   *************************************************************/

#ifdef USE_BASE

#if defined L298_MOTOR_DRIVER
  void initMotorController() {
    pinMode(LEFT_MOTOR_DRIVE, OUTPUT);
    pinMode(LEFT_MOTOR_DIR, OUTPUT);
    
    pinMode(RIGHT_MOTOR_DRIVE, OUTPUT);
    pinMode(RIGHT_MOTOR_DIR, OUTPUT);
  }
  
  void setMotorSpeed(int i, int spd) {
    unsigned char reverse = 0;
    
    if (spd < 0)
    {
      spd = -spd;
      reverse = 1;
      
    }
    if (spd > 255)
      spd = 255;
    
    if (i == LEFT) { 
      if      (reverse == 0) { analogWrite(LEFT_MOTOR_DRIVE, spd); digitalWrite(LEFT_MOTOR_DIR, LOW); }
      else if (reverse == 1) { analogWrite(LEFT_MOTOR_DRIVE, spd); digitalWrite(LEFT_MOTOR_DIR, HIGH); }
    }
    else /*if (i == RIGHT) //no need for condition*/ {
      if      (reverse == 0) { analogWrite(RIGHT_MOTOR_DRIVE, spd); digitalWrite(RIGHT_MOTOR_DIR, LOW); }
      else if (reverse == 1) { analogWrite(RIGHT_MOTOR_DRIVE, spd); digitalWrite(RIGHT_MOTOR_DIR, HIGH); }
    }
    

  } 
  
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#else
  #error A motor driver must be selected!
#endif

#endif
