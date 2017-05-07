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
byte face[8] = {  0x01,
  0x03,
  0x02,
  0x06,
  0x16,
  0x1C,
  0x0C,
  0x08};
byte FifteenMin[8] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0}; // fetching time indicator
byte raindrop[8] = {0x4, 0x4, 0xA, 0xA, 0x11, 0xE, 0x0,}; // fetching Valve Data indicator
typedef enum {
  STAND_BY_ALL_OFF, RUN_SINGLE_ZONE, RUN_ALL_ZONES, CYCLE_COMPLETE, ZONE_SELECT_MENU, CANCELLING
}  SprinklerStates;
SprinklerStates state = STAND_BY_ALL_OFF;   //define variable called state, of the type SprinklerStates
SprinklerStates lastState;                  //define variable called lastState, of the type SprinklerStates
//typedef enum {
//  RUN_ALL, RUN_Zone_1, RUN_Zone_2, RUN_Zone_3, Config
//}  MainMenuStates;
//MainMenuStates MainMenu_Current_State = RUN_ALL;
byte MainMenu_Current_State = 0;       // 0 is Run all, 1= zone1, 2=zone2, 3= zone3, 4 = config
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
  lcd.createChar(6, face);
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
  // TURN RELAYS OFF
  MainMenu(MainMenu_Current_State);
}


void loop()
{
  updateDisplay();            // Call update display function
  switch (state) {
    case STAND_BY_ALL_OFF:
        if (DOWNbuttonPushed)
        {
           if (MainMenu_Current_State == 4)  MainMenu_Current_State = 0;
              else MainMenu_Current_State++;
           MainMenu(MainMenu_Current_State);
         }
        else if (0==0)
          {
          }
   
    break;
    case RUN_SINGLE_ZONE:
    break;
    case RUN_ALL_ZONES:
    break;
    case CANCELLING:
    break;
  }

  
  if (DOWNbuttonPushed)
  {
    
  }
    else if (0==0)
    {
    }
   
}



