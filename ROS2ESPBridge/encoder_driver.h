/* *************************************************************
   Encoder driver function definitions - by James Nugen
   ************************************************************ */
   
#ifdef USE_ENCODERS
  //below can be changed, but should be PORTD pins; 
  //otherwise additional changes in the code are required
  #define LEFT_ENC_CLK D14    //CLK
  #define LEFT_ENC_DT D13     //DT
  
  //below can be changed, but should be PORTC pins
  #define RIGHT_ENC_CLK D4   //CLK
  #define RIGHT_ENC_DT D15    //DT
#endif
   
long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders(); 
void updateEncoder(int i);
void updateEncoders();

void IRAM_ATTR ENC_R_ISR ();
void IRAM_ATTR ENC_L_ISR ();
