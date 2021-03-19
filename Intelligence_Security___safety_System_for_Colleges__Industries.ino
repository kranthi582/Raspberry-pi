
#include<LiquidCrystal.h>

int RS=12;
int EN=11;
int D4=7;
int D5=6;
int D6=5;
int D7=4;
int gas_sensor=2;
int buzzer=10;
int flag;
bool sms_flag=0;
LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);
//SoftwareSerial  mySerial(9, 10);  

//int Rx=9;
//int Tx=10;

void setup()
{
 Serial.begin(9600);
// mySerial.begin(9600);
 Serial.println("Hello");
 lcd.begin(16,2);
 lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Intelligence");
  lcd.setCursor(0,1);
  lcd.print("Safety System");
  delay(1000);

  pinMode(gas_sensor,INPUT);
  pinMode(buzzer,OUTPUT);
}

void loop() 
{
 int gas_value=digitalRead(gas_sensor);
  Serial.print("Gas value:");
  Serial.println(gas_value);
  delay(1000);
  if (gas_value==0)
  {
    
    lcd.clear();
    lcd.print("Gas Leaked");
    lcd.setCursor(0,1);
    lcd.print("EMERGENCY");
    delay(1000);
    if(sms_flag==0)
    {
      sms_flag=1;
    digitalWrite(buzzer,HIGH);
      sendsms();
      lcd.setCursor(0,0);
      lcd.print("buzzer on");
      flag=0;
      delay(1000);
    }
  }
  else
  {
    sms_flag=0;
    digitalWrite(buzzer,LOW);
    lcd.setCursor(0,0);
  lcd.print("Intelligence");
  lcd.setCursor(0,1);
  lcd.print("Safety System");
  delay(1000);

  }
  delay(1000);
}

void sendsms()
  {
    Serial.println("AT+CMGF=1");
    delay(1000);
    Serial.println("AT+CMGS=\"+919526234625\"\r");
    delay(1000);
   Serial.print("EMERGENCY:Gas Leaked");
//    delay(10);
   //Serial.println( link);
   // delay(100);
    //Serial.write(26);
   Serial.println((char)26); // ASCII code of CTRL+Z
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("msg send");
  }
