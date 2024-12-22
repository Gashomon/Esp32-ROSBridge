/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/

#ifndef Pins_Esp_h
#define Pins_Esp_h

#define GPIO_0 0 //PULLUP INPUT
#define GPIO_1 1 //TX PIN
#define GPIO_2 2
#define GPIO_3 3 //RX PIN
#define GPIO_4 4
#define GPIO_5 5
#define GPIO_6 6 //NO EXTERNAL PIN
#define GPIO_7 7 //NO EXTERNAL PIN 
#define GPIO_8 8 //NO EXTERNAL PIN
#define GPIO_9 9 //NO EXTERNAL PIN
#define GPIO_10 10 //NO EXTERNAL PIN
#define GPIO_11 11 //NO EXTERNAL PIN
#define GPIO_12 12 // STRAPPING PIN
#define GPIO_13 13
#define GPIO_14 14 
#define GPIO_15 15 //STRAPPING PIN
#define GPIO_16 16
#define GPIO_17 17
#define GPIO_18 18
#define GPIO_19 19
#define GPIO_21 21
#define GPIO_22 22
#define GPIO_23 23
#define GPIO_25 25
#define GPIO_26 26
#define GPIO_27 27
#define GPIO_32 32
#define GPIO_33 33
#define GPIO_34 34 //INPUT ONLY
#define GPIO_35 35 //INPUT ONLY
#define GPIO_36 36 //INPUT ONLY
#define GPIO_39 39 //INPUT ONLY

// Board Defined Pins source: https://lastminuteengineers.com/esp32-pinout-reference/
static const uint8_t GNDby3V = GPIO_0;
static const uint8_t TX0 = GPIO_1;
static const uint8_t D2 = GPIO_2;
static const uint8_t RX0 = GPIO_3;
static const uint8_t D4 = GPIO_4;
static const uint8_t D5 = GPIO_5;
static const uint8_t D12 = GPIO_12; 
static const uint8_t D13 = GPIO_13;
static const uint8_t D14 = GPIO_14;
static const uint8_t D15 = GPIO_15;
static const uint8_t TX3 = GPIO_16;
static const uint8_t RX3 = GPIO_17;
static const uint8_t D18 = GPIO_18;
static const uint8_t D19 = GPIO_19;
static const uint8_t D21 = GPIO_21;
static const uint8_t D22 = GPIO_22;
static const uint8_t D23 = GPIO_23;
static const uint8_t D25 = GPIO_25;
static const uint8_t D26 = GPIO_26;
static const uint8_t D27 = GPIO_27;
static const uint8_t D32 = GPIO_32;
static const uint8_t D33 = GPIO_33;
static const uint8_t D34 = GPIO_34;
static const uint8_t D35 = GPIO_35;
static const uint8_t D36 = GPIO_36;
static const uint8_t D39 = GPIO_39;

#endif
