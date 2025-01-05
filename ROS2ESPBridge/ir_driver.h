#ifdef IR_READER
  #define IR_LIN D23
  #define IR_LOUT D27
  #define IR_RIN D13
  #define IR_ROUT D14
#endif

double getIRDist(int ir_pin);

void IRAM_ATTR IR_R_ISR();
void IRAM_ATTR IR_L_ISR();
void updateRanges();
void resetTimers();
