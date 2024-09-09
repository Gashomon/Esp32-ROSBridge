/* *************************************************************
   Encoder driver function definitions - by James Nugen
   ************************************************************ */
   
   
#ifdef ARDUINO_ENC_COUNTER
  //below can be changed, but should be PORTD pins; 
  //otherwise additional changes in the code are required
  #define LEFT_ENC_PIN_A 1  //CLK
  #define LEFT_ENC_PIN_B 2  //DT
  
  //below can be changed, but should be PORTC pins
  #define RIGHT_ENC_PIN_A 11  //CLK
  #define RIGHT_ENC_PIN_B 8   //DT
#endif
   
long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();

void IRAM_ATTR ISR_R ();
void IRAM_ATTR ISR_L ();
