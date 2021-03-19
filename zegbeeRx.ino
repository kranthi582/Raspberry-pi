#include <SoftwareSerial.h>
#include<LiquidCrystal.h>
#include <TinyGPS.h> 
LiquidCrystal lcd(2,3, 4, 5, 6, 7); 
TinyGPS gps; // create gps object 

static const int RXPin = 11, TXPin = 12;
SoftwareSerial zigbee(RXPin, TXPin);



int motor=8;
int buz=10;
float lati = 28.5458, longi = 77.1703;

void setup() 
  {
    Serial.begin(9600);
    zigbee.begin(9600);
  
    
    pinMode(motor,OUTPUT);
    pinMode(buz,OUTPUT);
    //Serial.println("Hello");
    
    lcd.begin(16,2);
    lcd.clear();
    lcd.setCursor(0,0);
    
    lcd.print("SMART HELMET RX");
    delay(3000);
    digitalWrite(motor,LOW);
    digitalWrite(buz,LOW);
  
  }



void loop() 
  {
    char c;
    int x, y;
      while(zigbee.available()>0)
      c = zigbee.read();
      x = analogRead(A0);
      y = analogRead(A1);
      

   // Serial.println(x);
   // Serial.println('\n');
   // Serial.println(y);
      while(Serial.available())
          {
                if(gps.encode(Serial.read()))// encode gps data 
                  {
                       gps.f_get_position(&lati, &longi);
                        
                  }

          }


          
      if((x<270 || x>430) && (y<270 || y>430) )
        {
            //Serial.println("Acsident occured");
            //Serial.println(lati);
            //Serial.println(longi);
            
            lcd.setCursor(0,0);
            lcd.print("     ALERT      ");           
            lcd.setCursor(0,1);
            lcd.print("Acsident occured");
            digitalWrite(motor,LOW);
            digitalWrite(buz,HIGH);
            delay(3000);
            
            lcd.setCursor(0,0);
            lcd.print("SENDING LOCATION"); 
            
            lcd.setCursor(0,1);
            lcd.print("ON 738 738 9299 "); 
               
            SendMessage();


            lcd.setCursor(0,0);
            lcd.print("  LOCATION SENT ");
            lcd.setCursor(0,1);
            lcd.print("  SUCCSSESFULLY ");
            delay(3000);
            
             //send sms   
        }

      

 // else
     
        
      
      if (c=='A')
        {
          //Serial.println("A");
      
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("SMART HELMET RX ");
          lcd.setCursor(0,1);
          lcd.print("ALCOHOL DETECTED");

          digitalWrite(motor,LOW);
          digitalWrite(buz,HIGH);
        }


      else if (c=='S')
        {
          //Serial.println("S");
          
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("SMART HELMET RX ");
          lcd.setCursor(0,1);
          lcd.print("PERFECT STATE   ");
          
          digitalWrite(motor,HIGH);
          digitalWrite(buz,LOW);
        }

      else if (c=='H')
        {
          //Serial.println("H");
          
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("SMART HELMET RX ");
          lcd.setCursor(0,1);
          lcd.print("WEAR YOUR HELMET");
          
          digitalWrite(motor,LOW);
          digitalWrite(buz,LOW);
        }

      else if (c=='B')
        {
          //Serial.println("B");

          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("ALCOHOL CONSUMED");
          lcd.setCursor(0,1);
          lcd.print("WEAR YOUR HELMET");
          
          digitalWrite(motor,LOW);
          digitalWrite(buz,HIGH);
        } 
     
  }













void SendMessage()
  {
    Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
    delay(1000);  // Delay of 1000 milli seconds or 1 second
    Serial.println("AT+CMGS=\"+917387389299\"\r"); // Replace x with mobile number//
    delay(1000);
    Serial.println("Accsident Occured at");// The SMS text you want to send
    delay(1000);
    Serial.println(lati);
    Serial.println(longi);
    delay(1000);
    Serial.println((char)26);// ASCII code of CTRL+Z
    delay(1000);
  }
