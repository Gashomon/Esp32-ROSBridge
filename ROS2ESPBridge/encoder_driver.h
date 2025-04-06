/* *************************************************************
   Encoder driver function definitions - by James Nugen
   ************************************************************ */
   
#ifdef USE_ENCODERS
  //below can be changed, but should be PORTD pins; 
  //otherwise additional changes in the code are required
  #define LEFT_ENC_CLK D13    //CLK
  #define LEFT_ENC_DT D14     //DT
  
  //below can be changed, but should be PORTC pins
  #define RIGHT_ENC_CLK D23   //CLK
  #define RIGHT_ENC_DT D27    //DT
#endif
   
long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders(); 
void updateEncoder(int i);
void updateEncoders();

void IRAM_ATTR ENC_R_ISR ();
void IRAM_ATTR ENC_L_ISR ();
