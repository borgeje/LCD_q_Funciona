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

