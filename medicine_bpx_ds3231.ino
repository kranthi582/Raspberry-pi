#include <RTClib.h>

//#include <RTCDS1307.h>


/*  PulseSensor Starter Project and Signal Tester
 *  The Best Way to Get Started  With, or See the Raw Signal of, your PulseSensor.com™ & Arduino.
 *
 *  Here is a link to the tutorial
 *  https://pulsesensor.com/pages/code-and-guide
 *
 *  WATCH ME (Tutorial Video):
 *  https://www.youtube.com/watch?v=RbB8NSRa5X4
 *
 *
-------------------------------------------------------------
1) This shows a live human Heartbeat Pulse.
2) Live visualization in Arduino's Cool "Serial Plotter".
3) Blink an LED on each Heartbeat.
4) This is the direct Pulse Sensor's Signal.
5) A great first-step in troubleshooting your circuit and connections.
6) "Human-readable" code that is newbie friendly."

*/
//#include "RTCDS1307.h"
#include <OneWire.h>
//#include <DallasTemperature.h>
#include <SoftwareSerial.h>
#include <Wire.h>
//#include "RTClib.h"
#include <LiquidCrystal.h>            // Header inclusion
#include <EEPROM.h>


/*
  DS1307 RTC (Real-Time-Clock) Example

  Uno       A4 (SDA), A5 (SCL)
  Mega      20 (SDA), 21 (SCL)
  Leonardo   2 (SDA),  3 (SCL)
 */
 unsigned int hr_count=0;
unsigned int min_count=0,day_count=0,month_count=0;
unsigned char addr=0;
unsigned char sec, min_, hour_, day_, month_;
  unsigned int year_;
bool set_date=0,set_time=0,set_hour=0,set_min=0,set_day=0,set_month=0,medicine_flag=0;
unsigned char medicine_hour[10]={"00"};
unsigned char medicine_minute[10]={"00"};
unsigned long int med_period=0;
unsigned long int med_period_1=0;
unsigned long int med_period_2=0;
unsigned long int med_period_3=0;
 unsigned char med_period_hr[2]={"0"};
 unsigned char med_period_min[2]={"0"} ;

bool med_flag=0;
RTC_DS1307 rtc;
//RTC_DS1307 rtc;
//RTCDS1307 rtc;
//RTCDS1307 rtc(0x68);
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2, inc_sw=10,dec_sw=9,enter_sw=8,buzzer=A5;
const int M0 = A1, M1 = A3,M2 = A4;

const int L1 = 13, L2 = 12,L3 = 11;    /////ledddd

int med1_voice=A0;
int med2_voice=A1;
int med3_voice=A2;

// Data wire is plugged into port 2 on the Arduino, while external pullup P-MOSFET gate into port 3
//#define ONE_WIRE_BUS    2
unsigned char eeprom_data=0;

//  Variables
//int PulseSensorPurplePin = A0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
//int LED13 = 13;   //  The on-board Arduion LED
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
//OneWire oneWire(ONE_WIRE_BUS);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//DallasTemperature sensors(&oneWire);
SoftwareSerial mySerial(A5, A4);

