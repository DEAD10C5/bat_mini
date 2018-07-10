/*!
   @file bat_mini.h
    ____  _____      _    ____    _  ___     ____ ____
   |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___|
   | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \
   | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
   |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/


   Author : @p0lr_ @mzbat @theDevilsVoice @dead10c5
   Date   : July 4, 2018
   Version: 0.1





                    ATMEL ATTINY84 / ARDUINO

                             +-\/-+
                       VCC  1|    |14  GND
               (D  0)  PB0  2|    |13  AREF (D 10)
               (D  1)  PB1  3|    |12  PA1  (D  9)
                       PB3  4|    |11  PA2  (D  8)
    PWM  INT0  (D  2)  PB2  5|    |10  PA3  (D  7)
    PWM        (D  3)  PA7  6|    |9   PA4  (D  6)
    PWM        (D  4)  PA6  7|    |8   PA5  (D  5)        PWM
                             +----+


*/
#ifndef BAT_H
#define BAT_H
#define VERSION "0.1"

// Defines for LED pulse code
#define BRIGHT    31    //max led intensity (1-500)
#define INHALE    1250    //Inhalation time in milliseconds.
#define PULSE     INHALE*1000/BRIGHT
#define REST      100    //Rest Between Inhalations.

#include <Arduino.h>
#include <APA102.h>

// pins'n'stuff
const uint8_t dataPin    = PA2;
const uint8_t clockPin   = PA3;
const uint8_t heart      = PA7;
const uint8_t left_eye   = PB2;
const uint8_t right_eye  = 0;
const uint8_t button     = 1;
const uint16_t ledCount  = 6;
const uint8_t brightness = 10;


class MyBat {
  public:
    int buttonState;         // variable for reading the pushbutton status
    uint8_t led_pattern_cur;
    
    rgb_color hsvToRgb(uint16_t, uint8_t, uint8_t);
};

#endif
