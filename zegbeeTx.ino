#include<LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
#include <SoftwareSerial.h>
static const int RXPin = 10, TXPin = 11;
SoftwareSerial zigbee(RXPin, TXPin);

int ir=8;
int alc=9;
int i,j;
int a,b,c,d;

 
void setup() 
  {
        // put your setup code here, to run once:
      Serial.begin(9600);
      zigbee.begin(9600);
      pinMode(ir,INPUT);
      pinMode(alc,INPUT);
      lcd.begin(16,2);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("SMART HELMET TX");
      delay(4000);
  }





void loop() 
  {

    i = digitalRead(ir);
    j = digitalRead(alc);
  
  if(i==HIGH && j==LOW)
     {
        zigbee.print('A');   
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("    HELMET ON   ");
        lcd.setCursor(0,1);
        lcd.print("ALCOHOL DETECTED");
     }

  if(i==HIGH && j==HIGH)
    {
       zigbee.print('S'); 
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("   HELMET ON    ");
       lcd.setCursor(0,1);   
       lcd.print("   NO ALCOHOL   "); 
    }

  
 if(i==LOW && j==HIGH)
    {
       zigbee.print('H');  
       lcd.clear();
       lcd.setCursor(0,0);   
       lcd.print("   NO HELMET    ");
       lcd.setCursor(0,1);   
       lcd.print("   NO ALCOHOL   ");
    }



  if(i == LOW && j==LOW)  //no helmet & alcohol
    {
       zigbee.print('B');  
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("    NO HELMET   ");
       lcd.setCursor(0,1);
       lcd.print("ALCOHOL DETECTED");
    }


 delay(2000);


  
}


