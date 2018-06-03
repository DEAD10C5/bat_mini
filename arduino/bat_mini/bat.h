/*!
   @file bat.h
    ____  _____      _    ____    _  ___     ____ ____
   |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___|
   | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \
   | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
   |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/


   Author : e @p0lr_ @mzbat @theDevilsVoice @dead10c5
   Date   : May 29, 2018
   Version: 0.3





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

#include <Arduino.h>
//#include <SoftwareSerial.h>
#include <APA102.h>

#define VERSION "0.3"

// Defines for LED pulse code
#define BRIGHT    350     //max led intensity (1-500)
#define INHALE    1250    //Inhalation time in milliseconds.
#define PULSE     INHALE*1000/BRIGHT
#define REST      100    //Rest Between Inhalations.

// ***
// *** Define the RX and TX pins. Choose any two
// *** pins that are unused. Try to avoid D0 (pin 5)
// *** and D2 (pin 7) if you plan to use I2C.
// ***
#define RX    3   // *** D3, Pin 2
#define TX    4   // *** D4, Pin 3

// ***
// *** Define the software based serial port. Using the
// *** name Serial so that code can be used on other
// *** platforms that support hardware based serial. On
// *** chips that support the hardware serial, just
// *** comment this line.
// ***
//SoftwareSerial Serial(RX, TX);

// ***
// *** For Serial TTL Cable:
// *** https://www.adafruit.com/products/954
// ***
// *** Connect 3V  (red)   to Pin 8
// *** Connect GND (black) to Pin 4
// *** Connect RX  (white) to Pin 3
// *** Connect TX  (green) to Pin 2
// ***


const uint16_t ledCount  = 7;
// Set the brightness to use (the maximum is 31).
const uint8_t brightness = 1;
const uint16_t minPower  = 1;
const uint16_t maxPower  = 255 * 31;
const float multiplier   = pow(maxPower / minPower, 1.0 / (ledCount - 1));
const uint8_t  dataPin    = 10;
const uint8_t clockPin   = 11;
const uint8_t left_eye   = 6;
const uint8_t right_eye  = 12;

class MyBat {
  public:
    void led_breath();
    void led_half_breath();
    rgb_color hsvToRgb(uint16_t, uint8_t, uint8_t);
};


#endif
