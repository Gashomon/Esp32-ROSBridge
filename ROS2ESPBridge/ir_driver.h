#ifdef IR_READER
  #define IR_LIN D19
  #define IR_LOUT D18
  #define IR_RIN D17 
  #define IR_ROUT D16
#endif

double getIRDist(int ir_pin);

void IRAM_ATTR IR_R_ISR();
void IRAM_ATTR IR_L_ISR();
void updateRanges();
void resetTimers();
