//LCD PROTOTYPE FOR SPRINKLER SYSTEM - by Joao Borges
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define DEBUG_ON   // comment out to supress serial monitor output
#ifdef DEBUG_ON
#define DEBUG_PRINT(x)   Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#define SERIAL_START(x)
#endif


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
unsigned long timeRemaining;
unsigned long timeRemainingMinutes;
unsigned long timeRemainingSeconds;
bool DOWNbuttonPushed = false;
bool ENTERbuttonPushed = false;
unsigned long nowMillis;

//Flashmap
unsigned long SINGLEVALVETIME=10000;   // 10 minutes * 60 *1000 time in milliseconds
unsigned long Zone1TimeAuto = 11000;
unsigned long Zone2TimeAuto = 9000;
unsigned long Zone3TimeAuto = 5000;

//Hardware
const int DOWN_Pin = 3;
const int ENTER_Pin = 4;
const int MENU_Pin = 5;
int RunValve = 0;

//others
#define VALVE_RESET_TIME 7500UL 


/********************/
/********************/
/********************/
/********************/
void setup()
{
  Serial.begin(115200);
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
  attachInterrupt(digitalPinToInterrupt(ENTER_Pin), ENTERbuttonPress, RISING);
  
  //////// MAIN INTRO SCREEN, print and stay 2s /////////
  lcd.setCursor(0,0);
  lcd.print("Sprinkler     v1.1");
  lcd.setCursor(2,1);
  lcd.print("My Sensors System");
  lcd.setCursor(0,2);
  lcd.print("              ");
  lcd.setCursor(2,3);
  lcd.print("Joao Borges");
  delay(2000);                //////// REPLACE WITH WAIT WHEN INTEGRATING WITH MYSENSORS
  lcd.init();
  // TURN RELAYS OFF
  MainMenu(MainMenu_Current_State);
}




