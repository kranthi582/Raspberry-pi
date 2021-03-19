#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <TinyGPS++.h>
LiquidCrystal lcd(2,3,4,5,6,7);

int RS=2;
int EN=3;
int D4=4;
int D5=5;
int D6=6;
int D7=7;
const int sw=8;
int sw1;
TinyGPSPlus gps;
String  link = {};
String L2 = {};
float latitude = 0;
float longitude = 0;

unsigned int tempe;
SoftwareSerial MY_SERIAL(10,11);

void setup()
{
  
  Serial.begin(9600);
  MY_SERIAL.begin(9600);
  lcd.begin(16,2);
  Serial.println("womem is in danger");
  pinMode(sw,INPUT_PULLUP);
  lcd.print("Hello...");
  delay(2000);
//  trackgps();
//  delay(2000);
}

void loop()
{
  sw1=digitalRead(sw);
  if(sw1==LOW)
  {
    trackgps();
    delay(1000);
   // MY_SERIAL.println("ATD09121991303;");
    delay(20000);
    lcd.setCursor(0,0);
    lcd.print("womem in danger");
    lcd.setCursor(0,1);
    lcd.print("Need Help..");
    sendsms();
  }
}

void trackgps()
  {
     tempe= 0;
     while(tempe==0)
     {
      while (Serial.available() > 0)
      {
        gps.encode(Serial.read());
        if (gps.location.isUpdated())
        {
          latitude = (gps.location.lat());
          longitude = (gps.location.lng());
          link="http:\\www.google.com/maps/place/" + String(latitude) + ',' + String(longitude);
//          Serial.print("Latitude= ");
//          Serial.print(gps.location.lat(), 6);
//
//          Serial.print("Longitude= ");
//          Serial.print(gps.location.lng(), 6);
         // L1 = String(latitude, 6);
         //L2 = String(longitude, 6);           
//         Serial.println("updated");
//         Serial.println("LAT:  ");
//         Serial.print(L1);
//         Serial.println("LONG:  ");
//         Serial.print(L2);
         tempe= 1;
       }
    }
    if(tempe==1)
    {
       break;
      }
  }
  }

  
void sendsms()
  {
//    Serial.println("AT");
//    delay(1000);
    //Serial.println("ATD+919121991303;");
    //Serial.println("ATEO");
    //delay(1000);
    MY_SERIAL.println("AT+CMGF=1");
    delay(1000);
    MY_SERIAL.println("AT+CMGS=\"+919526234625\"\r");
     //Serial.println("AT+CMGS=\"+919074598671\"\r");
    delay(1000);
   MY_SERIAL.print("women in danger:");
//    delay(10);
   MY_SERIAL.println( link);
    delay(100);
    //Serial.write(26);
    MY_SERIAL.println((char)26); // ASCII code of CTRL+Z
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("msg send");
  }

