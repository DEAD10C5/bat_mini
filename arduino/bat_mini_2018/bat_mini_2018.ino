/*!
   @file hardware_test.ino
    ____  _____      _    ____    _  ___     ____ ____
   |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___|
   | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \
   | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
   |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/


   Author : @dead10c5 @p0lr_ @mzbat @theDevilsVoice
   Date   : September 20th, 2018
   Version: 1.2
*/
#include "bat_mini.h"
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>


SoftwareSerial Serial(RX, TX);

MyBat mybat;

APA102<DATA_PIN, CLOCK_PIN> ledStrip;

rgb_color colors[LED_COUNT];

long heartBeatArray[] = {
  50, 100, 15, 1200
};
int hbeatIndex = 1;   // this initialization is important or it starts on the "wrong foot"
long prevMillis;

/*
Code for enabling CPU sleep to attempt to increase battery life 
*/

/* void sleep_function(void)
{ 
  sbi(PCMSK1, PCINT8); //enable interrupt again
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);//set deep sleep mode
  sleep_enable(); //enable sleep
  sleep_mode(); //start sleep
  sleep_disable(); //code continues here after wake up
  return;
}
*/

void setup_watchdog(int ii) 
{
  // 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
  // 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec

  uint8_t bb;
  if (ii > 9 ) ii=9;
  bb=ii & 7;
  if (ii > 7) bb|= (1<<5);
  bb|= (1<<WDCE);

  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCSR = bb;
  WDTCSR |= _BV(WDIE);
}


// system wakes up when watchdog is timed out
void system_sleep() 
{
  cbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter OFF
  setup_watchdog(3);                   // approximately 128 mseconds sleep
 
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();
  sei();                               // Enable the Interrupts so the wdt can wake us up

  sleep_mode();                        // System sleeps here

  sleep_disable();                     // System continues execution here when watchdog timed out 
  sbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter ON
}


/*
   (pin, intensity 0 (off) to 255 (max) )
*/
void eyes() {
  for (int i = -255; i <= 254; i++) {
    analogWrite(LEFT_EYE, abs(i));
    analogWrite(RIGHT_EYE, abs(i));
    delay(1);
  }
} // eyes()



void heartBeat(float tempo) {


  if ((millis() - prevMillis) > (long)(heartBeatArray[hbeatIndex] * tempo)) {
    hbeatIndex++;
    if (hbeatIndex > 3) hbeatIndex = 0;

    if ((hbeatIndex % 2) == 0) {
      digitalWrite(HEART, HIGH);
      delay((int)heartBeatArray[hbeatIndex]) ;
      digitalWrite(HEART, LOW);
      delay(150);
      digitalWrite(HEART, HIGH);
      delay((int)heartBeatArray[hbeatIndex]) ;
      digitalWrite(HEART, LOW);
    }
    hbeatIndex++;
    Serial.println(hbeatIndex);
    prevMillis = millis();

  }

}

void darkness() {

  // turn off the rgb leds
  for (uint16_t i = 0; i < LED_COUNT; i++) {
    colors[i] = mybat.hsvToRgb(0, 0, 0);
  }
  ledStrip.write(colors, LED_COUNT, 0);

  // turn off other LEDs
  digitalWrite(LEFT_EYE, LOW);
  digitalWrite(RIGHT_EYE, LOW);
  digitalWrite(HEART, LOW);

} // darkness()

void rainbow() {

  mybat.buttonState = HIGH;
  system_sleep();

  while (mybat.buttonState != LOW) {

    uint8_t time = millis() >> 4;
    for (uint16_t i = 0; i < LED_COUNT; i++) {
      uint8_t p = time - i * 8;
      colors[i] = mybat.hsvToRgb((uint32_t)p * 359 / 256, 255, 255);
    }
    ledStrip.write(colors, LED_COUNT, BRIGHTNESS);
    system_sleep();

    mybat.buttonState = digitalRead(1);
  }

} //rainbow()

void flicker() {

  mybat.buttonState = HIGH;
  system_sleep();

  while (mybat.buttonState != LOW) {


    // pulse the eyes all the time
    eyes();

    //heartbeat();
    heartBeat(1.0);

    uint8_t time = millis() >> 4;
    for (uint16_t i = 0; i < LED_COUNT; i++) {
      uint8_t p = time - i * 8;
      colors[i] = mybat.hsvToRgb((uint32_t)p * 359 / 256, 255, 255);
    }
    ledStrip.write(colors, LED_COUNT, BRIGHTNESS);
    system_sleep();

    mybat.buttonState = digitalRead(1);
  }
} // flicker()


