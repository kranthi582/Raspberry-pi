//Home made maximum power point tracking system

#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define LED_green 10
# define LED_white 8
///////////////////////////////////////////////////////////////////////
#define DEBUG true
String mySSID = "project";       // WiFi SSID
String myPWD = "123456789"; // WiFi Password
String myAPI = "L99BJG2PTQDUPAW4";   // API Key
String myHOST = "api.thingspeak.com";
String myPORT = "80";

String myFIELD1 = "field1";
String myFIELD2 = "field2";
String myFIELD3 = "field3";
 
float sendVal;
////////////////////////////////////////////////////////////////////////




const int Batery_voltageSensor = A0;
int Batery_value = 0;
float Batery_vOUT = 0.0;
float Batery_vIN = 0.0;

const int Solar_voltageSensor = A1;
int Solar_value = 0;
float Solar_vOUT = 0.0;
float Solar_vIN = 0.0;



float R1 = 30000.0;
float R2 = 7500.0;




const int currentPin = A2;
int sensitivity = 66;
int adcValue= 0;
int offsetVoltage = 2500;
double adcVoltage = 0;
double currentValue = 0;









void AfterBoot()
  {
        int i;
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(100);                       // wait for a second
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        delay(100);
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(100);                       // wait for a second
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        delay(100);
        lcd.begin(16, 2);
        lcd.print("     WELCOME    ");
        lcd.setCursor(0, 1);
        lcd.print("       TO       ");
        delay(2000);
        lcd.clear();
        delay(20);
        lcd.print("HOMEMADE MAXIMUM");
        lcd.setCursor(0, 1);
        lcd.print(" POWER POINT"); 
        delay(2000);
        lcd.clear();
        lcd.print(" TRACKING SYSTEM");
        delay(2000);
        lcd.clear();
        lcd.print("      MPPT      ");
     
  }



void connect_wifi()
  {
      espData("AT+RST", 1000, DEBUG);                      //Reset the ESP8266 module
      espData("AT+CWMODE=1", 1000, DEBUG);                 //Set the ESP mode as station mode
      espData("AT+CWJAP=\""+ mySSID +"\",\""+ myPWD +"\"", 1000, DEBUG);   //Connect to WiFi network
      /*while(!esp.find("OK")) 
      {          
          //Wait for connection
      }*/
//      String ip = "AT+CIFSR";
//     Serial1.println(ip);
//      Serial.print("ip is ");
//      delay(2000);
//      // Loop through all the data returned
//      while(Serial1.available()) 
//        {
//          // The esp has data so display its output to the serial window
//          char d = Serial1.read(); // read the next character.
//          Serial.write(d);
//        }
//    Serial.println("");   
      delay(1000);
  }




void setup() 
  {
    char c;
    Serial.begin(9600);
    Serial1.begin(115200);
    pinMode(LED_green, OUTPUT);
    pinMode(LED_white, OUTPUT);
    digitalWrite(LED_green, LOW);
    digitalWrite(LED_white, LOW);
    AfterBoot();
    delay(1000);
    Serial.println("hello word");
    connect_wifi();
    
  }






void loop() 
  {
     Batery_value = analogRead(Batery_voltageSensor);
     Batery_vOUT = (Batery_value * 5.0) / 1024.0;
     Batery_vIN = Batery_vOUT / (R2/(R1+R2));

     Solar_value = analogRead(Solar_voltageSensor);
     Solar_vOUT = (Solar_value * 5.0) / 1024.0;
     Solar_vIN = Solar_vOUT / (R2/(R1+R2));

     adcValue = analogRead(currentPin);
     adcVoltage = (adcValue / 1024.0) * 5000;
     currentValue = ((adcVoltage - offsetVoltage) / sensitivity);




     lcd.clear();
     lcd.print("BatV ");
     lcd.setCursor(0, 1);
     lcd.print(Batery_vIN);
      
     lcd.setCursor(5, 0);
     lcd.print("Sol_V ");
     lcd.setCursor(6, 1);
     lcd.print(Solar_vIN);

     lcd.setCursor(11, 0);
     lcd.print("Sol_I");
     lcd.setCursor(12, 1);
     lcd.print(currentValue);

     
     
    if(Batery_vIN >= 11.0)
        {
            digitalWrite(LED_white, HIGH);
            digitalWrite(LED_green, LOW);
           
          
        }

      else
        {
            digitalWrite(LED_white, LOW);
            digitalWrite(LED_green, HIGH);
          
         }  
        
     update_data();
     



     
  }



void update_data()
  {
        //sendVal = random(1000); // Send a random number between 1 and 1000
        sendVal = Batery_vIN; // Send a random number between 1 and 1000
        String sendData = "GET /update?api_key="+ myAPI +"&"+ myFIELD1 +"="+String(sendVal);
        espData("AT+CIPMUX=1", 1000, DEBUG);       //Allow multiple connections
        espData("AT+CIPSTART=0,\"TCP\",\""+ myHOST +"\","+ myPORT, 1000, DEBUG);
        espData("AT+CIPSEND=0," +String(sendData.length()+4),1000,DEBUG);  
        Serial1.find(">"); 
        Serial1.println(sendData);
        Serial.print("Value to be sent: ");
        Serial.println(sendVal);
        espData("AT+CIPCLOSE=0",1000,DEBUG);
        
        delay(5000);  
        
       // sendData = "\n";
        sendVal = currentValue; // Send a random number between 1 and 1000
         sendData = "GET /update?api_key="+ myAPI +"&"+ myFIELD2 +"="+String(sendVal);
        espData("AT+CIPMUX=1", 1000, DEBUG);       //Allow multiple connections
        espData("AT+CIPSTART=0,\"TCP\",\""+ myHOST +"\","+ myPORT, 1000, DEBUG);
        espData("AT+CIPSEND=0," +String(sendData.length()+4),1000,DEBUG);  
        Serial1.find(">"); 
        Serial1.println(sendData);
        Serial.print("Value to be sent: ");
        Serial.println(sendVal);
        espData("AT+CIPCLOSE=0",1000,DEBUG);

        delay(5000);

        
        //sendData = "\n";
        sendVal = Solar_vIN; // Send a random number between 1 and 1000
         sendData = "GET /update?api_key="+ myAPI +"&"+ myFIELD3 +"="+String(sendVal);
        espData("AT+CIPMUX=1", 1000, DEBUG);       //Allow multiple connections
        espData("AT+CIPSTART=0,\"TCP\",\""+ myHOST +"\","+ myPORT, 1000, DEBUG);
        espData("AT+CIPSEND=0," +String(sendData.length()+4),1000,DEBUG);  
        Serial1.find(">"); 
        Serial1.println(sendData);
        Serial.print("Value to be sent: ");
        Serial.println(sendVal);
        espData("AT+CIPCLOSE=0",1000,DEBUG);
        delay(5000);
        //sendData = "\n";
  }











  String espData(String command, const int timeout, boolean debug)
{
  Serial.print("AT Command ==> ");
  Serial.print(command);
  Serial.println("     ");
  
  String response = "";
  Serial1.println(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (Serial1.available())
    {
      char c = Serial1.read();
      response += c;
    }
  }
  if (debug)
  {
    //Serial.print(response);
  }
  return response;
}










