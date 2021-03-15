/*
*
* Function Name:  customMedTime
* Input:    None
* Output:   None
* Logic:    This function is called only once. It takes the input from the user of the custom doze times of each day
* Example Call:   void customMedTime()
*
*/
void customMedTime()
{   
    lcd.clear();
    delay(300);
    setHour = 0;
    setMin = 0;
    lcd.setCursor(0,0);
    lcd.print("Set time");
    lcd.setCursor(0,1);
    lcd.print(daysOfTheWeek[cD]);
    lcd.setCursor(0,2);
    lcd.print(setHour);
    lcd.print(":");
    lcd.print(setMin);
    medTime();
    EEPROM.write(dayAddr,cD);
    dayAddr  += 3;
}