void sin_wave() {

  mybat.buttonState = HIGH;
  system_sleep();
  float tcount = 0.0;
  int ibright = 0;
  int ihue = random(0, 255);
  while (mybat.buttonState != LOW) {

    // pulse the eyes all the time
    eyes();

    heartBeat(0.5);

    for (int i = 0; i < LED_COUNT; i++ ) {
      tcount = tcount + .1;
      if (tcount > 3.14) {
        tcount = 0.0;
      }
      ibright = int(sin(tcount) * 255);
      colors[i] = mybat.hsvToRgb(ihue, 255, 255);
      ledStrip.write(colors, LED_COUNT, ibright);
      system_sleep();
    }

    ledStrip.write(colors, LED_COUNT, 10);
    system_sleep();
    mybat.buttonState = digitalRead(1);
  }
} // sin_wave()

void color_pop() {

  mybat.buttonState = HIGH;
  system_sleep();

  int idex = random(0, LED_COUNT);
  int ihue = random(0, 255);

  while (mybat.buttonState != LOW) {
    // pulse the eyes all the time
    eyes();
    heartBeat(0.5);
    colors[idex] = mybat.hsvToRgb(ihue, 255, 255);
    ledStrip.write(colors, LED_COUNT, BRIGHTNESS);
    system_sleep();
    idex = random(0, LED_COUNT);
    ihue = random(0, 255);
    mybat.buttonState = digitalRead(1);
  }
} // color_pop()

void cyber_police() {

  mybat.buttonState = HIGH;
  system_sleep();
  while (mybat.buttonState != LOW) {
    // pulse the eyes all the time
    eyes();
    heartBeat(0.5);
    for (uint16_t i = 0; i < LED_COUNT; i++)
    {
      if (i % 2 == 0) {
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
    ledStrip.write(colors, LED_COUNT, 10);
    mybat.buttonState = digitalRead(1);
    system_sleep();
    // pulse the eyes all the time
    eyes();
    heartBeat(0.5);
    for (uint16_t i = 0; i < LED_COUNT; i++)
      if (i % 2 != 0) {
        //uint8_t x = time - i * 8;
        colors[i].red = 0;
        colors[i].green = 0;
        colors[i].blue = 255;
      } else {
        colors[i].red = 0;
        colors[i].green = 255;
        colors[i].blue = 0;
      }
    ledStrip.write(colors, LED_COUNT, 5);
    mybat.buttonState = digitalRead(1);
    system_sleep();
  }
} //cyber_police()

void led_only() {

  mybat.buttonState = HIGH;
  system_sleep();

  while (mybat.buttonState != LOW) {
    // pulse the eyes all the time
    eyes();
    heartBeat(0.5);
    system_sleep();
    mybat.buttonState = digitalRead(1);
  }

} //led_only()

void setup() {
  Serial.begin(9600);
  Serial.println("##############################");
  Serial.println("# DE:AD:10:C5 Bat Badge 2018 #");
  Serial.println("##############################");
  Serial.println("This badge was a lot of work and a lot of fun. Hope you enjoy it!");
  Serial.println("...");
  Serial.print("Version: ");
  Serial.println(VERSION);
  Serial.println("Initializing...");
  pinMode(LEFT_EYE, OUTPUT);
  pinMode(RIGHT_EYE, OUTPUT);
  pinMode(HEART, OUTPUT);
  pinMode(BUTTON, INPUT);
  mybat.buttonState = LOW;
  mybat.led_pattern_cur = 1;
  Serial.println("Complete!");
}

void loop() {

  Serial.println("Time to make a selection...");

  if (mybat.buttonState == LOW) {
    switch (mybat.led_pattern_cur) {
      case 1:
        flicker();
        darkness();
        mybat.led_pattern_cur++;
        break;
      case 2:
        sin_wave();
        darkness();
        mybat.led_pattern_cur++;
        break;
      case 3:
        color_pop();
        darkness();
        mybat.led_pattern_cur++;
        break;
      case 4:
        rainbow();
        darkness();
        mybat.led_pattern_cur++;
        break;
      case 5:
        cyber_police();
        darkness();
        mybat.led_pattern_cur++;
        break;
      case 6:
        led_only();
        mybat.led_pattern_cur = 1; // button push takes us back to the first pattern
        break;
      default:
        break;
    }
  }
}
