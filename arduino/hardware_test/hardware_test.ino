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
  pinMode(left_eye, OUTPUT);
  pinMode(right_eye, OUTPUT);
  pinMode(heart, OUTPUT);

  pinMode(button, INPUT);
  mybat.buttonState = LOW;
  mybat.led_pattern_cur = 1;
}

void loop() {
  int my_brightness = 1;  // Set the brightness to use
  int step = 1;
  analogWrite(heart, my_brightness);
  my_brightness = my_brightness + step;
  if (my_brightness >= 255)
    my_brightness = 0;

  if (mybat.buttonState == LOW) {

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

void rainbow() {

  mybat.buttonState = HIGH;
  delay(100);
  while (mybat.buttonState != LOW) {

    uint8_t time = millis() >> 4;
    for (uint16_t i = 0; i < ledCount; i++) {
      uint8_t p = time - i * 8;
      colors[i] = mybat.hsvToRgb((uint32_t)p * 359 / 256, 255, 255);
    }
    ledStrip.write(colors, ledCount, brightness);
    delay(10);

    mybat.buttonState = digitalRead(1);
  }
}

void chase() {
  mybat.buttonState = HIGH;
  delay(100);

  digitalWrite(left_eye, HIGH);
  digitalWrite(right_eye, HIGH);
  digitalWrite(heart, HIGH);

  while (mybat.buttonState != LOW) {
    for (uint16_t i = 0; i < ledCount; i++) {
      for (uint16_t j = 0; j < ledCount; j++) {
        if (i != j) {
          colors[i] = mybat.hsvToRgb(0, 0, 0);
        } else {
          colors[i] = mybat.hsvToRgb(240, 255, 255);
        }
      }
      ledStrip.write(colors, ledCount, 0);
      delay(250);
    }
    mybat.buttonState = digitalRead(1);
  }
}

void derp() {
  mybat.buttonState = HIGH;
  delay(100);
  while (mybat.buttonState != LOW) {
    digitalWrite(right_eye, HIGH);
    digitalWrite(left_eye, HIGH);
    delay(500);
    digitalWrite(right_eye, LOW);
    digitalWrite(left_eye, LOW);
    delay(500);

    digitalWrite(heart, HIGH);
    delay(500);
    digitalWrite(heart, LOW);
    delay(500);
    mybat.buttonState = digitalRead(1);
  }

}

void led_half_breath() {
  //ramp decreasing intensity, Exhalation (half time):
  for (int i = BRIGHT - 1; i > 0; i--) {
    digitalWrite(heart, LOW);          // turn the LED on.
    //digitalWrite(right_eye, LOW);
    delayMicroseconds(i * 10);        // wait
    digitalWrite(heart, HIGH);         // turn the LED off.
    //digitalWrite(right_eye, HIGH);
    delayMicroseconds(PULSE - i * 10); // wait
    i--;
    delay(0);                        //to prevent watchdog firing.
  }
  delay(REST);                       //take a rest...
}

/*
   Pulse the Internal LED
*/
void led_breath() {
  //ramp increasing intensity, Inhalation:
  for (int i = 1; i < BRIGHT; i++) {
    digitalWrite(left_eye, HIGH);         // turn the LED on.
    digitalWrite(right_eye, HIGH);
    delayMicroseconds(i * 10);       // wait
    digitalWrite(left_eye, LOW);         // turn the LED off.
    digitalWrite(right_eye, LOW);
    delayMicroseconds(PULSE - i * 10); // wait
    delay(0);                        //to prevent watchdog firing.
  }
}

void darkness() {
  // turn off the rgb leds
  for (uint16_t i = 0; i < ledCount; i++) {
    colors[i] = mybat.hsvToRgb(0, 0, 0);
  }
  ledStrip.write(colors, ledCount, 0);

  digitalWrite(left_eye, LOW);
  digitalWrite(right_eye, LOW);
  digitalWrite(heart, LOW);
}