// The SetUp Function:
void setup() {
 // pinMode(LED13,OUTPUT);         // pin that will blink to your heartbeat!

  pinMode(enter_sw,INPUT_PULLUP); 
  pinMode(inc_sw,INPUT_PULLUP); 
pinMode(dec_sw,INPUT_PULLUP); 
//pinMode(M0, OUTPUT);
//pinMode(M1, OUTPUT);
//pinMode(M2, OUTPUT);

pinMode(buzzer, OUTPUT);
pinMode(med1_voice, OUTPUT);
pinMode(med2_voice, OUTPUT);
pinMode(med3_voice, OUTPUT);

pinMode(L1, OUTPUT);
pinMode(L2, OUTPUT);
pinMode(L3, OUTPUT);

digitalWrite(buzzer, LOW);
digitalWrite(L1, LOW);
digitalWrite(L2, LOW);
digitalWrite(L3, LOW);

//digitalWrite(M0, HIGH);
//digitalWrite(M1, HIGH);
//digitalWrite(M2, HIGH);
 rtc.begin();
  mySerial.begin(9600);
  Serial.begin(9600);
  while(!Serial); /*wait for serial port to connect - needed for Leonardo only*/

  /*init RTC*/
  Serial.println("Init RTC...");

  /*only set the date+time one time*/
 // rtc.set(0, 0, 8, 24, 12, 2020); /*08:00:00 24.12.2014 //sec, min, hour, day, month, year*/

  /*stop/pause RTC*/
  // rtc.stop();

  /*start RTC*/
//  if (! rtc.begin()) 
//  {
//    Serial.println("Couldn't find RTC");
//    Serial.flush();
//    abort();
//  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    //RTC.adjust(DateTime(F(__DATE__), F( __TIME__)));

  }
//if (rtc.lostPower()) 
//{
//    Serial.println("RTC lost power, let's set the time!");
//    // When time needs to be set on a new device, or after a power loss, the
//    // following line sets the RTC to the date & time this sketch was compiled
//   // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//    // This line sets the RTC with an explicit date & time, for example to set
//    // January 21, 2014 at 3am you would call:
//    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
//  }
   // Start up the library
lcd. cursor();
lcd.begin(16, 2);                // Set up the LCD's number of columns and rows:
lcd.clear();              // Position the LCD cursor
lcd.print("MEDICINE BOX");   // Print a message to the LCD.
lcd.setCursor(0,1);              // Position the LCD cursor
lcd.print(" REMINDER"); 
delay(2000);
set_time_and_date();
digitalWrite(med1_voice,HIGH);
digitalWrite(med2_voice,HIGH);
digitalWrite(med3_voice,HIGH);
  lcd.clear();

}

