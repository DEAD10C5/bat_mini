/*!
   @file bat_mini.h
    ____  _____      _    ____    _  ___     ____ ____
   |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___|
   | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \
   | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
   |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/


   Author : @p0lr_ @mzbat @theDevilsVoice @dead10c5
   Date   : September 20th, 2018
   Version: 1.2

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

IDE Attiny84 Physical Pin
  0      PA0           13
  1      PA1           12
  2      PA2           11
  3      PA3           10
  4      PA4            9
  5      PA5            8
  6      PA6            7
  7      PA7            6
  8      PB2            5
  9      PB1            3
 10      PB0            2

*/
#ifndef BAT_H
#define BAT_H

#define VERSION "1.2"
#define LEDBLINK_MS     1000  // Blink rate (in milliseconds)

#include <Arduino.h>
#include <APA102.h>
#include <SoftwareSerial.h>

// ***
// *** Define the RX and TX pins. Choose any two
// *** pins that are unused. Try to avoid D0 (pin 5)
// *** and D2 (pin 7) if you plan to use I2C.
// ***
#define RX    3
#define TX    10

/*
 *     
 *  3V3/5V - This wire is optional and can be used to power your circuit during testing. You can power your circuit only when the 
 *  current demand is limited (less than 500 mA). This wire is usually red (color may be vary).
    GND - This wire is required and should be connected to pin 4 on the ATtiny85 (or to whatever point you designated as ground). 
    This wire is usually black (color may be vary).
    TX - This wire is used by the external device to send data to your ATtiny85. This wire should be connected to the pin you 
    designated as RX when you setup your Software Serial instance. On FTDI cables, this wire is usually orange. On the USB to TTL 
    Serial Cable this wire is usually green (color may be vary).
    RX - This wire is used by the external device to receive data from your ATtiny85. This wire should be connected to the pin 
    you designated as TX when you setup your Software Serial instance. On FTDI cables, this wire is usually yellow. On the USB 
    to TTL Serial Cable this wire is usually white (color may be vary).
 */

// pins'n'stuff
const uint8_t  DATA_PIN   = PA2;
const uint8_t  CLOCK_PIN  = PA3;
const uint8_t  RIGHT_EYE  = 7;
const uint8_t  LEFT_EYE   = 8;
const uint8_t  HEART      = 0;
const uint8_t  BUTTON     = 1;
const uint16_t LED_COUNT  = 6;
const uint8_t  BRIGHTNESS = 1;


class MyBat {
  public:
    int buttonState;         // variable for reading the pushbutton status
    uint8_t led_pattern_cur;
    
    rgb_color hsvToRgb(uint16_t, uint8_t, uint8_t);
};

#endif
