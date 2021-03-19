
#include <Stepper.h>

int buzzer=7;
const int D0 = 5;  // Defining Digital Input Pins from DTMF Module
const int D1 = 6;
int SoQ1 = 0;     // Defining variable to store the status(HIGH/LOW) of above inputs.
int SoQ2 = 0;
int oldCon = 0;  //  Variable to know what was the last button pressed.

//const int stepsPerRevolution = 200; 
//Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

int S1=8;
int S2=9;
int S3=10;
int S4=11;

void setup()
{
  Serial.begin(9600);   // Setup Serial Communication.  
  pinMode(D0, INPUT);  // Defining pins as input.
  pinMode(D1, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(S4, OUTPUT);
 // myStepper.setSpeed(60);
}

void loop() 
{
  SoQ1 = digitalRead(D0);  // Reading status of Input Pins. It can be LOW or HIGH
  SoQ2 = digitalRead(D1);

  if(SoQ2==LOW && SoQ1==HIGH )               // Condition for Button 1. It is equal to Binary - 0001 
  {
    if (oldCon!=1)
    { 
      door_open();
    }
    oldCon=1;
  }

  else if(SoQ2==HIGH && SoQ1==LOW )               // Condition for Button 1. It is equal to Binary - 0001 
    {
      if (oldCon!=2)
      { 
        door_close();
      }
      oldCon=2;
    }

  else if(SoQ2==HIGH && SoQ1==HIGH )               // Condition for Button 1. It is equal to Binary - 0001 
    {
      if (oldCon!=3)
      { 
        buzzer_on();
      }
      oldCon=3;
    }
  
}


void door_open()
{
  Serial.println("Open Door");
 // myStepper.step(stepsPerRevolution);
   for(int i = 0; i<120; i++)
  {
    digitalWrite(S4, HIGH);
    digitalWrite(S3, LOW);
    digitalWrite(S2, LOW);
    digitalWrite(S1, LOW);
    delay(5);
    digitalWrite(S4, HIGH);
    digitalWrite(S3, HIGH);
    digitalWrite(S2, LOW);
    digitalWrite(S1, LOW);
    delay(5);
    digitalWrite(S4, LOW);
    digitalWrite(S3, HIGH);
    digitalWrite(S2, LOW);
    digitalWrite(S1, LOW);
    delay(5);
    digitalWrite(S4, LOW);
    digitalWrite(S3, HIGH);
    digitalWrite(S2, HIGH);
    digitalWrite(S1, LOW);
    delay(5);
    digitalWrite(S4, LOW);
    digitalWrite(S3, LOW);
    digitalWrite(S2, HIGH);
    digitalWrite(S1, LOW);
    delay(5);
    digitalWrite(S4, LOW);
    digitalWrite(S3, LOW);
    digitalWrite(S2, HIGH);
    digitalWrite(S1, HIGH);
    delay(5);
    digitalWrite(S4, LOW);
    digitalWrite(S3, LOW);
    digitalWrite(S2, LOW);
    digitalWrite(S1, HIGH);
    delay(5);
    digitalWrite(S4, HIGH);
    digitalWrite(S3, LOW);
    digitalWrite(S2, LOW);
    digitalWrite(S1, HIGH);
    delay(5);
  }
  digitalWrite(S4, HIGH);
  digitalWrite(S3, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S1, LOW);
  delay(5);

  delay(10);
}

void door_close()
{
  Serial.println("Close Door");
 for(int j = 0; j<120; j++)
  {
    digitalWrite(S4, LOW);
    digitalWrite(S3, LOW);
    digitalWrite(S2, LOW);
    digitalWrite(S1, HIGH);
    delay(5);
    digitalWrite(S4, LOW);
    digitalWrite(S3, LOW);
    digitalWrite(S2, HIGH);
    digitalWrite(S1, HIGH);
    delay(5);
    
    digitalWrite(S4, LOW);
    digitalWrite(S3, LOW);
    digitalWrite(S2, HIGH);
    digitalWrite(S1, LOW);
    delay(5);
    digitalWrite(S4, LOW);
    digitalWrite(S3, HIGH);
    digitalWrite(S2, HIGH);
    digitalWrite(S1, LOW);
    delay(5);
    
    digitalWrite(S4, LOW);
    digitalWrite(S3, HIGH);
    digitalWrite(S2, LOW);
    digitalWrite(S1, LOW);
    delay(5);
    digitalWrite(S4, HIGH);
    digitalWrite(S3, HIGH);
    digitalWrite(S2, LOW);
    digitalWrite(S1, LOW);
    delay(5);
    
    digitalWrite(S4, HIGH);
    digitalWrite(S3, LOW);
    digitalWrite(S2, LOW);
    digitalWrite(S1, LOW);
    delay(5);
    digitalWrite(S4, HIGH);
    digitalWrite(S3, LOW);
    digitalWrite(S2, LOW);
    digitalWrite(S1, HIGH);
    delay(5);
  }
  digitalWrite(S4, LOW);
  digitalWrite(S3, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S1, HIGH);
  delay(10);
}

void buzzer_on()
{
  digitalWrite(buzzer, HIGH);
        delay(2000);
        digitalWrite(buzzer,LOW);
        delay(2000);
}

