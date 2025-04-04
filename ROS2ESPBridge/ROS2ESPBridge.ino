/*********************************************************************
 *  ROSArduinoBridge
 
    A set of simple serial commands to control a differential drive
    robot and receive back sensor and odometry data. Default 
    configuration assumes use of an Arduino Mega + Pololu motor
    controller shield + Robogaia Mega Encoder shield.  Edit the
    readEncoder() and setMotorSpeed() wrapper functions if using 
    different motor controller or encoder method.

    Created for the Pi Robot Project: http://www.pirobot.org
    and the Home Brew Robotics Club (HBRC): http://hbrobotics.org
    
    Authors: Patrick Goebel, James Nugen

    Inspired and modeled after the ArbotiX driver by Michael Ferguson
    
    Software License Agreement (BSD License)

    Copyright (c) 2012, Patrick Goebel.
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

     * Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above
       copyright notice, this list of conditions and the following
       disclaimer in the documentation and/or other materials provided
       with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
    COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
    ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

#define USE_BASE      // Enable the base controller code
//#undef USE_BASE     // Disable the base controller code

/* Define the motor controller and encoder library you are using */
#ifdef USE_BASE
   /* Use Encoders */
   #define USE_ENCODERS

   /* L298 Motor driver*/
   #define L298_MOTOR_DRIVER

  /* My own IMU sensor*/
  #define IMU_READER
  #define WORKING_IMU

  /* My own IR sensor*/
  #define IR_READER
  #define WORKING_RANGE
#endif

/* Serial port baud rate SHOULD BE 115200, BUT 9600 IS USED FOR DEBUGGING WITH WIRE EXTENSION*/
#define BAUDRATE        115200

/* Maximum PWM signal */
#define MAX_PWM         150
#define MAX_PWM_SPIN    150

/* Include definition of serial commands */
#include "commands.h"

/* Include other functions for compilation*/
#include "sensors.h"

#ifdef USE_BASE

  // Assign pins
  #include "pins_esp.h"

  /* Motor driver function definitions */
  #include "motor_driver.h"

  /* Encoder driver function definitions */
  #include "encoder_driver.h"

  /* PID parameters and functions */
  #include "diff_controller.h"

  /* IMU driver function definitions */
  #include "imu_driver.h"
  
  /* IR driver function definitions*/
  #include "ir_driver.h"

  /* Run the PID loop at 30 times per second */
  #define PID_RATE           50     // Hz

  /* Convert the rate into an interval */
  const int PID_INTERVAL = 1000 / PID_RATE;
  
  /* Track the next time we make a PID calculation */
  unsigned long nextPID = PID_INTERVAL;

  /* Stop the robot if it hasn't received a movement command in this number of milliseconds */
  #define AUTO_STOP_INTERVAL 500
  long lastMotorCommand = AUTO_STOP_INTERVAL;  
#endif

/* Variable initialization */

// A pair of varibles to help parse serial commands (thanks Fergs)
int arg = 0;
int in_dicks = 0;

// Variable to hold an input character
char chr;

// Variable to hold the current single-character command
char cmd;

// Character arrays to hold the first and second arguments
char argv1[16];
char argv2[16];

// The arguments converted to integers
long arg1;
long arg2;

/* Clear the current command parameters */
void resetCommand() {
  cmd = NULL;
  memset(argv1, 0, sizeof(argv1));
  memset(argv2, 0, sizeof(argv2));
  arg1 = 0;
  arg2 = 0;
  arg = 0;
  in_dicks = 0;
}

