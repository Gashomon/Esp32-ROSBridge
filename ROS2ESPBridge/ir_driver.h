#ifdef IR_READER
  #define IR_LIN D19
  #define IR_LOUT D18
  #define IR_RIN D17 
  #define IR_ROUT D16
#endif

double getIRDist(int ir_pin);

void IRAM_ATTR IR_R_ISRR();
void IRAM_ATTR IR_R_ISRF();
void IRAM_ATTR IR_L_ISRR();
void IRAM_ATTR IR_L_ISRF();

void updateRanges();
void resetTimers();
