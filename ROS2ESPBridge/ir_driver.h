#ifdef IR_READER
  #define IR_LIN D13
  #define IR_LOUT D14
  #define IR_RIN D4
  #define IR_ROUT D27
#endif

double getIRDist(int ir_pin);

void IRAM_ATTR IR_R_ISR();
void IRAM_ATTR IR_L_ISR();
void updateRanges();
void resetTimers();
