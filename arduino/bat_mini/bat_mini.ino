/*!
 * @file bat_mini.ino
    ____  _____      _    ____    _  ___     ____ ____
   |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___|
   | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \
   | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
   |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/


   Author : e @p0lr_ @mzbat @theDevilsVoice @dead10c5
   Date   : May 29, 2018
   Version: 0.3
*/

#include "bat.h"

// instantiate bat object
MyBat mybat;

// Create an object for writing to the LED strip.
APA102<dataPin, clockPin> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
rgb_color colors[ledCount];

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(left_eye, OUTPUT);
  pinMode(right_eye, OUTPUT);
  pinMode(heart, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {

    if (mybat.button_state == LOW) {

    switch (mybat.led_pattern_cur) {
      case 1:
        rainbow();
        darkness();
        mybat.led_pattern_cur++;
        break;
      case 2:
        chase();
        darkness();
        mybat.led_pattern_cur++;
        break;
      case 3:
        derp();
        darkness();
        mybat.led_pattern_cur = 1; // button push takes us back to the first pattern
        break;
      default:
        break;
    }
  }

}




