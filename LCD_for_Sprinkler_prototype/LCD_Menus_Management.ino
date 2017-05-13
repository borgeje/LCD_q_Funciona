void MainMenu(byte Menu)
{

  lcd.setCursor(0,0);
  lcd.print(" *** Main Menu ***");
  lcd.setCursor(0,1);
  lcd.print(" 09:00PM  22/05/16");
  lcd.setCursor(0,2);
  lcd.print("Auto Cycle          ");
  lcd.setCursor(0,3);
  lcd.print("                   ");
  lcd.setCursor(0,3);
  lcd.print("Z1 _ Z2 _ Z3 _ more_");
  if (Menu == 0)                lcd.setCursor(12,2);
  else if (Menu == 1)        lcd.setCursor(3,3);
    else if (Menu == 2)      lcd.setCursor(8,3);
       else if(Menu == 3)    lcd.setCursor(13,3);
          else if (Menu == 4)    lcd.setCursor(19,3);
  lcd.write(6);
}

void Run_All_Zones_Menu()
{
        lcd.setCursor(0,0);
        lcd.print(" >>> AUTO CYCLE <<<");
        lcd.setCursor(0,1);
        lcd.print("    Zone 1: ");
        unsigned long a=Zone1TimeAuto/60000;
        if (Zone1TimeAuto<60000) lcd.print("0");
        lcd.print(a);
        lcd.print(":");
        if (Zone1TimeAuto<10000) lcd.print("0");
        lcd.print(Zone1TimeAuto/1000-a);
        
        lcd.setCursor(0,2);
        lcd.print("    Zone 2: ");
        a=Zone2TimeAuto/60000;
        if (Zone2TimeAuto<60000) lcd.print("0");
        lcd.print(a);
        lcd.print(":");
        if (Zone2TimeAuto<10000) lcd.print("0");
        lcd.print(Zone2TimeAuto/1000-a);
        
        lcd.setCursor(0,3);
        lcd.print("    Zone 3: ");
        a=Zone3TimeAuto/60000;
        if (Zone3TimeAuto<60000) lcd.print("0");
        lcd.print(a);
        lcd.print(":");
        if (Zone3TimeAuto<10000) lcd.print("0");
        lcd.print(Zone3TimeAuto/1000-a);
}


void SingleZoneScreenManagement(int RunValve)
{
        lcd.setCursor(0,0);
        lcd.print(" >>> Single Zone <<<");
        lcd.setCursor(0,1);
        lcd.print("               ");
        lcd.setCursor(0,2);
        lcd.print("Current Zone: ");
        lcd.print(RunValve);
        lcd.setCursor(0,3);
        lcd.print("Time Remain.:  ");
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
