#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <ErriezRotaryFullStep.h>
#include <TimerOne.h>

#define ChipSelect 53
#define ROTARY_PIN1        3
#define ROTARY_PIN2         2
#define sw A2

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);
RotaryFullStep rotary(ROTARY_PIN1, ROTARY_PIN2);

int count = 0;
int countLast = 0;

// Forward declaration
void rotaryInterrupt();

//variables for setting the doze times
int cD;             //custome doze
int setHour;
int setMin;
int setDay;
int rA;             //regular alarm

//variables used to hold EEPROM addresses
int hourAddr = 2;
int minAddr  = 3;
int ChourAddr = 11;
int CminAddr  = 12;
int dayAddr   = 13;
boolean firstTime = true;
//varibale to detect if the machine is booted for the first time

//variables to check the current time with time set by care taker
int checkHour;
int checkMin;
int checkHourTempVar;
int checkMinTempVar;
int CcheckHour;
int CcheckMin;
int CcheckHourTempVar;
int CcheckMinTempVar;
int checkDay;
int alarmHour;
int alarmMin;

//variables to store current time
int currHour = 0;
int currMin  = 0;
int currDay  = 0;

//strings for displaying dozes on LCD
String item1;
String item2;
String item3;
String item4;

//booleans for reading the rotary encoder
boolean up = false;
boolean down = false;
boolean middle = false;
boolean displaySwitch = false;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup()
{
  pinMode(ChipSelect, OUTPUT);
  digitalWrite(ChipSelect, HIGH);
  delay(100);
  rtc.begin();
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Welcome"); //print this messese when uploaded
  delay(2000); //wait 6 sec
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN1), rotaryInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN2), rotaryInterrupt, CHANGE);
  rotary.setSensitivity(125);
  Serial.begin(115200);
}

void loop()
{
  //  Serial.println(count);
  //  lcd.setCursor(0, 1);
  //  lcd.print(count);
  //  delay(20);
  //  if (digitalRead(sw) == LOW)
  //  {
  //    count =0;
  //    lcd.clear();
  //  }




  DateTime now = rtc.now();         //current time is read
  if (EEPROM.read(1))               //this condition checks if the machine is booted for the first time or not
  {
    firstBoot();                    //function to handle the first boot up is called
  }

  encoderButton();                  //rotary encoder is read
  if (middle)                       //system detects if encoder button is pressed
  {
    middle = false;
    displaySwitch = !displaySwitch;
  }

  if (displaySwitch)
  {
    displayTime();                  //if the system detects that the user has pressed the encoder button, time is displayed
  }
}

void rotaryInterrupt()
{
  int rotaryState;

  // Read rotary state (Counter clockwise) -2, -1, 0, 1, 2 (Clockwise)
  rotaryState = rotary.read();

  // Count up or down by using rotary speed
  if (rotaryState == 0) {
    // No change
    return;
  } else if (abs(rotaryState) >= 2) {
    count += rotaryState * 2;
  } else {
    count += rotaryState;
  }

  // Limit count to a minimum and maximum value
  if (count > 100) {
    count = 100;
  }
  if (count < 0) {
    count = 0;
  }

  // Print count value when count value changed
  if (countLast != count) {
    countLast = count;
    Serial.print(F("Count: "));
    Serial.println(count);
  }
}


/*

#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Arduino.h>
#include <RTClib.h>
#include <ClickEncoder.h>
#include <TimerOne.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>


#define ChipSelect 53
//#define clk A0
//#define dt A1
//#define sw A2

LiquidCrystal_I2C lcd(0x27, 16, 2);

ClickEncoder *encoder;    //for rotary encoder
int16_t last, value;

//variables for setting the doze times
int cD;             //custome doze
int setHour;
int setMin;
int setDay;
int rA;             //regular alarm

//variables used to hold EEPROM addresses
int hourAddr = 2;
int minAddr  = 3;
int ChourAddr = 11;
int CminAddr  = 12;
int dayAddr   = 13;
boolean firstTime = true;
//varibale to detect if the machine is booted for the first time

//variables to check the current time with time set by care taker
int checkHour;
int checkMin;
int checkHourTempVar;
int checkMinTempVar;
int CcheckHour;
int CcheckMin;
int CcheckHourTempVar;
int CcheckMinTempVar;
int checkDay;
int alarmHour;
int alarmMin;

//variables to store current time
int currHour = 0;
int currMin  = 0;
int currDay  = 0;

//strings for displaying dozes on LCD
String item1;
String item2;
String item3;
String item4;

//booleans for reading the rotary encoder
boolean up = false;
boolean down = false;
boolean middle = false;
boolean displaySwitch = false;

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


void timerIsr()
{
  encoder->service();
}

void setup()
{
  Serial.begin(115200);
  //all the objects are started and communication is established between the different modules interfaced
  pinMode(ChipSelect, OUTPUT);
  digitalWrite(ChipSelect, HIGH);
  delay(100);
  rtc.begin();
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Welcome"); //print this messese when uploaded
  delay(200); //wait 6 sec
  //lcd.clear(); //remove the msg

  Timer1.initialize(1000);

  EEPROM.write(1, 1);
  //this is used to check if the machine is booted for the first time or not

  //rotary encoder initializations
  encoder = new ClickEncoder(A1, A0, A2);
  encoder->setAccelerationEnabled(true);
  //last = encoder->getValue();
  last = -1;
}

void loop() {
  value += encoder->getValue();
  lcd.setCursor(0, 1);
  lcd.print(value);

  delay(10);

  if (value != last) 
  {
    last = value;
    Serial.print("Encoder Value: ");
    Serial.println(value);

  }
  if (digitalRead(A2) == LOW)
  {
    Serial.println(digitalRead(A2));
  }

  DateTime now = rtc.now();         //current time is read
  if (EEPROM.read(1))               //this condition checks if the machine is booted for the first time or not
  {
    firstBoot();                    //function to handle the first boot up is called
  }

  encoderButton();                  //rotary encoder is read
  if (middle)                       //system detects if encoder button is pressed
  {
    middle = false;
    displaySwitch = !displaySwitch;
  }

  if (displaySwitch)
  {
    displayTime();                  //if the system detects that the user has pressed the encoder button, time is displayed
  }
}*/
