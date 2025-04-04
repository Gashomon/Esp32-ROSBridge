#ifdef IR_READER
  // #define IR_LIN D33
  // #define IR_LOUT D32
  // #define IR_RIN D17
  // #define IR_ROUT D16

  #define IR_IN D33
  #define IR_OUT D32
#endif

double getIRDist(int ir_pin);

// void IRAM_ATTR IR_R_ISRR();
// void IRAM_ATTR IR_R_ISRF();
// void IRAM_ATTR IR_L_ISRR();
// void IRAM_ATTR IR_L_ISRF();

void IRAM_ATTR IR_ISRF();

// void updateRanges();
void updateRange();

// void resetTimers();
void resetIR();
