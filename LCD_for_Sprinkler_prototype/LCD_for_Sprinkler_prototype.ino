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
unsigned long startMillis;
bool DOWNbuttonPushed = false;

//Hardware
const int DOWN_Pin = 3;

//others
#define VALVE_RESET_TIME 7500UL 


/********************/
void setup()
{
 //    Basic Initiatization procedures //
  lcd.init();                       // initialize the LCD
  lcd.init();                       // initialize the LCD
  lcd.createChar(0, Bar1);          // Create custom character in LCD
  lcd.createChar(1, Bar2);          // Create custom character in LCD
  lcd.createChar(2, ParBar);        // Create custom character in LCD
  lcd.createChar(3, VertBar);       // Create custom character in LCD
  lcd.createChar(4, FifteenMin);    // Create custom character in LCD
  lcd.createChar(5, raindrop);      // Create custom character in LCD
  lcd.backlight();                  // Turn on Back light (to tur off is lcd.noBacklight()
  attachInterrupt(digitalPinToInterrupt(DOWN_Pin), DownButtonPress, RISING);
  
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
  lcd.init();
  MainMenu();
}


void loop()
{
  
  if (DOWNbuttonPushed)
  {
    
  }
}


