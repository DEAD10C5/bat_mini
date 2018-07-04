#include <APA102.h>

const uint8_t dataPin    = PA2;
const uint8_t clockPin   = PA3;
// variables will change:
int buttonState = LOW;         // variable for reading the pushbutton status

const int button = 1;

const uint16_t ledCount  = 6;
// Set the brightness to use (the maximum is 31).
;

const uint8_t heart       = 0;
const uint8_t eyes      = 7;

// Create an object for writing to the LED strip.
APA102<dataPin, clockPin> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
rgb_color colors[ledCount];



void setup() {
  pinMode(eyes, OUTPUT);
  pinMode(heart, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(1);
  if (buttonState == LOW) {

    digitalWrite(eyes, HIGH);
    delay(500);
    digitalWrite(eyes, LOW);
    delay(500);

    digitalWrite(heart, HIGH);
    delay(500);
    digitalWrite(heart, LOW);
    delay(500);
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
  }

}
