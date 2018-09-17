# Bat Badge 2018  

[![Build Status](https://travis-ci.org/DEAD10C5/bat_mini.svg?branch=master)](https://travis-ci.org/DEAD10C5/bat_mini)



## Serial

You can make a serial connection to the badge using a USB to TTL serial cable. 

For example: 
[USB to TTL Serial Cable](https://www.adafruit.com/product/954)

- Green wire: Connect to serial port, right side looking at back. 
- White wire: Connect to serial port, left side looking at back.
- Black wire: Connect to Battery port, negative (-) port. 
- Red/Orange wire: Do not connect! This is +5V but the board is at +3V. 

## Programming 

We used an Arduino UNO as an ISP to program the attiny84 chip on the badge. 

[Set up the programming environment](http://highlowtech.org/?p=1695)

We did a "6 way" header similar to the one described at the link below. 

[About ISP headers](http://www.batsocks.co.uk/readme/isp_headers.htm)

## Chip Information

ATMEL ATTINY84 / ARDUINO pinout




````
//

//                      +-\/-+

//                VCC 1|      |14 GND

//       `  (D 0) PB0 2|      |13 AREF (D10)

//          (D 1) PB1 3|      |12 PA1 (D9) 

//                PB3 4|      |11 PA2 (D 8) 

// PWM INT0 (D 2) PB2 5|      |10 PA3 (D 7) 

//      PWM (D 3) PA7 6|      |9 PA4(D 6) 

//      PWM (D 4) PA6 7|      |8 PA5(D 5) PWM

//                      +----+

IDE Attiny84 Physical Pin  Usage
  0      PA0           13  Button
  1      PA1           12  Heart
  2      PA2           11  RGB LED Data Pin
  3      PA3           10  Serial TX
  4      PA4            9
  5      PA5            8  Left Eye
  6      PA6            7  Right Eye
  7      PA7            6
  8      PB2            5
  9      PB1            3  Serial RX 
 10      PB0            2     
```
