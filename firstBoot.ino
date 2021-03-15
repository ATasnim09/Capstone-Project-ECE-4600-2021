/*
*
* Function Name:  firstBoot
* Input:    None
* Output:   None
* Logic:    This function is called only once. It takes the input from the user of the doze and alarm times according to the prescription
* Example Call:   void firstBoot()
*
*/
void firstBoot()
{
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Welcome New User");
  
  delay(6000);
  lcd.clear();
  delay(300);
  lcd.setCursor(0,0);
  lcd.print("Set time");
  lcd.setCursor(0,1);
  lcd.print("Doze 1");
  medTime();                    //function is called to set the time
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set time");
  lcd.setCursor(0,1);
  lcd.print("Doze 2");
  medTime();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set time");
  lcd.setCursor(0,1);
  lcd.print("Doze 3");
  medTime();
  lcd.clear();
  delay(300);

  lcd.setCursor(0,0);
  lcd.print("Set time for");
  lcd.setCursor(0,1);
  lcd.print("custom dozes of");
  lcd.setCursor(0,2);
  lcd.print("each day");
  
  delay(6000);
  for(cD = 0; cD < 7; cD++) customMedTime(); //function is called to set the time

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set time for");
  lcd.setCursor(0,1);
  lcd.print("alarms");
  delay(2000);
  for (rA = 0; rA < 3; rA++) regAlarm();   //function is called to set the time

  
  delay(3000); 
}
