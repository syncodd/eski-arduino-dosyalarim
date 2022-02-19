/*
** Test of R06A RF decoder e/w SC2272-T4
**
** This example uses a SainSmart I2C LCD2004 adapter for HD44780 LCD screens
**
** LCD2004 Address pins 0,1 & 2 are all permenantly tied high so the address
** is fixed at 0x27
**
** Written for and tested with Arduino 1.0
** This example uses F Malpartida's NewLiquidCrystal library. Obtain from:
** https://bitbucket.org/fmalpartida/new-liquidcrystal
**
** Edward Comer
** LICENSE: GNU General Public License, version 3 (GPL-3.0)
**
** NOTE: Tested on Arduino NANO whose I2C pins are A4==SDA, A5==SCL
**       INT0 is on D2
** Wiring for Nano: A4->SDA, A5->SCL
*/
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

// These pins are on the PCF8574 I/O expander for I2C-bus, not the nano
#define I2C_ADDR    0x27  // Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

#define  LED_OFF  0
#define  LED_ON  1

#define  PIN_D2_INT  0

// R06A defines - wired to Digital Arduino pins
// Wire the R06A per this assignment
#define R06A_VT 2    // used for INT0
#define R06A_D0 3
#define R06A_D1 4
#define R06A_D2 5
#define R06A_D3 6

int r06a_0, r06a_1, r06a_2, r06a_3 = 0; // storage for data states
int dirty = 0;                          // interrupt has occurred flag

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

// Interrupt Service Routine attached to INT0 vector
void pinD2ISR()
{
   // Provide a visual clue of the interrupt
   digitalWrite(13, !digitalRead(13));  // Toggle LED on pin 13
   // Grab the data states
   r06a_0 = digitalRead(R06A_D0);      // Grab data for later consumption in loop()
   r06a_1 = digitalRead(R06A_D1);
   r06a_2 = digitalRead(R06A_D2);
   r06a_3 = digitalRead(R06A_D3);
   dirty = 1;       // flag interrupt occurance
}

void setup()
{
 lcd.begin (20,4);
 
// Switch on the backlight
 lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
 lcd.setBacklight(LED_ON);
 
 lcd.home ();                     // Home
 lcd.print("Test of R06A Decoder"); // Logo 1st line
 lcd.setCursor ( 0, 2 );          // Go to the 3rd line
 lcd.print("DAT3 DAT2 DAT1 DAT0");
 
 attachInterrupt(PIN_D2_INT, pinD2ISR, RISING); // Set D2 interrupt
 
 // setup the R06A decoder connections
 pinMode(R06A_D0, INPUT);
 pinMode(R06A_D1, INPUT);
 pinMode(R06A_D2, INPUT);
 pinMode(R06A_D3, INPUT);
}

void loop()
{
  if(dirty)
  {
    dirty = 0;    // clear interrupt occurance flag
    lcd.setCursor (15,3);     // go to LCD col 15 of line 4
    lcd.print(r06a_0 ? "HIGH": "LOW ");
    lcd.setCursor (10,3);     // go to LCD col 10 of line 4
    lcd.print(r06a_1 ? "HIGH": "LOW ");
    lcd.setCursor (5,3);      // go to LCD col 5 of line 4
    lcd.print(r06a_2 ? "HIGH": "LOW ");
    lcd.setCursor (0,3);      // go to LCD col 0 of line 4
    lcd.print(r06a_3 ? "HIGH": "LOW ");
  }
}
