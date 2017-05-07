void updateDisplay()
{
/*  static unsigned long lastUpdateTime;
  static bool displayToggle = false;
  static SprinklerStates lastDisplayState;
  if (state != lastDisplayState || millis() - lastUpdateTime >= 3000UL)
  {
    displayToggle = !displayToggle; 
    switch (state) {
      case STAND_BY_ALL_OFF:
        //
        fastClear();
        lcd.setCursor(0, 0);
        break;
      case RUN_SINGLE_ZONE:
        //
        fastClear();
        lcd.setCursor(0, 0);
        break;
      case RUN_ALL_ZONES:
        //
        fastClear();
        lcd.setCursor(0, 0);
        break;
      case CYCLE_COMPLETE:
        break;
    }                         // BREAK FINISHES HERE

    
    lastUpdateTime = millis();
  }
  lastDisplayState = state;
*/
/*

    lcd.setCursor(0,0);
  lcd.print("     MAIN MENU    ");
  lcd.setCursor(0,1);
  lcd.print(" 09:00PM  22/05/16");
  lcd.setCursor(0,2);
  lcd.print("   Default          ");
  lcd.setCursor(0,3);
  lcd.print("                   ");
  lcd.setCursor(0,3);
  lcd.print("Z1 _ Z2 _ Z3 _ more_");
 */ 
}

void fastClear()
{
  lcd.setCursor(0, 0);
  lcd.print("                   ");
  lcd.setCursor(0, 1);
  lcd.print("                   ");
  lcd.setCursor(0, 2);
  lcd.print("                   ");
  lcd.setCursor(0, 3);
  lcd.print("                   ");
}


