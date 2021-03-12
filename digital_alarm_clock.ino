#include <DS1307.h>
#include <LiquidCrystal_I2C.h>
#include<RTClib.h>

#include  <Wire.h>

#include <LiquidCrystal_I2C.h>

//************************************//
LiquidCrystal_I2C lcd(0x27,16,2); // Display  I2C 16 x 2

RTC_DS1307 RTC;
//************Button*****************//
int P1=6; // Button SET MENU'
int P2=7; // Button +
int P3=8; // Button -
int P4=9; // SWITCH Alarm
//**************Alarm***************//
#define LED 13
#define buzzer 10
//************Variables**************//
int hourupg, yearupg, minupg, monthupg, dayupg;
int setAll =0;
uint8_t  alarmHours = 0, alarmMinutes = 0;      // Holds the current alarm time

void setup()
{
  
  lcd.backlight();
  lcd.clear();

  pinMode(P1,INPUT_PULLUP); 
  pinMode(P2,INPUT_PULLUP);
  pinMode(P3,INPUT_PULLUP);
  pinMode(P4,INPUT_PULLUP);
  pinMode(LED,OUTPUT);
  pinMode(buzzer, OUTPUT); // Set buzzer as an output
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // Set the date and time at compile time
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }}
 
void loop()
{ 
// check if you press the SET button and increase the menu index
  
  if((digitalRead(P2)== LOW)&&(digitalRead(P3)== LOW))                                                                                                                                                                     
  {
    
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("ALARM");
    lcd.setCursor(5,1);
    lcd.print(alarmHours, DEC);
    lcd.print(":");
    lcd.print(alarmMinutes, DEC);
    delay(1000);
    lcd.clear();
  }
int DisplaySetHourAll();

  while(digitalRead(P1)==HIGH)
{
  lcd.clear();
   if(digitalRead(P2)==LOW)
  {
    if(alarmHours==23)
    {
      alarmHours=0;
    }
    else
    {
      alarmHours=alarmHours+1;
    }
  }
   if(digitalRead(P3)==LOW)
  {
    if(alarmHours==0)
    {
      alarmHours=23;
    }
    else
    {
      alarmHours=alarmHours-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set HOUR Alarm:");
  lcd.setCursor(0,1);
  lcd.print(alarmHours,DEC);
  delay(200);
 }
 delay(200);

}
int DisplaySetMinuteAll()                                     // Setting the alarm minutes
 {
  while(digitalRead(P1)==HIGH)
{ 
  lcd.clear();
  if(digitalRead(P2)==LOW)
  {
    if (alarmMinutes==59)
    {
      alarmMinutes=0;
    }
    else
    {
      alarmMinutes=alarmMinutes+1;
    }
  }
   if(digitalRead(P3)==LOW)
  {
    if (alarmMinutes==0)
    {
      alarmMinutes=59;
    }
    else
    {
      alarmMinutes=alarmMinutes-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set MIN. Alarm:");
  lcd.setCursor(0,1);
  lcd.print(alarmMinutes,DEC);
  delay(200);
 }
 delay(200);
}
int printAllOn()
{
   lcd.setCursor(0,3);
  lcd.print("Alarm: ");
  if (alarmHours <= 9)
  {
    lcd.print("0");
  }
  lcd.print(alarmHours, DEC);
  lcd.print(":");
  if (alarmMinutes <= 9)
  {
    lcd.print("0");
  }
  lcd.print(alarmMinutes, DEC); 
}
int printAllOff() {
  lcd.setCursor(0, 3);
  lcd.print("Alarm: Off  ");  
}
int Alarm(){
   if(digitalRead(P4)== LOW){
   setAll=setAll+1;
  }
  if (setAll==0)  {
     printAllOff();
     noTone (buzzer);
     digitalWrite(LED,LOW);
     }
  if (setAll==1)
    {
     printAllOn();    
       DateTime now = RTC.now();
     if ( now.hour() == alarmHours && now.minute() == alarmMinutes )
        {
         lcd.noBacklight();
         DateTime now = RTC.now();
         digitalWrite(LED,HIGH);
         tone(buzzer,880); //play the note "A5" (LA5)
         delay (300);
         tone(buzzer,698); //play the note "F6" (FA5)
         lcd.backlight();
        }
    else{
         noTone (buzzer);
         digitalWrite(LED,LOW);
        }
       } 
  if (setAll==2)
    {
     setAll=0;
    }
    delay(200);
}
