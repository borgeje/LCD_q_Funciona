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