// The Main Loop Function
void loop() 
{

  lcd.clear();
delay(10);
lcd.print("STATUS:"); 
                                 
if( EEPROM.read(6)=='f')
{
  lcd.print(" ACTIVE");
 
delay(200);
  if(medicine_flag==0)
{
   medicine_flag=1;
 
 

 med_period_hr[0]=EEPROM.read(0);
 med_period_hr[1]=EEPROM.read(2);
 med_period_hr[2]=EEPROM.read(4);
 
  med_period_min[0]=EEPROM.read(1);
 med_period_min[1]=EEPROM.read(3);
 med_period_min[2]=EEPROM.read(5);
 
 med_period_1= (med_period_hr[0]*100)+ med_period_min[0];
 Serial.println("medicine period__2:"+String(med_period_1));

med_period_2= (med_period_hr[1]*100)+ med_period_min[1];
Serial.println("medicine period__3:"+String(med_period_2));

med_period_3= (med_period_hr[2]*100)+ med_period_min[2];
Serial.println("medicine period__3:"+String(med_period_3));

}
       
}
else
{
  lcd.print(" ____  "); 
  lcd.setCursor(0,1);
lcd.print("TIME NOT ADDED    "); 
delay(500);      
}

if(digitalRead(enter_sw)==0)
 {
  lcd.setCursor(0,1);
lcd.print("READY TO ADD    "); 
delay(1500);      
lcd.setCursor(0,1);
lcd.print("               "); 
 add_medicine_time(3);
 }
 lcd.setCursor(0,1);              // Position the LCD cursor
lcd.print("                ");


  /*get time from RTC*/
 /*get time from RTC*/
DateTime now = rtc.now();
 year_=now.year(); 
 month_=now.month();
 day_=now.day();
 int w=now.dayOfTheWeek();
 hour_=now.hour();
 min_=now.minute();
 sec=now.second();
if(hour_<10)
{
lcd.setCursor(0,1);              // Position the LCD cursor
lcd.print("0");
lcd.print(hour_, DEC);
}
else
{
lcd.setCursor(0,1);              // Position the LCD cursor
lcd.print(hour_, DEC);
  
}


 lcd.setCursor(2,1);
  lcd.print(":");
  if(min_<10)
  {
    lcd.setCursor(3,1);
    lcd.print("0");
  lcd.print(min_, DEC);
  }else
  {
    lcd.setCursor(3,1);
  lcd.print(min_, DEC);
  }

  
  lcd.setCursor(5,1);
  lcd.print(":");
  if(sec<10)
  {
    lcd.setCursor(6,1);
    lcd.print("0");
  lcd.print(sec, DEC);
  }else
  {
    lcd.setCursor(6,1);
  lcd.print(sec, DEC);
  }



  lcd.print(" ");
  if(day_<10)
  {
    lcd.setCursor(9,1);
    lcd.print("0");
  lcd.print(day_, DEC);
  }
  else
   {
    lcd.setCursor(9,1);
  lcd.print(day_, DEC);
  }

  
  lcd.setCursor(11,1);
  lcd.print(".");
  if(month_<10)
  {
    lcd.setCursor(12,1);
    lcd.print("0");
  lcd.print(month_, DEC);
  }
  else
  {
    lcd.setCursor(12,1);
  lcd.print(month_, DEC);
  }

  
  lcd.setCursor(14,1);
  lcd.print(".");
  lcd.print("20");
  //lcd.print(year, DEC);
  /*serial output*/
  Serial.print("\nTime: ");
  Serial.print(hour_, DEC);
  Serial.print(":");
  Serial.print(min_, DEC);
  Serial.print(":");
  Serial.print(sec, DEC);

  Serial.print("\nDate: ");
  Serial.print(day_, DEC);
  Serial.print(".");
  Serial.print(month_, DEC);
  Serial.print(".");
  Serial.print(year_, DEC);

med_period=((hour_*100)+min_);
Serial.println("medicine period:"+String(med_period));

if(med_period_1==med_period)
{
  
  lcd.setCursor(0,1);
    lcd.print("TAKE MEDICINE   ");
    //sound_strobe(M2,3000);
    digitalWrite(L1, HIGH);
digitalWrite(L2, LOW);
digitalWrite(L3, LOW);
digitalWrite(buzzer, HIGH);
delay(1000);
  digitalWrite(buzzer, LOW);
     delay(200);
     digitalWrite(med1_voice,LOW);
     lcd.setCursor(0, 1);
  delay(10);

  delay(100);
 lcd.setCursor(0, 1);
  delay(10);
  lcd.print("                ");
  delay(1000);
  digitalWrite(med1_voice,HIGH);
 if(med_flag==0)
{
med_flag=1;

//sendsms();//+String(hour)+":"+String(min));

}
}
else if(med_period_2==med_period)
{
  digitalWrite(L1, LOW);
digitalWrite(L2, HIGH);
digitalWrite(L3, LOW);


  lcd.setCursor(0,1);
    lcd.print("TAKE MEDICINE   ");
     delay(200);

 //sound_strobe(M2,3000);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(med2_voice,LOW);
 lcd.setCursor(0, 1);
  delay(10);
  lcd.print("                ");
  delay(1000);
  digitalWrite(med2_voice,HIGH);
  if(med_flag==0)
{
med_flag=1;

//sendsms();//+String(hour)+":"+String(min));

}

}else if(med_period_3==med_period) 
{
  digitalWrite(L1, LOW);
digitalWrite(L2, LOW);
digitalWrite(L3, HIGH);


  lcd.setCursor(0,1);
    lcd.print("TAKE MEDICINE   ");
     delay(200);
//
//  delay(100);
// sound_strobe(M2,3000);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(med3_voice,LOW);
 lcd.setCursor(0, 1);
  delay(10);
  lcd.print("                ");
  delay(1000);
  digitalWrite(med1_voice,HIGH);
  if(med_flag==0)
{
med_flag=1;
//sendsms();//+String(hour)+":"+String(min));
}

}
else
{
  medicine_flag=0;
  med_flag=0;
  digitalWrite(buzzer, LOW);
 digitalWrite(L1, LOW);
digitalWrite(L2, LOW);
digitalWrite(L3, LOW); 
}
  /*wait a second*/
  delay(500);





}

