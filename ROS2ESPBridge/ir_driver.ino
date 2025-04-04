#ifdef USE_BASE
    #ifdef IR_READER
    volatile double left_IR = 0;
    volatile double right_IR = 0;
    volatile double IR_Range = 0;

    // bool LEFT_SENT = false;
    // bool LEFT_GOT = false;
    // volatile unsigned long LEFT_timer1;
    // volatile unsigned long LEFT_timer2;

    // bool RIGHT_SENT = false;
    // bool RIGHT_GOT = false;
    // volatile unsigned long RIGHT_timer1;
    // volatile unsigned long RIGHT_timer2;

    bool IR_SENT = false;
    bool IR_GOT = false;
    volatile unsigned long IR_timer1;
    volatile unsigned long IR_timer2;

    #ifdef WORKING_RANGE
    double getIRDist(int ir_pin){
        if(ir_pin == LEFT) return left_IR;
        else if (ir_pin == RIGHT)return right_IR;
        else return IR_Range;

    }
    #endif

    #ifndef WORKING_RANGE
    double getIRDist(int ir_pin){
        return 100000;
    }
    #endif

    // void IRAM_ATTR IR_R_ISRR() {

    // }
    // void IRAM_ATTR IR_L_ISRR() {

    // }

    // void IRAM_ATTR IR_R_ISRF() {
    //   right_IR = computeDist(micros()-RIGHT_timer2);
    //   resetRight();
    //   // Serial.println("lol");
    // }
    // void IRAM_ATTR IR_L_ISRF() {
    //   left_IR = computeDist(micros()-LEFT_timer2);
    //   resetLeft();
    // }

    void IRAM_ATTR IR_ISRF() {
      IR_Range = computeDist(micros()-IR_timer2);
      resetIR();
    }

    double computeDist(double microvalue){
        double formula = microvalue * 0.034 / 2;
        // formula = formula * 0.01; //cm to m
        return formula;
    }

    // void updateRangeLeft(){
    //   //Timeout of 1 second = 1M micros. Send a huge number. Reset.
    //   if(micros()-LEFT_timer1 >= 1000000){
    //       digitalWrite(IR_LOUT, LOW);
    //       left_IR = computeDist(1000000);
    //       resetLeft();
    //   }

    //   //First 10 microseconds. Send Signal
    //   if(micros()-LEFT_timer2 <= 10){
    //       digitalWrite(IR_LOUT, HIGH);
    //       LEFT_SENT = true;
    //       LEFT_GOT = false;
    //   }

    //   //Waiting to receive the signal. Send Distance
    //   if(micros()-LEFT_timer1 >= 10){
    //       digitalWrite(IR_LOUT, LOW); //Stop Sending signal

    //       //Compute Distance & reset
    //       if(LEFT_SENT){

    //           //Start Timer. State Signal is received.
    //           if(digitalRead(IR_LIN) == HIGH && !LEFT_GOT){
    //               LEFT_timer2 = micros();
    //               LEFT_GOT = true;
    //           }
              
    //           //End Timer. Check end of signal. Send distance
    //       }
    //     }
    // }

    // void updateRangeRight(){
    //   //Timeout of 1 second = 1M micros. Send a huge number. Reset.
    //   if(micros()-RIGHT_timer1 >= 1000000){
    //       digitalWrite(IR_ROUT, LOW);
    //       right_IR = computeDist(1000000);
    //       resetRight();
    //   }

    //   //First 10 microseconds. Send Signal
    //   if(micros()-RIGHT_timer1 <= 10){
    //       digitalWrite(IR_ROUT, HIGH);
    //       RIGHT_SENT = true;
    //       RIGHT_GOT = false;
    //       // Serial.println("hi");
    //   }

    //   //Waiting to receive the signal. Send Distance
    //   if(micros()-RIGHT_timer1 >= 10){
    //       digitalWrite(IR_ROUT, LOW); //Stop Sending signal

    //       //Compute Distance & reset
    //       if(RIGHT_SENT){
                  
    //           //Start Timer. State Signal is received.
    //           if(digitalRead(IR_RIN) == HIGH && !RIGHT_GOT){
    //               RIGHT_timer2 = micros();
    //               RIGHT_GOT = true;
    //               // Serial.println("hello");
    //           }
    //       }
    //     }
    // }
    
    void updateRange(){
      //Timeout of 1 second = 1M micros. Send a huge number. Reset.
      if(micros()-IR_timer1 >= 1000000){
          digitalWrite(IR_OUT, LOW);
          IR_Range = computeDist(1000000);
          resetIR();
      }

      //First 10 microseconds. Send Signal
      if(micros()-IR_timer1 <= 10){
          digitalWrite(IR_OUT, HIGH);
          IR_SENT = true;
          IR_GOT = false;
          // Serial.println("sent");
      }

      //Waiting to receive the signal. Send Distance
      if(micros()-IR_timer1 >= 10){
          digitalWrite(IR_OUT, LOW); //Stop Sending signal

          //Compute Distance & reset
          if(IR_SENT){

              //Start Timer. State Signal is received.
              if(digitalRead(IR_IN) == HIGH && !IR_GOT){
                  IR_timer2 = micros();
                  IR_GOT = true;
                  // Serial.println("got");
              }
              
              //End Timer. Check end of signal. Send distance
          }
        }
    }

    // void updateRanges(){
    //     updateRangeLeft();
    //     updateRangeRight();
    // }
    
    // void resetLeft(){
    //     // digitalWrite(IR_LOUT, LOW);
    //     LEFT_timer1 = micros();
    //     LEFT_timer2 = micros();
    //     LEFT_SENT = false;
    //     LEFT_GOT = false;
    // }

    // void resetRight(){
    //     // digitalWrite(IR_ROUT, LOW);
    //     RIGHT_timer1 = micros();
    //     RIGHT_timer2 = micros();
    //     RIGHT_SENT = false;
    //     RIGHT_GOT = false;
    // }

    // void resetTimers(){
    //     resetLeft();
    //     resetRight();
    // }

    void resetIR(){
      IR_timer1 = micros();
      IR_timer2 = micros();
      IR_SENT = false;
      IR_GOT = false;
      // Serial.println("rest");
    }

    #endif
#endif