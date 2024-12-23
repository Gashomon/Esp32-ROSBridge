/* *************************************************************
   Encoder definitions
   
   Add an "#ifdef" block to this file to include support for
   a particular encoder board or library. Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   ************************************************************ */
   
#ifdef USE_BASE

#if defined(USE_ENCODERS)
  volatile long left_enc_pos = 0L;
  volatile long right_enc_pos = 0L;

  uint8_t curr_left = digitalRead(LEFT_ENC_CLK);
  uint8_t curr_right = digitalRead(RIGHT_ENC_CLK);
  uint8_t prev_left = curr_left;
  uint8_t prev_right = curr_right;

  /* Interrupt routine for LEFT encoder, taking care of actual counting */
  void IRAM_ATTR ENC_L_ISR (){
  	if (digitalRead(LEFT_ENC_DT) == digitalRead(LEFT_ENC_CLK))
    left_enc_pos ++;
    else
    left_enc_pos --;
  }
  
  /* Interrupt routine for RIGHT encoder, taking care of actual counting */
  void IRAM_ATTR ENC_R_ISR (){
    if (digitalRead(RIGHT_ENC_DT) == digitalRead(RIGHT_ENC_CLK))
    right_enc_pos ++;
    else
    right_enc_pos --;
  }
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return left_enc_pos;
    else return right_enc_pos;
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT){
      left_enc_pos=0L;
      return;
    } else { 
      right_enc_pos=0L;
      return;
    }
  }
#else
  #error A encoder driver must be selected!
#endif

/* Wrap the encoder reset function */
void resetEncoders() {
  resetEncoder(LEFT);
  resetEncoder(RIGHT);
}

#endif

