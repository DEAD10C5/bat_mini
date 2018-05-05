/*
 *  ____  _____      _    ____    _  ___     ____ ____  
 * |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___| 
 * | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \ 
 * | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
 * |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/ 
 *                                                    
 *                                                    
 * Author : e @p0lr_ @mzbat @theDevilsVoice @dead10c5
 * Date   : April 16, 2018
 * Version: 0.1
 */
#ifndef BAT_H
#define BAT_H

#include <Arduino.h>
//#include <SoftwareSerial.h>
#include <APA102.h>

#define VERSION "0.2"

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
// Defines for LED pulse code
#define BRIGHT    350     //max led intensity (1-500)
#define INHALE    1250    //Inhalation time in milliseconds.
#define PULSE     INHALE*1000/BRIGHT
#define REST      100    //Rest Between Inhalations.
// Set the brightness to use (the maximum is 31).
const uint8_t brightness = 1;
const uint16_t minPower = 1;
const uint16_t maxPower = 255 * 31;
const float multiplier = pow(maxPower / minPower, 1.0 / (ledCount - 1));

const uint8_t dataPin    = PA3;
const uint8_t clockPin   = PA2;
const uint8_t  left_eye  = PA7;
const uint8_t  right_eye = PA1;

void led_breath();
void led_half_breath();
rgb_color hsvToRgb(uint16_t, uint8_t, uint8_t);

#endif 
