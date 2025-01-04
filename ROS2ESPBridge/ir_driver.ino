#ifdef USE_BASE
    #ifdef IR_READER
    volatile int left_IR = 0;
    volatile int right_IR = 0;

    bool LEFT_SENT = false;
    volatile unsigned long LEFT_start_time;
    volatile unsigned long LEFT_ms_delay = 0;

    bool RIGHT_SENT = false;
    volatile unsigned long RIGHT_start_time;
    volatile unsigned long RIGHT_ms_delay = 0;

    double getIRDist(int ir_pin){
        if(ir_pin == LEFT) return left_IR;
        else return right_IR;
    }

    void IRAM_ATTR IR_R_ISR() {
        // right_IR = digitalRead(IRRIGHT);

    }
    void IRAM_ATTR IR_L_ISR() {
        // left_IR = digitalRead(IRLEFT);

    }

    int computeDist(int ms){
        int formula = ms * 0.034 / 2;
        return formula;
    }

    void updateRangeLeft(){
        if(millis()-LEFT_start_time <= 10){
            //begin sending signal
            digitalWrite(IR_LOUT, HIGH);
            LEFT_SENT = true;
        }
        else if(millis()-LEFT_start_time >= 1000000){
            //reset 
            digitalWrite(IR_LOUT, LOW);
            left_IR = computeDist(1000000);
            LEFT_start_time = millis();
            LEFT_SENT = false;
        }
        else{
            //wait for signal
            digitalWrite(IR_LOUT, LOW);
            //Compute Distance & reset
            if(LEFT_SENT){
                if(digitalRead(IR_LIN) == HIGH){
                    LEFT_ms_delay = millis() - LEFT_start_time - 10;
                    left_IR = computeDist(LEFT_ms_delay);
                    LEFT_start_time = millis();
                    LEFT_SENT = false;
                }
            }
            else{
                LEFT_start_time = millis();
            }
        }
    }

    void updateRangeRight(){
        if(millis()-RIGHT_start_time <= 10){
            //begin sending signal
            digitalWrite(IR_ROUT, HIGH);
            RIGHT_SENT = true;
        }
        else if(millis()-RIGHT_start_time >= 1000000){
            //reset 
            digitalWrite(IR_ROUT, LOW);
            right_IR = computeDist(1000000);
            RIGHT_start_time = millis();
            RIGHT_SENT = false;
        }
        else{
            //wait for signal
            digitalWrite(IR_ROUT, LOW);
            //Compute Distance & reset
            if(RIGHT_SENT){
                if(digitalRead(IR_RIN) == HIGH){
                    RIGHT_ms_delay = millis() - RIGHT_start_time - 10;
                    right_IR = computeDist(RIGHT_ms_delay);
                    RIGHT_start_time = millis();
                    RIGHT_SENT = false;
                }
            }
            else{
                RIGHT_start_time = millis();
            }
        }
    }
    
    void updateRanges(){
        updateRangeLeft();
        updateRangeRight();
    }
    
    void resetTimers(){
        LEFT_start_time = millis();
        RIGHT_start_time = millis();
    }
    #endif
#endif