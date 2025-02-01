#ifdef USE_BASE
    #ifdef IR_READER
    volatile double left_IR = 0;
    volatile double right_IR = 0;

    bool LEFT_SENT = false;
    bool LEFT_GOT = false;
    volatile unsigned long LEFT_timer1;
    volatile unsigned long LEFT_timer2;

    bool RIGHT_SENT = false;
    bool RIGHT_GOT = false;
    volatile unsigned long RIGHT_timer1;
    volatile unsigned long RIGHT_timer2;

    #ifdef WORKING_RANGE
    double getIRDist(int ir_pin){
        if(ir_pin == LEFT) return left_IR;
        else return right_IR;
    }
    #endif

    #ifndef WORKING_RANGE
    double getIRDist(int ir_pin){
        return 100000;
    }
    #endif

    void IRAM_ATTR IR_R_ISRR() {

    }
    void IRAM_ATTR IR_L_ISRR() {

    }

    void IRAM_ATTR IR_R_ISRF() {
      right_IR = computeDist(micros()-RIGHT_timer2);
                  resetRight();
    }
    void IRAM_ATTR IR_L_ISRF() {
      left_IR = computeDist(micros()-LEFT_timer2);
                  resetLeft();
    }

    double computeDist(double microvalue){
        double formula = microvalue * 0.034 / 2;
        return formula;
    }

    void updateRangeLeft(){
      //Timeout of 1 second = 1M micros. Send a huge number. Reset.
      if(micros()-LEFT_timer1 >= 1000000){
          digitalWrite(IR_LOUT, LOW);
          left_IR = computeDist(1000000);
          resetLeft();
      }

      //First 10 microseconds. Send Signal
      if(micros()-LEFT_timer1 <= 10){
          digitalWrite(IR_LOUT, HIGH);
          LEFT_SENT = true;
          LEFT_GOT = false;
      }

      //Waiting to receive the signal. Send Distance
      if(micros()-LEFT_timer1 >= 10){
          digitalWrite(IR_LOUT, LOW); //Stop Sending signal

          //Compute Distance & reset
          if(LEFT_SENT){

              //Start Timer. State Signal is received.
              if(digitalRead(IR_LIN) == HIGH && !LEFT_GOT){
                  LEFT_timer2 = micros();
                  LEFT_GOT = true;
              }
              
              //End Timer. Check end of signal. Send distance
              // if(digitalRead(IR_LIN) == LOW && LEFT_GOT){
              //     left_IR = computeDist(micros()-LEFT_timer2);
              //     resetLeft();
              // }
          }
        }
    }

    void updateRangeRight(){
      
      //Timeout of 1 second = 1M micros. Send a huge number. Reset.
      if(micros()-RIGHT_timer1 >= 1000000){
          digitalWrite(IR_ROUT, LOW);
          right_IR = computeDist(1000000);
          resetRight();
      }

      //First 10 microseconds. Send Signal
      if(micros()-RIGHT_timer1 <= 10){
          digitalWrite(IR_ROUT, HIGH);
          RIGHT_SENT = true;
          RIGHT_GOT = false;
      }

      //Waiting to receive the signal. Send Distance
      if(micros()-RIGHT_timer1 >= 10){
          digitalWrite(IR_ROUT, LOW); //Stop Sending signal

          //Compute Distance & reset
          if(RIGHT_SENT){

              //Start Timer. State Signal is received.
              if(digitalRead(IR_RIN) == HIGH && !RIGHT_GOT){
                  RIGHT_timer2 = micros();
                  RIGHT_GOT = true;
              }
              
              //End Timer. Check end of signal. Send distance
              // if(digitalRead(IR_RIN) == LOW && RIGHT_GOT){
              //     right_IR = computeDist(micros()-RIGHT_timer2);
              //     resetRight();
              // }
          }
        }
    }
    
    void updateRanges(){
        updateRangeLeft();
        updateRangeRight();
    }
    
    void resetLeft(){
        // digitalWrite(IR_LOUT, LOW);
        LEFT_timer1 = micros();
        LEFT_timer2 = 0;
        LEFT_SENT = false;
        LEFT_GOT = false;
    }

    void resetRight(){
        // digitalWrite(IR_ROUT, LOW);
        RIGHT_timer1 = micros();
        RIGHT_timer2 = 0;
        RIGHT_SENT = false;
        RIGHT_GOT = false;
    }

    void resetTimers(){
        resetLeft();
        resetRight();
    }

    #endif
#endif