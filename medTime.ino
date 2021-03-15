/*
*
* Function Name:  medTime
* Input:    None
* Output:   None
* Logic:    This function is to store the input given by user in memory of the microcontroller.
* Example Call:   void medTime()
*
*/
void medTime()
{
  int temp = 1;
  setHour = 0;
  setMin = 0;
  while (temp == 1)           //hour is set
  {
    readRotaryEncoder();
    encoderButton();
    if(EEPROM.read(1))
    { 
      EEPROM.write(1,0);
      middle = false;
    }
    if(up)                  //checks if the encoder is rotated in upwards direction
    {
      setHour++;
      up = false;
      if (setHour > 23) setHour = 0;
      if (setHour < 0) setHour = 23;
    }
    else if(down)           //checks if the encoder is rotated in downwards direction            
    {
      setHour--;
      down = false;
      if (setHour < 0) setHour = 23;
      if (setHour > 23) setHour = 0;
    }
    lcd.setCursor(0,2);
    lcd.print(setHour);
    lcd.print(":");
    lcd.print(setMin);
    if(middle == true)    //checks if button is pressed
    { 
      middle = false;
      EEPROM.write(hourAddr, setHour); //time is set for the doze
      hourAddr += 3;
      temp = 2;
    }
  }
  while (temp == 2)           //minutes are set
  {
    readRotaryEncoder();
    encoderButton();
    if(up)
    {
      setMin++;
      up = false;
      if (setMin > 59) setMin = 0;
      if (setMin < 0) setMin = 59;
    }
    else if(down)
    {
      setMin--;
      down = false;
      if (setMin < 0) setMin = 59;
      if (setMin > 59) setMin = 0;
    }
    lcd.setCursor(0,2);
    lcd.print(setHour);
    lcd.print(":");
    lcd.print(setMin);
    if(middle == true)
    {
      middle = false;
      EEPROM.write(minAddr, setMin);
      minAddr += 3;
      temp = 0;
    }
  }
}
