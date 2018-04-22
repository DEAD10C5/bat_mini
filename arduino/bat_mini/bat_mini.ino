/*
    ____  _____      _    ____    _  ___     ____ ____
   |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___|
   | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \
   | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
   |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/


   Author : e @p0lr_ @mzbat @theDevilsVoice @dead10c5
   Date   : April 16, 2018
   Version: 0.1
*/

#include "bat.h"
#include <APA102.h>

// Create an object for writing to the LED strip.
APA102<dataPin, clockPin> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
rgb_color colors[ledCount];


// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(left_eye, OUTPUT);
  pinMode(right_eye, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {

  
  digitalWrite(left_eye, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(right_eye, LOW);
  delay(50);               // wait for a second
  digitalWrite(left_eye, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(right_eye, HIGH);
  delay(50);               // wait for a second
  

  for(uint16_t i = 0; i < ledCount; i++)
  {
    
    if (i%2 == 0) {
      //uint8_t x = time - i * 8;
      colors[i].red = 0;
      colors[i].green = 0;
      colors[i].blue = 255;
    } else {
      colors[i].red = 0;
      colors[i].green = 255;
      colors[i].blue = 0;
    }
    
  }  
  ledStrip.write(colors, ledCount, 10);
  delay(200);
  
  for(uint16_t i = 0; i < ledCount; i++)
    if (i%2 != 0) {
      //uint8_t x = time - i * 8;
      colors[i].red = 0;
      colors[i].green = 0;
      colors[i].blue = 255;
    } else {
      colors[i].red = 0;
      colors[i].green = 255;
      colors[i].blue = 0;
    }
  ledStrip.write(colors, ledCount, 5);
  delay(200);

  /*
  // rainbow
  uint8_t time = millis() >> 4;
  for(uint16_t i = 0; i < ledCount; i++) {
    uint8_t p = time - i * 8;
    colors[i] = hsvToRgb((uint32_t)p * 359 / 256, 255, 255);
  }
  ledStrip.write(colors, ledCount, brightness);
  delay(10);
  */
  

  //led_half_breath();
}




