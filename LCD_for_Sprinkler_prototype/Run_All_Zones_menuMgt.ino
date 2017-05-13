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

