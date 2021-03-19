#include <LiquidCrystal.h> 
#include <SoftwareSerial.h> 
#include <TinyGPS.h> 


float lat = 28.5458,lon = 77.1703; // create variable for latitude and longitude object  
SoftwareSerial gpsSerial(6,7);//rx,tx 


const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); 
TinyGPS gps; // create gps object 

void setup()
  { 
      Serial.begin(9600); // connect serial 
      //Serial.println("The GPS Received Signal:"); 
      gpsSerial.begin(9600); // connect gps sensor 
      lcd.begin(16,2);
      lcd.print("HELLO");
      delay(2000);
      lcd.clear();
       
  } 


void loop()
   { 
        while(gpsSerial.available())
          { // check for gps data 
              if(gps.encode(gpsSerial.read()))// encode gps data 
                {  
                    gps.f_get_position(&lat,&lon); // get latitude and longitude 
                    // display position 
                    lcd.clear(); 
                    lcd.setCursor(1,0); 
                    lcd.print("GPS Signal"); 
                    //Serial.print("Position: "); 
                    //Serial.print("Latitude:"); 
                    //Serial.print(lat,6); 
                    //Serial.print(";"); 
                    //Serial.print("Longitude:"); 
                    //Serial.println(lon,6);  
                    lcd.setCursor(1,0); 
                    lcd.print("LAT:"); 
                    lcd.setCursor(5,0); 
                    lcd.print(lat); 
                    //Serial.print(lat); 
                    //Serial.print(" "); 
                    lcd.setCursor(0,1); 
                    lcd.print(",LON:"); 
                    lcd.setCursor(5,1); 
                    lcd.print(lon); 
                 } 
          } 
              String latitude = String(lat,6); 
              String longitude = String(lon,6); 
              Serial.println(latitude+";"+longitude); 
              delay(1000); 
   } 
