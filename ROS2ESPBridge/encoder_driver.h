/* *************************************************************
   Encoder driver function definitions - by James Nugen
   ************************************************************ */
   
#ifdef USE_ENCODERS
  //below can be changed, but should be PORTD pins; 
  //otherwise additional changes in the code are required
  #define LEFT_ENC_CLK D17  //CLK
  #define LEFT_ENC_DT D16  //DT
  
  //below can be changed, but should be PORTC pins
  #define RIGHT_ENC_CLK D19  //CLK
  #define RIGHT_ENC_DT D18   //DT
#endif
   
long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();

void IRAM_ATTR ENC_R_ISR ();
void IRAM_ATTR ENC_L_ISR ();