/* Run a command.  Commands are defined in commands.h */
void runCommand() {
  int i = 0;
  char *p = argv1;
  char *str;
  int pid_args[4];
  arg1 = atoi(argv1);
  arg2 = atoi(argv2);
  char nul = '/0';
  
  switch(cmd) {
  case GET_BAUDRATE:
    Serial.println(BAUDRATE);
    break;
  case ANALOG_READ:
    Serial.println(analogRead(arg1));
    break;
  case DIGITAL_READ:
    Serial.println(digitalRead(arg1));
    break;
  case ANALOG_WRITE:
    analogWrite(arg1, arg2);
    Serial.println("AW"); 
    break;
  case DIGITAL_WRITE:
    if (arg2 == 0) digitalWrite(arg1, LOW);
    else if (arg2 == 1) digitalWrite(arg1, HIGH);
    Serial.println("DW"); 
    break;
  case PIN_MODE:
    if (arg2 == 0) pinMode(arg1, INPUT);
    else if (arg2 == 1) pinMode(arg1, OUTPUT);
    Serial.println("PM");
    break;
  case PING:
    Serial.println(Ping(arg1));
    break;

    
#ifdef USE_BASE
  case READ_ENCODERS:
    Serial.print(readEncoder(LEFT));
    Serial.print(" ");
    Serial.println(readEncoder(RIGHT));
    break;

   case RESET_ENCODERS:
    resetEncoders();
    resetPID();
    Serial.println("RESET");
    break;

  case MOTOR_SPEEDS:
    /* Reset the auto stop timer */
    lastMotorCommand = millis();
    if (arg1 == 0 && arg2 == 0) {
      setMotorSpeeds(0, 0);
      resetPID();
      moving = 0;
    }
    else moving = 1;
    leftPID.TargetTicksPerFrame = arg1;
    rightPID.TargetTicksPerFrame = arg2;
    Serial.println("SPEEDS");
    break;

  case MOTOR_RAW_PWM:
    /* Reset the auto stop timer */
    lastMotorCommand = millis();
    resetPID();
    moving = 0; // Sneaky way to temporarily disable the PID
    setMotorSpeeds(arg1, arg2);
    Serial.println("RAW");
    break;

  // Must tweak Update PID
  case UPDATE_PID: 
    while ((str = strtok_r(p, ":", &p) ) != &nul) {
       pid_args[i] = atoi(str);
       i++;
       if( i >= 4){
        break;
       }
    }
    // pid_args[0] = 10;
    // pid_args[1] = 10;
    // pid_args[2] = 10;
    // pid_args[3] = 10;
    Kp = pid_args[0];
    Kd = pid_args[1];
    Ki = pid_args[2];
    Ko = pid_args[3];
    // Serial.print("NEW PID (P, D, I, O): ");
    // Serial.print(Kp);
    // Serial.print(" ");
    // Serial.print(Kd);
    // Serial.print(" ");
    // Serial.print(Ki);
    // Serial.print(" ");
    // Serial.println(Ko);
    Serial.println("PIDU");
    break;
    
    case IMU_READ:
    Serial.print(getImu(ACCX));
    Serial.print(" ");
    Serial.print(getImu(ACCY));
    Serial.print(" ");
    Serial.print(getImu(ACCZ));
    Serial.print(" ");
    Serial.print(getImu(ROTX));
    Serial.print(" ");
    Serial.print(getImu(ROTY));
    Serial.print(" ");
    Serial.println(getImu(ROTZ));
    break;

    case IR_READ:
    // Serial.print(getIRDist(LEFT));
    // Serial.print(" ");
    // Serial.println(getIRDist(RIGHT));
    Serial.println(getIRDist(MIDDLE));
    break;
#endif
  default:
    Serial.println("Invalid Command");
    break;
  }
}

/* Setup function--runs once at startup. */
void setup() {
  Serial.begin(BAUDRATE);

// Initialize the motor controller if used */
#ifdef USE_BASE
  #ifdef USE_ENCODERS
    // encoder code initializations
    pinMode(LEFT_ENC_CLK, INPUT);
    pinMode(RIGHT_ENC_CLK, INPUT);
    pinMode(LEFT_ENC_DT, INPUT);
    pinMode(RIGHT_ENC_DT, INPUT);
    // attachInterrupt(digitalPinToInterrupt(LEFT_ENC_CLK),ENC_L_ISR,RISING);
    // attachInterrupt(digitalPinToInterrupt(RIGHT_ENC_CLK),ENC_R_ISR,RISING);
  #endif
  initMotorController();
  resetPID();

  // IMU initializations
  #ifdef IMU_READER
    pinMode(IMUSCL, INPUT);  
    pinMode(IMUSDA, INPUT);
    beginIMU();
  #endif

  // IR initializations
  #ifdef IR_READER
    // pinMode(IR_LIN, INPUT);  
    // pinMode(IR_LOUT, OUTPUT);
    // pinMode(IR_RIN, INPUT);  
    // pinMode(IR_ROUT, OUTPUT);
    pinMode(IR_IN, INPUT);  
    pinMode(IR_OUT, OUTPUT);
    // resetTimers();
    resetIR();
    // attachInterrupt(digitalPinToInterrupt(IR_LIN),IR_L_ISRR,RISING);
    // attachInterrupt(digitalPinToInterrupt(IR_LIN),IR_L_ISRF,FALLING);
    // attachInterrupt(digitalPinToInterrupt(IR_RIN),IR_R_ISRR,RISING);
    // attachInterrupt(digitalPinToInterrupt(IR_RIN),IR_R_ISRF,FALLING);

    attachInterrupt(digitalPinToInterrupt(IR_IN),IR_ISRF,FALLING);
  #endif
#endif
}