/*
void sound_strobe(const int a,unsigned int count)
{
  digitalWrite(a,HIGH);
delay(100);
digitalWrite(a,LOW );
delay(count+100);
digitalWrite(a,HIGH);

}

void sendsms()
{
    lcd.setCursor(0, 2);
  delay(10);
  lcd.print("SENDING SMS      ");
  delay(500);
  
  Serial.println("AT");
  delay(2000);
  Serial.println("ATE0");
  delay(2000);
 Serial.println("AT+CMGF=1");
 delay(2000);
  Serial.println("AT+CMGS=\"+919100634131\"");
  delay(1000);
   //Serial.print(message);
   Serial.print("Time to take medicine.Please check your medicine box");
   
  delay(1000);
  Serial.println((char)26);

  delay(1000);
}*/

void set_time_and_date()
{
  while(set_time==0)
{
lcd.clear();
lcd.setCursor(0,0); 
lcd.print("ENTER TO CHANGE  ");
lcd.setCursor(0,1);
lcd.print("TIME:"); 
/*get time from RTC*/
DateTime now = rtc.now();
 year_=now.year(); 
 month_=now.month();
 day_=now.day();
 int w=now.dayOfTheWeek();
 hour_=now.hour();
 min_=now.minute();
 sec=now.second();
//lcd.setCursor(0,1);              // Position the LCD cursor

 lcd.print(hour_, DEC); ///// DEC-Decimal
 lcd.setCursor(7,1); 
  lcd.print(":");
  lcd.print(min_, DEC);
  lcd.setCursor(10,1); 
  lcd.print(":");
 lcd.print(sec, DEC);
 if(digitalRead(enter_sw)==0)
 {
  ////////////////////////////////////////////// hour ///////////////////////
  lcd.setCursor(6,1);
      lcd. blink();
  delay(1000);
  while(set_hour==0)
  {
    if(digitalRead(inc_sw)==0)
    {
      hr_count++;
      if(hr_count>=24)
      {
        hr_count=24;
      }
     if(hr_count<10)
     {
    lcd.setCursor(5,1);
     lcd.print( "0"+String(hr_count));
     lcd.setCursor(6,1);
      lcd. blink();
     }
     else
     {
       lcd.setCursor(5,1);
     lcd.print( hr_count);
      lcd.setCursor(6,1);
      lcd. blink();
     }
      
      
    }
    if(digitalRead(dec_sw)==0)
    {
      hr_count--;
      if(hr_count>=24)
      {
        hr_count=24;
      }
      
       if(hr_count<10)
     {
      lcd.setCursor(5,1);
    lcd.print("0"+ String(hr_count));
     lcd.setCursor(6,1);
      lcd. blink();
     }
     else
     {
      lcd.setCursor(5,1);
     lcd.print(hr_count);
      lcd.setCursor(6,1);
      lcd. blink();
     }
      if(hr_count<0)
      {
        hr_count=0;
      }
     
      
    }
     if(digitalRead(enter_sw)==0)
     {
      set_hour=1;
      break;
     }
     delay(200);
  }
  ///////////////////////////////////////////// minute ////////////////////////
lcd.setCursor(9,1);
      lcd. blink();
  delay(1000);
   while(set_min==0)
  {
    
    if(digitalRead(inc_sw)==0)
    {
      min_count++;
     if(min_count>=60)
      {
        min_count=0;
      }
      if(min_count<10)
     {
       lcd.setCursor(8,1);
     lcd.print( "0"+String(min_count));
     lcd.setCursor(9,1);
      lcd. blink();
     }
     else
     {
       lcd.setCursor(8,1);
     lcd.print( min_count);
      lcd.setCursor(9,1);
      lcd. blink();
     }
      
      
    }
    if(digitalRead(dec_sw)==0)
    {
      min_count--;
       if(min_count>=60)
      {
        min_count=0;
      }
      
      if(min_count<10)
     {
      lcd.setCursor(8,1);
     lcd.print( "0"+String(min_count));
     lcd.setCursor(9,1);
      lcd. blink();
     }
     else
     {
      lcd.setCursor(8,1);
     lcd.print( min_count);
      lcd.setCursor(9,1);
      lcd. blink();
     }
      
    }
     if(digitalRead(enter_sw)==0)
     {
      set_min=1;
      break;
     }
      delay(200);
  }
 
  lcd.clear();
lcd.print("TIME:CHANGED    "); 
 delay(1000);
lcd.setCursor(0,1);
lcd.print("DATE:");
// delay(1000);
lcd.print(day_, DEC);
 lcd.setCursor(7,1);
  lcd.print(".");
  lcd.print(month_, DEC);
   lcd.setCursor(10,1);
  lcd.print(".");
  lcd.print(year_, DEC);
  //delay(1000);
   ////////////////////////////////////////////////////////// day ///////////////////////    
 lcd.setCursor(6,1);
      lcd. blink();
delay(1000);
   while(set_day==0)
  {
    if(digitalRead(inc_sw)==0)
    {
      
     day_count++;
       if(day_count>=31)
      {
        day_count=31;
      }

       if(day_count<10)
     {
       lcd.setCursor(5,1);
     lcd.print( "0"+String(day_count));
     lcd.setCursor(6,1);
      lcd. blink();
     }
     else
     {
       lcd.setCursor(5,1);
     lcd.print( day_count);
      lcd.setCursor(6,1);
      lcd. blink();
     }
    }
    if(digitalRead(dec_sw)==0)
    {
     day_count--;
     if(day_count>=31)
      {
        day_count=31;
      }
        if(day_count<10)
     {
       lcd.setCursor(5,1);
     lcd.print( "0"+String(day_count));
     lcd.setCursor(6,1);
      lcd. blink();
     }
     else
     {
       lcd.setCursor(5,1);
     lcd.print( day_count);
      lcd.setCursor(6,1);
      lcd. blink();
     }
      
    }
     if(digitalRead(enter_sw)==0)
     {
      set_day=1;
      break;
     }
      delay(200);
  }
///////////////////////////////////////////////// month /////////////////////////////
lcd.setCursor(9,1);
      lcd. blink();
  delay(1000);
   while(set_month==0)
  {
    if(digitalRead(inc_sw)==0)
    {
      month_count++;
      
      
      if(month_count>=12)
      {
        month_count=12;
      }
          if(month_count<10)
     {
       lcd.setCursor(8,1);
     lcd.print( "0"+String(month_count));
     lcd.setCursor(9,1);
      lcd. blink();
     }
     else
     {
       lcd.setCursor(8,1);
     lcd.print( month_count);
      lcd.setCursor(9,1);
      lcd. blink();
     }
    }
    if(digitalRead(dec_sw)==0)
    {
     
   month_count--;
      if(month_count>=12)
      {
        month_count=12;
      }
          if(month_count<10)
     {
       lcd.setCursor(8,1);
     lcd.print( "0"+String(month_count));
     lcd.setCursor(9,1);
      lcd. blink();
     }
     else
     {
       lcd.setCursor(8,1);
     lcd.print( month_count);
      lcd.setCursor(9,1);
      lcd. blink();
     }
      
    }
     if(digitalRead(enter_sw)==0)
     {
      set_month=1;
      break;
     }
      delay(200);
  } 
  lcd.setCursor(0,1);
lcd.print("DATE:CHANGED    "); 
/*only set the date+time one time*/
rtc.adjust(DateTime(2021,  month_count,day_count, hr_count, min_count, 0));
set_time=1;
 delay(2000);
 }
 else if(digitalRead(inc_sw)==0)
 {
  set_time=1;
  break;
 }
 delay(100);
}
}

