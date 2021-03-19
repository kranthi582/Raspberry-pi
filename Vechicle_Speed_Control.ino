#include<LiquidCrystal.h>
int RS=12;
int EN=11;
int D4=10;
int D5=9;
int D6=8;
int D7=7;
LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);
char data[12],temp[12];
char school[]="3600A48B1F06", Hospital[]="3600A46E708C" , Park[]="3600A49F4F42";
int i,j,flag=0;
int m1=5;
int m2=6;

void setup()
{
 Serial.begin(9600);
 lcd.begin(16,2);
 pinMode(m1,OUTPUT);
 pinMode(m2,OUTPUT);
 lcd.print("Speed Control");
 lcd.setCursor(0,1);
 lcd.print("System");
 delay(1000);
}

void loop()
{
  if(Serial.available())
  {
  char a=Serial.read();
    data[i]=a;
    i++;
  }

  
  if(i==12)
  {
    //int cmp_flag=-1;
  
      if ((compare(data,school)==1)|| (compare(data,Hospital)==1) )
      {
      Serial.print("Danger Zone");
      lcd.setCursor(0,0);
      for(int j=0;j<12;j++)
        {
          lcd.print(data[j]);
        }
      lcd.setCursor(0,1);
      lcd.print("Slow Speed");
      analogWrite(m1,100);
      analogWrite(m2,0);
      
      delay(3000);
      lcd.setCursor(0,0);
      lcd.print("Normal Speed");
      analogWrite(m1,255);
      analogWrite(m2,0);
      }
 
  
   else
    {
      lcd.clear();
      Serial.print("Safe Zone");
      lcd.setCursor(0,0);
      lcd.print("Normal Speed");
      analogWrite(m1,255);
      analogWrite(m2,0);
//      for(int j=0;j<12;j++)
//      {
//        //Serial.print(data[j]);
//        lcd.setCursor(0,1);
//        lcd.print(data[j]);
//      }
    }
 
  
//    else
//    {
//      Serial.print("Unknown Id");
//      lcd.setCursor(0,0);
//      lcd.print("Unknown Id");
//    }
       Serial.println();
    i=0;
  }
}

 
int compare( char *a,char *b)
{
  for(j=0;j<12;j++)
   {
    if(a[j]!=b[j])
   {
    return 0;
   }
   }
   return 1;
}