/* Enter the main loop.  Read and parse input from the serial port
   and run any valid commands. Run a PID calculation at the target
   interval and check for auto-stop conditions.
*/
void loop() {
  // Serial.print("Left: ");
  // Serial.print(leftPID.output);
  // Serial.print(" Right: ");
  // Serial.println(rightPID.output);
  
    // Serial.println("hi"); delay(1000);
  while (Serial.available() > 0) {
    
    // Read the next character
    chr = Serial.read();
    // Serial.println(chr); 
    // Terminate a command with a CR
    if (chr == 13) {
      if (arg == 1) argv1[in_dicks] = NULL;
      else if (arg == 2) argv2[in_dicks] = NULL;
      // Serial.println("run"); 
      runCommand();
      // Serial.println("got run"); 
      resetCommand();
      // Serial.println("reset"); 
    }
    // Use spaces to delimit parts of the command
    else if (chr == ' ') {
      // Step through the arguments
      if (arg == 0) arg = 1;
      else if (arg == 1)  {
        argv1[in_dicks] = NULL;
        arg = 2;
        in_dicks = 0;
      }
      continue;
    }
    else {
      if (arg == 0) {
        // The first arg is the single-letter command
        cmd = chr;
      }
      else if (arg == 1) {
        // Subsequent arguments can be more than one character
        argv1[in_dicks] = chr;
        in_dicks++;
      }
      else if (arg == 2) {
        argv2[in_dicks] = chr;
        in_dicks++;
      }
    }
    
    // Serial.println("hello"); delay(1000);
    #ifdef IMU_READER
      updateIMU();
    #endif

    #ifdef IR_READER
      // updateRanges();
      // updateRangeRight();
      // updateRangeLeft();
      updateRange();
    #endif

    updateEncoders();
  }
  
// If we are using base control, run a PID calculation at the appropriate intervals
#ifdef USE_BASE
  // Serial.print(readEncoder(LEFT));
  //   Serial.print(" ");
  //   Serial.println(readEncoder(RIGHT));
  // Serial.print(getImu(ACCX));
  //   Serial.print(" ");
  //   Serial.print(getImu(ACCY));
  //   Serial.print(" ");
  //   Serial.print(getImu(ACCZ));
  //   Serial.print(" ");
  //   Serial.print(getImu(ROTX));
  //   Serial.print(" ");
  //   Serial.print(getImu(ROTY));
  //   Serial.print(" ");
  //   Serial.println(getImu(ROTZ));
  if (millis() > nextPID) {
    updatePID();
    nextPID += PID_INTERVAL;
  }
  
  // Check to see if we have exceeded the auto-stop interval
  if ((millis() - lastMotorCommand) > AUTO_STOP_INTERVAL) {
    setMotorSpeeds(0, 0);
    if (leftPID.Encoder == leftPID.PrevEnc && rightPID.Encoder == rightPID.PrevEnc) moving = 0;
  }

  //imu sensor reading
  #ifdef IMU_READER
    updateIMU();
  #endif

  #ifdef IR_READER
    // updateRanges();
    // updateRangeRight();
    // updateRangeLeft();
    updateRange();
  #endif

  updateEncoders();
  
#endif

}
