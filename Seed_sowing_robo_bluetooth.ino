#include<Servo.h>
void seed();
// Declare the Servo pin 
int servoPin = 9; 
// Create a servo object 
Servo Servo1; 
int m1=2;
int m2=3;
int m3=4;
int m4=5;
char state;
int flag;
int k=0;

void setup() 
{
  Servo1.attach(servoPin); 
  Serial.begin(9600);
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  pinMode(m3,OUTPUT);
  pinMode(m4,OUTPUT);
  
  //attachInterrupt(0, pin_ISR, CHANGE);
}

void loop() 
{
 
if(Serial.available())
  {
    state=Serial.read();
    Serial.print(state);
    //flag=0;
//    Servo1.write(90); 
//    delay(500); 
//     Servo1.write(0); 
//   delay(500); 

  if(state=='f')
  {
     k=1;
    digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    digitalWrite(m3,HIGH);
    digitalWrite(m4,LOW);
    Serial.println("Motor: Forward");
  }
   else if(state=='q')
    {
    seed();    
     }
//     else
//     {
//       Servo1.write(0); 
//     }
  
  else if(state=='b')
  {
    digitalWrite(m1,LOW);
    digitalWrite(m2,HIGH);
    digitalWrite(m3,LOW);
    digitalWrite(m4,HIGH);
//    Servo1.write(180); 
//    delay(1000); 
//     Servo1.write(0); 
//   delay(1000); 
    
        Serial.println("Motor: Backward");
        flag=1;
  }
  
  else if(state=='r')
  {
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
    digitalWrite(m3,HIGH);
    digitalWrite(m4,LOW);
//    Servo1.write(180); 
//    delay(1000); 
//     Servo1.write(0); 
//   delay(1000); 
        Serial.println("Motor: Right-Turn");
  }

  else if(state=='l')
  {
    digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,LOW);
//    Servo1.write(180); 
//    delay(1000); 
//     Servo1.write(0); 
//   delay(1000); 
    Serial.println("Motor: Left Turn");
  }
  
  else if(state=='s')
  {
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,LOW);
//    Servo1.write(180); 
//    delay(1000); 
//     Servo1.write(0); 
//   delay(1000); 
  Serial.println("Motor: OFF");
    }

//else if(state=='p')
//  {
//    Servo1.write(90); 
//    delay(500); 
//     Servo1.write(0); 
//   delay(500); 
//  }
//// Servo1.write(90); 
// else 
//  {
//  Servo1.write(0); 
// }
}
}

 
void seed()
{
 while(true)
 {
    Servo1.write(90); 
    delay(500); 
     Servo1.write(0); 
    delay(500); 
    Serial.print("hello");
    if(Serial.available())
  {
    state=Serial.read();
  }
    if(state=='e'){
    Serial.write("exit");
    break;
 }
 }
}
