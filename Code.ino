#include <TinyGPS++.h>

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
///* Create object named bt of the class SoftwareSerial */
SoftwareSerial GPS_SoftSerial(10,9);/* (Rx, Tx) */
///* Create an object named gps of the class TinyGPSPlus */
TinyGPSPlus gps;      
//
//SoftwareSerial mySerial(9, 10);

volatile float minutes, seconds;
volatile int degree, secs, mins;
int led = 13;
int received = 0;
int i;
int buzzer=7;

void setup()
{
  Serial.begin(9600); /* Define baud rate for serial communication */
  GPS_SoftSerial.begin(9600); /* Define baud rate for software serial communication */
  //mySerial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() 
{
   smartDelay(1000); /* Generate precise delay of 1ms */
        unsigned long start;
        float speed_val;
        double lat_val, lng_val, alt_m_val;
        uint8_t hr_val, min_val, sec_val;
        bool loc_valid, alt_valid, time_valid;
        lat_val = gps.location.lat(); /* Get latitude data */
        loc_valid = gps.location.isValid(); /* Check if valid location data is available */
        lng_val = gps.location.lng(); /* Get longtitude data */
        alt_m_val = gps.altitude.meters();  /* Get altitude data in meters */
        alt_valid = gps.altitude.isValid(); /* Check if valid altitude data is available */
        hr_val = gps.time.hour(); /* Get hour */
        min_val = gps.time.minute();  /* Get minutes */
        sec_val = gps.time.second();  /* Get seconds */
        time_valid = gps.time.isValid();  /* Check if valid time data is available */
        speed_val = gps.speed.kmph();
        if (!loc_valid)
        {          
          Serial.print("Latitude : ");
          Serial.println("*****");
          Serial.print("Longitude : ");
          Serial.println("*****");
        }
        else
        {
          DegMinSec(lat_val);
          Serial.print("Latitude in Decimal Degrees : ");
          Serial.println(lat_val, 6);
//          Serial.print("Latitude in Degrees Minutes Seconds : ");
//          Serial.print(degree);
//          Serial.print("\t");
//          Serial.print(mins);
//          Serial.print("\t");
//          Serial.println(secs);
       
          DegMinSec(lng_val); /* Convert the decimal degree value into degrees minutes seconds form */
          Serial.print("Longitude in Decimal Degrees : ");
          Serial.println(lng_val, 6);
//          Serial.print("Longitude in Degrees Minutes Seconds : ");
//          Serial.print(degree);
//          Serial.print("\t");
//          Serial.print(mins);
//          Serial.print("\t");
//          Serial.println(secs);
         // Serial.println("http://www.google.com/maps/place/"+String(lat_val)+","+String(lng_val));
          Serial.print("Speed of Vehicle : ");
          Serial.println(speed_val);
        }
        if (!alt_valid)
        {
          Serial.print("Altitude : ");
          Serial.println("*****");
        }
        else
        {
          Serial.print("Altitude : ");
          Serial.println(alt_m_val, 6);    
        }
        if (!time_valid)
        {
          Serial.print("Time : ");
          Serial.println("*****");
        }
        else
        {
          char time_string[32];
          sprintf(time_string, "Time : %02d/%02d/%02d \n", hr_val, min_val, sec_val);
          Serial.print(time_string);    
        }

       
        
if (Serial.available() > 0)
  {
  received = Serial.read();
  Serial.println(received);
  
    if (received == 'a')
    {
    digitalWrite(led, HIGH);
    delay(2000);
    digitalWrite(led, LOW);
    Serial.println("Vechicle Without Helmet Identified");
    sendsms();
    
    }
     else if (received == 'b')
     {
      for(i=0;i<5;i++)
      {
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(1000);
    }
    //track_gps();
  } 
}
else if(speed_val>2)
        {
          Serial.println("Over Speed");
          digitalWrite(buzzer,HIGH);
          sendsms();
          digitalWrite(buzzer,LOW);
        }   
       
}




void sendsms()
  {
//    Serial.println("AT");
//    delay(1000);
    //Serial.println("ATD+919121991303;");
    //Serial.println("ATEO");
    //delay(1000);
//    mySerial.println("AT+CMGF=1");
    Serial.println("AT+CMGF=1");
    delay(1000);
  //  mySerial.println("AT+CMGS=\"+919526234625\"\r");
    Serial.println("AT+CMGS=\"+919526234625\"\r");
     //Serial.println("AT+CMGS=\"+919074598671\"\r");
    delay(1000);
   // mySerial.print("Traffic Rule Violation");
   Serial.print("Traffic Rule Violation");
//    delay(10);
   //MY_SERIAL.println( link);
    delay(100);
    //Serial.write(26);
  //  mySerial.println((char)26);
    Serial.println((char)26); // ASCII code of CTRL+Z
    delay(1000);
    //mySerial.println("Message Send");
    Serial.println("Message Send");
  }


static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (GPS_SoftSerial.available())  /* Encode data read from GPS while data is available on serial port */
      gps.encode(GPS_SoftSerial.read());
/* Encode basically is used to parse the string received by the GPS and to store it in a buffer so that information can be extracted from it */
  } while (millis() - start < ms);
}

void DegMinSec( double tot_val)   /* Convert data in decimal degrees into degrees minutes seconds form */
{  
  degree = (int)tot_val;
  minutes = tot_val - degree;
  seconds = 60 * minutes;
  minutes = (int)seconds;
  mins = (int)minutes;
  seconds = seconds - minutes;
  seconds = 60 * seconds;
  secs = (int)seconds;
}


