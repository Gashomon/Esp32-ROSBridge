#ifdef USE_BASE
    #ifdef IR_READER
    volatile int left_IR = 0;
    volatile int right_IR = 0;

    double getIRDist(int ir_pin){
        if(ir_pin == LEFT) return left_IR;
        else return right_IR;
    }

    void IRAM_ATTR IR_R_ISR() {
        right_IR = digitalRead(IRRIGHT);
    }
    void IRAM_ATTR IR_L_ISR() {
        left_IR = digitalRead(IRLEFT);
    }
    
    #endif
#endif