/*
*
* Function Name:  displayTime
* Input:    None
* Output:   None
* Logic:    This function is called to display the current time and upcoming doze on the LCD
* Example Call:   void displayTime()
*
*/
void displayTime()
{  
   DateTime now = rtc.now();
   lcd.clear();
   lcd.setCursor(4,0);
   lcd.print(now.hour());
   lcd.print('.');
   lcd.print(now.minute());
   lcd.setCursor(4,1);
   lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
   lcd.setCursor(4,2);
   lcd.print(now.day());
   lcd.print('/');
   lcd.print(now.month());
   lcd.print('/');
   lcd.print(now.year());
   lcd.setCursor(0,3);
   lcd.print("Upcoming:");
   lcd.print(EEPROM.read(hourAddr-3));
   lcd.print('.');
   lcd.print(EEPROM.read(minAddr-3));
   delay(300);
}
