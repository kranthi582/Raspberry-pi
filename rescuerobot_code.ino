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
int m5=8; //A
int m6=9; // B
int m7=10; //C
int m8=11; //D
char state;
int flag;
int k=0;
int n=1;

void setup() 
{
 // Servo1.attach(servoPin); 
  Serial.begin(9600);
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  pinMode(m3,OUTPUT);
  pinMode(m4,OUTPUT);
   pinMode(m5,OUTPUT);
  pinMode(m6,OUTPUT);
  pinMode(m7,OUTPUT);
  pinMode(m8,OUTPUT);
  Serial.println("PROJECT");
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
   
       digitalWrite(m5,LOW);//DOWN
    digitalWrite(m6,HIGH);
    delay(1000);
    digitalWrite(m5,LOW);
      digitalWrite(m6,LOW);
      
    digitalWrite(m7,HIGH); //CLOSE
    digitalWrite(m8,LOW);
    delay(500);
     digitalWrite(m7,LOW);
    digitalWrite(m8,LOW);
    
    delay(500);
    digitalWrite(m5,HIGH); ///UP
    digitalWrite(m6,LOW);
    delay(1000);
    digitalWrite(m5,LOW);
      digitalWrite(m6,LOW);
      
     }

   else if(state=='c')
   {
     arm_close();
   }
   else if(state=='d')  //up
   {
    arm_up();
   }
   else if(state=='e')  //down
   {
    arm_down();
   }
   else if(state=='o')
   {
    arm_open();
   }
  else if(state=='b')
  {
    digitalWrite(m1,LOW);
    digitalWrite(m2,HIGH);
    digitalWrite(m3,LOW);
    digitalWrite(m4,HIGH);
        Serial.println("Motor: Backward");
        flag=1;
  }
  
  else if(state=='r')
  {
    digitalWrite(m1,LOW);
    digitalWrite(m2,HIGH);
    digitalWrite(m3,HIGH);
    digitalWrite(m4,LOW);
    
        Serial.println("Motor: Right-Turn");
  }

  else if(state=='l')
  {
    digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,HIGH);
    Serial.println("Motor: Left Turn");
  }
  
  else if(state=='s')
  {
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,LOW);
      digitalWrite(m5,LOW);
    digitalWrite(m6,LOW);
    digitalWrite(m7,LOW);
    digitalWrite(m8,LOW);
  Serial.println("Motor: OFF");
    }

}
}


void  arm_close()
{
 digitalWrite(m7,HIGH);
    digitalWrite(m8,LOW);
    delay(500);
     digitalWrite(m7,LOW);
    digitalWrite(m8,LOW); 
}

void arm_open()

 {
     digitalWrite(m7,LOW);
    digitalWrite(m8,HIGH);
    delay(500);
     digitalWrite(m7,LOW);
    digitalWrite(m8,LOW);
   }

void arm_up()
{
   digitalWrite(m5,HIGH); ///UP
    digitalWrite(m6,LOW);
    delay(500);
       digitalWrite(m5,LOW);
    digitalWrite(m6,LOW);
}

void arm_down()
{
      digitalWrite(m5,LOW);//DOWN
    digitalWrite(m6,HIGH);
    delay(500);
      digitalWrite(m5,LOW);
    digitalWrite(m6,LOW);
}

