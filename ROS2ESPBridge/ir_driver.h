#ifdef IR_READER
  #define IRLEFT D13
  #define IRRIGHT D14
#endif

int getIRDist(int ir_pin);

void IRAM_ATTR IR_R_ISR();
void IRAM_ATTR IR_L_ISR();