void add_medicine_time(int p)
{
   medicine_flag=0;
   addr=0;
   unsigned int i=0;
  while(i<p)
  {
  ////////////////////////////////////////////// hour ///////////////////////
  if(set_hour==0)
  {
  lcd.setCursor(6,1);
      lcd. blink();
  delay(1000);
  }
  while(set_hour==0)
  {
    if(digitalRead(inc_sw)==0)
    {
      hr_count++;
      if(hr_count>=24)
      {
        hr_count=24;
      }
     if(hr_count<10)
     {
      lcd.setCursor(5,1);
      lcd.print("0");
    lcd.setCursor(6,1);
    lcd.print( hr_count);
     //lcd.print( "0"+String(hr_count));
     lcd.setCursor(6,1);
      lcd. blink();
     }
     else
     {
       lcd.setCursor(5,1);
     lcd.print( hr_count);
      lcd.setCursor(6,1);
      lcd. blink();
     }
      
      
    }
    else if(digitalRead(dec_sw)==0)
    {
      hr_count--;
      if(hr_count>=24)
      {
        hr_count=24;
      }
      
       if(hr_count<10)
     {
      lcd.setCursor(5,1);
      lcd.print("0");
      lcd.setCursor(6,1);
      lcd.print(hr_count);
    //lcd.print("0"+ String(hr_count));
     lcd.setCursor(6,1);
      lcd. blink();
     }
     else
     {
      lcd.setCursor(5,1);
     lcd.print(hr_count);
      lcd.setCursor(6,1);
      lcd. blink();
     }
      if(hr_count<0)
      {
        hr_count=0;
      }
     
      
    }
     if(digitalRead(enter_sw)==0)
     {
      set_hour=1;
      break;
     }
     delay(200);
  }
  ///////////////////////////////////////////// minute ////////////////////////
  if(set_min==0)
  {
lcd.setCursor(9,1);
      lcd. blink();
  delay(1000);
  }
   while(set_min==0)
  {
    
    if(digitalRead(inc_sw)==0)
    {
      min_count++;
     if(min_count>=60)
      {
        min_count=0;
      }
      if(min_count<10)
     {
       lcd.setCursor(8,1);
     lcd.print( "0");
     lcd.setCursor(9,1);
     lcd.print(min_count);
     lcd.setCursor(9,1);
      lcd. blink();
     }
     else
     {
       lcd.setCursor(8,1);
     lcd.print( min_count);
      lcd.setCursor(9,1);
      lcd. blink();
     }
      
      
    }
    else if(digitalRead(dec_sw)==0)
    {
      min_count--;
       if(min_count>=60)
      {
        min_count=0;
      }
      
      if(min_count<10)
     {
      lcd.setCursor(8,1);
     lcd.print( "0");
     lcd.setCursor(9,1);
     lcd.print(min_count);
     lcd.setCursor(9,1);
      lcd. blink();
     }
     else
     {
      lcd.setCursor(8,1);
     lcd.print( min_count);
      lcd.setCursor(9,1);
      lcd. blink();
     }
      
    }
     if(digitalRead(enter_sw)==0)
     {
      
      medicine_hour[i]=hr_count;
  medicine_minute[i]=min_count;
      set_min=1;
      i++;
      break;
     }
      delay(200);
  }
 lcd.clear();
 delay(20);
lcd.print("TIME PERIOD:");
 lcd.print(i);
delay(20);
  if(digitalRead(inc_sw)==0)
  {
    //i++;
    set_min=0;
    set_hour=0;
  }
  delay(100);
 }
 delay(1000);
 for(int j=0;j<3;j++)
{
 EEPROM.write(addr,medicine_hour[j]);
  addr=addr+1;
 EEPROM.write(addr,medicine_minute[j]);
 addr=addr+1;
}
delay(10);
EEPROM.write(6,'f');
delay(10);
  lcd.clear();
lcd.print("TIME:ADDED       "); 
 delay(1000);
}
