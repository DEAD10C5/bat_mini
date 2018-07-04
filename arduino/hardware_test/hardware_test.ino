/*!
   @file hardware_test.ino
    ____  _____      _    ____    _  ___     ____ ____
   |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___|
   | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \
   | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
   |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/


   Author : @dead10c5 @p0lr_ @mzbat @theDevilsVoice
   Date   : July 4, 2018
   Version: 0.1
*/
#include "bat_mini.h"

MyBat mybat;



APA102<dataPin, clockPin> ledStrip;

rgb_color colors[ledCount];

void setup() {
  pinMode(eyes, OUTPUT);
  pinMode(heart, OUTPUT);

  pinMode(button, INPUT);
  mybat.buttonState = LOW;
  mybat.led_pattern_cur = 1;
}

/* Converts a color from HSV to RGB.
   h is hue, as a number between 0 and 360.
   s is the saturation, as a number between 0 and 255.
   v is the value, as a number between 0 and 255. */
rgb_color hsvToRgb(uint16_t h, uint8_t s, uint8_t v)
{
  uint8_t f = (h % 60) * 255 / 60;
  uint8_t p = (255 - s) * (uint16_t)v / 255;
  uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
  uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
  uint8_t r = 0, g = 0, b = 0;
  switch ((h / 60) % 6) {
    case 0: r = v; g = t; b = p; break;
    case 1: r = q; g = v; b = p; break;
    case 2: r = p; g = v; b = t; break;
    case 3: r = p; g = q; b = v; break;
    case 4: r = t; g = p; b = v; break;
    case 5: r = v; g = p; b = q; break;
  }
  return rgb_color(r, g, b);
}

void rainbow() {
mybat.buttonState = HIGH;
delay(100);
  while(mybat.buttonState != LOW) {

    uint8_t time = millis() >> 4;
    for (uint16_t i = 0; i < ledCount; i++) {
      uint8_t p = time - i * 8;
      colors[i] = hsvToRgb((uint32_t)p * 359 / 256, 255, 255);
    }
    ledStrip.write(colors, ledCount, brightness);
    delay(10);

    mybat.buttonState = digitalRead(1);
  } 

  // turn off the rgb leds
  for (uint16_t i = 0; i < ledCount; i++) {
    colors[i] = hsvToRgb(0, 0, 0);
  }
  ledStrip.write(colors, ledCount, 0);
}

void derp() {
  do {
    digitalWrite(eyes, HIGH);
    delay(500);
    digitalWrite(eyes, LOW);
    delay(500);

    digitalWrite(heart, HIGH);
    delay(500);
    digitalWrite(heart, LOW);
    delay(500);
    mybat.buttonState = digitalRead(1);
  } while (mybat.buttonState != HIGH);
}

void loop() {


  mybat.buttonState = digitalRead(1);

  if (mybat.buttonState == LOW) {

    switch (mybat.led_pattern_cur) {
      case 1:
        rainbow();
        mybat.led_pattern_cur++;
        break;
      case 2:
        derp();
        mybat.led_pattern_cur = 1;
        break;
      default:
        break;
    }

  }

}

