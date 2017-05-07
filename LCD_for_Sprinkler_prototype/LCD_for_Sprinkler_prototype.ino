//LCD PROTOTYPE FOR SPRINKLER SYSTEM - by Joao Borges
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
byte Bar1[8] = {
  B10000,
  B01000,
  B01000,
  B00100,
  B00100,
  B00010,
  B00010,
  B00001
};
byte Bar2[8] = {
  B00001,
  B00010,
  B00010,
  B00100,
  B00100,
  B01000,
  B01000,
  B10000
};
byte ParBar[8] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000
};
byte VertBar[8] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};
byte FifteenMin[8] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0}; // fetching time indicator
byte raindrop[8] = {0x4, 0x4, 0xA, 0xA, 0x11, 0xE, 0x0,}; // fetching Valve Data indicator

// General Variables
int Clock_Animation_time=200;

//others
#define VALVE_RESET_TIME 7500UL 

void setup()
{
 //    Basic Initiatization procedures //
  lcd.init();                      // initialize the lcd 
  lcd.init();
  lcd.createChar(0, Bar1);
  lcd.createChar(1, Bar2);
  lcd.createChar(2, ParBar);
  lcd.createChar(3, VertBar);
  lcd.createChar(4, FifteenMin);
  lcd.createChar(5, raindrop);
  lcd.backlight();
  //////// MAIN INTRO SCREEN, print and stay 2s /////////
  lcd.setCursor(0,0);
  lcd.print("Sprinkler     v1.1");
  lcd.setCursor(2,1);
  lcd.print("My Sensors System");
   lcd.setCursor(0,2);
  lcd.print("              ");
   lcd.setCursor(2,3);
  lcd.print("Joao Borges");
  delay(2000);                // REPLACE WITH WAIT WHEN INTEGRATING WITH MYSENSORS
  lcd.setCursor(0,2);
  lcd.print("  Initializing.......");
  lcd.setCursor(1,1);
  lcd.print("Zone1 Time: 03:59 x");
  lcd.setCursor(8,1);
  lcd.write(4);
  lcd.setCursor(0,2);
  lcd.print("");
  lcd.setCursor(10,3);
  lcd.write(5);
  delay(200);
}


void loop()
{
  lcd.setCursor(19,1);
  lcd.write(0);
  delay(Clock_Animation_time);
  lcd.setCursor(19,1);
  lcd.write(3);
  delay(Clock_Animation_time);
  lcd.setCursor(19,1);
  lcd.write(1);
  delay(Clock_Animation_time);
  lcd.setCursor(19,1);
  lcd.write(2);
  delay(Clock_Animation_time);
}


