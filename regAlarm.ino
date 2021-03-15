/*
*
* Function Name:  regAlarm
* Input:    None
* Output:   None
* Logic:    This function is called only once. It takes the input from the user of the alarm times
* Example Call:   void regAlarm()
*
*/
void regAlarm()
{
    lcd.clear();
    delay(300);
    setHour = 0;
    setMin = 0;
    lcd.setCursor(0,0);
    lcd.print("Set time");
    lcd.setCursor(0,2);
    lcd.print(setHour);
    lcd.print(":");
    lcd.print(setMin);
    medTime(); 
}