/********************/
/********************/
/********************/
void loop()
{
  delay(100);
  if (Serial.available()>0) 
    {
    String a;
    a = Serial.read();
    DEBUG_PRINT(a);
    DEBUG_PRINT("   Current State = ");
    DEBUG_PRINT(state);
    DEBUG_PRINT("   MainMenu Current state = ");
    DEBUG_PRINTLN(MainMenu_Current_State);
    if (a=="50")  ENTERbuttonPushed=true; 
    else 
        {   lcd.backlight(); //lcd.backlight;
            DOWNbuttonPushed = true;
        }

    }


    
  switch (state) {
    case STAND_BY_ALL_OFF:
        if (DOWNbuttonPushed)
        {
           if (MainMenu_Current_State == 4)  MainMenu_Current_State = 0;
              else MainMenu_Current_State++;
           MainMenu(MainMenu_Current_State);
           DOWNbuttonPushed = false;
         }
        else if (ENTERbuttonPushed)
          {
            if (MainMenu_Current_State==0)
              {
                    state=RUN_ALL_ZONES;
                    fastClear(); 
                    startMillis=millis();
                    ENTERbuttonPushed=false;
                    Run_All_Zones_Menu();
                    RunValve=1;
                    //Turn Relay 1 on
              }
              else if(MainMenu_Current_State==1)             
                {
                    state=RUN_SINGLE_ZONE;
                    RunValve=1;
                    fastClear(); 
                    SingleZoneScreenManagement(RunValve);
                    timeRemaining=SINGLEVALVETIME;
                    startMillis=millis();
                    ENTERbuttonPushed=false;
                }
                else if(MainMenu_Current_State==2)
                    {
                      state=RUN_SINGLE_ZONE;
                      RunValve=2;
                      fastClear();
                      SingleZoneScreenManagement(RunValve);
                      timeRemaining=SINGLEVALVETIME;
                      startMillis=millis();
                      ENTERbuttonPushed=false;
                    }
                  else if(MainMenu_Current_State==3)
                      {
                        state=RUN_SINGLE_ZONE;
                        RunValve=3;
                        fastClear();
                        SingleZoneScreenManagement(RunValve);
                        timeRemaining=SINGLEVALVETIME;
                        startMillis=millis();
                        ENTERbuttonPushed=false;
                      }
                    else {}
                
          }
      break;
    
    case RUN_SINGLE_ZONE:
          nowMillis = millis();
          if ((nowMillis-startMillis)>SINGLEVALVETIME)
            {
              //Turn_Relay_Off
              state=STAND_BY_ALL_OFF;
              MainMenu_Current_State=0;
              MainMenu(MainMenu_Current_State);
              }
              else {
                  timeRemaining = (SINGLEVALVETIME-(nowMillis-startMillis));
                  timeRemainingMinutes=timeRemaining/60000;
                  timeRemainingSeconds=(timeRemaining/1000)-(timeRemainingMinutes*60);
                  lcd.setCursor(14,3);
                  lcd.print(timeRemainingMinutes);
                  lcd.print(":");
                  if (timeRemainingSeconds<10) lcd.print("0");
                  lcd.print(timeRemainingSeconds);
                  Serial.print("Time Remaining: ");
                  Serial.print(timeRemaining);
                  Serial.print("    Millis function:  ");
                  Serial.println(nowMillis);
              }
        
      break;
    
    case RUN_ALL_ZONES:
          nowMillis = millis();
          if (RunValve==1)
          {
            if ((nowMillis-startMillis)>Zone1TimeAuto)
            {
              // TURN RELAY 1 off and TURN RELAY 2 ON
              RunValve=2;
              startMillis=millis();
              lcd.setCursor (18,1);
              lcd.print(" ");                                   //raindrop icon
            }
            else{
                  timeRemaining = (Zone1TimeAuto-(nowMillis-startMillis));
                  timeRemainingMinutes=timeRemaining/60000;
                  timeRemainingSeconds=(timeRemaining/1000)-(timeRemainingMinutes*60);
                  lcd.setCursor(12,1);
                  if (timeRemainingMinutes<10) lcd.print("0");
                  lcd.print(timeRemainingMinutes);
                  lcd.print(":");
                  if (timeRemainingSeconds<10) lcd.print("0");
                  lcd.print(timeRemainingSeconds);
                  //AnimeateProgressIcon(true, 100, 18, 1);
                  lcd.setCursor (18,1);
                  lcd.write(5);                                   //raindrop icon
                  Serial.print("Time Remaining: ");
                  Serial.print(timeRemaining);
                  Serial.print("    Run Valve  ");
                  Serial.println(RunValve);
            }
          }
          MainMenu_Current_State=0;
          if(RunValve==2) {
            if ((nowMillis-startMillis)>Zone2TimeAuto)
            {
              // TURN RELAY 2 off and TURN RELAY 3 ON
              RunValve=3;
              startMillis=millis();
              lcd.setCursor (18,2);
              lcd.print(" ");                                   //raindrop icon
            }
               else{
                  timeRemaining = (Zone2TimeAuto-(nowMillis-startMillis));
                  timeRemainingMinutes=timeRemaining/60000;
                  timeRemainingSeconds=(timeRemaining/1000)-(timeRemainingMinutes*60);
                  lcd.setCursor(12,2);
                  if (timeRemainingMinutes<10) lcd.print("0");
                  lcd.print(timeRemainingMinutes);
                  lcd.print(":");
                  if (timeRemainingSeconds<10) lcd.print("0");
                  lcd.print(timeRemainingSeconds);
                  lcd.setCursor (18,2);
                  lcd.write(5);                                   //raindrop icon
                  Serial.print("Time Remaining: ");
                  Serial.print(timeRemaining);
                  Serial.print("    Run Valve  ");
                  Serial.println(RunValve);
                   }
          } else if(RunValve==3) {
                if ((nowMillis-startMillis)>Zone3TimeAuto)
                {
                  // TURN RELAY 2 off and TURN RELAY 3 ON
                  RunValve=1;
                  startMillis=millis();
                  state=STAND_BY_ALL_OFF;
                  MainMenu_Current_State=0;
                  MainMenu(MainMenu_Current_State);
                  
                 }
                 else{
                  timeRemaining = (Zone3TimeAuto-(nowMillis-startMillis));
                  timeRemainingMinutes=timeRemaining/60000;
                  timeRemainingSeconds=(timeRemaining/1000)-(timeRemainingMinutes*60);
                  lcd.setCursor(12,3);
                  if (timeRemainingMinutes<10) lcd.print("0");
                  lcd.print(timeRemainingMinutes);
                  lcd.print(":");
                  if (timeRemainingSeconds<10) lcd.print("0");
                  lcd.print(timeRemainingSeconds);
                  lcd.setCursor (18,3);
                  lcd.write(5);                                   //raindrop icon
                  Serial.print("Time Remaining: ");
                  Serial.print(timeRemaining);
                  Serial.print("    Run Valve  ");
                  Serial.println(RunValve);
            }
          }
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



