
int m1=6;
int m2=7;
int m3=8;
int m4=9;

int trigr=2;
int echo=3;
long duration;
int distance;

char state;
int flag;
int k=0;
int n=1;

void setup() 
{
  Serial.begin(9600);
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  pinMode(m3,OUTPUT);
  pinMode(m4,OUTPUT);
  pinMode(trigr,OUTPUT);
  pinMode(echo,INPUT);

  Serial.println("PROJECT");
}


void loop() 
{
 
if(Serial.available())
  {
    state=Serial.read();
    Serial.print(state);
    
//  if(state=='f')
//  {
//     k=1;
//    digitalWrite(m1,HIGH);
//    digitalWrite(m2,LOW);
//    digitalWrite(m3,HIGH);
//    digitalWrite(m4,LOW);
//    Serial.println("Motor: Forward");
//  }
//   else if(state=='q')
//   {
//   
//       digitalWrite(m5,LOW);//DOWN
//    digitalWrite(m6,HIGH);
//    delay(1000);
//    digitalWrite(m5,LOW);
//      digitalWrite(m6,LOW);
//      
//    digitalWrite(m7,HIGH); //CLOSE
//    digitalWrite(m8,LOW);
//    delay(500);
//     digitalWrite(m7,LOW);
//    digitalWrite(m8,LOW);
//    
//    delay(500);
//    digitalWrite(m5,HIGH); ///UP
//    digitalWrite(m6,LOW);
//    delay(1000);
//    digitalWrite(m5,LOW);
//      digitalWrite(m6,LOW);
//      
//     }

  if(state=='c')
   {
     arm_close();
   }
   
   else if(state=='u')  //up
   {
    arm_up();
   }
   
   else if(state=='d')  //down
   {
    arm_down();
   }
   
   else if(state=='o')
   {
    arm_open();
   }
  
  
  else if(state=='s')
  {
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,LOW);
  Serial.println("Motor: OFF");
    }
    
 else if(state=='t')
 {
  distance_val();
 }
}
}


void  arm_close()
{
  Serial.println("Close ARM");
 digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    delay(500);
     digitalWrite(m1,LOW);
    digitalWrite(m2,LOW); 
}

void arm_open()

 {
    Serial.println("Open ARM");
     digitalWrite(m1,LOW);
    digitalWrite(m2,HIGH);
    delay(500);
     digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
   }

void arm_up()
{
  Serial.println("ARM UP");
   digitalWrite(m3,HIGH); ///UP
    digitalWrite(m4,LOW);
    delay(500);
       digitalWrite(m3,LOW);
    digitalWrite(m4,LOW);
}

void arm_down()
{
    Serial.println("ARM DOWN");
      digitalWrite(m3,LOW);//DOWN
    digitalWrite(m4,HIGH);
    delay(500);
      digitalWrite(m3,LOW);
    digitalWrite(m4,LOW);
}

void distance_val()
{
 digitalWrite(trigr,LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigr,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigr,LOW);
  
  duration=pulseIn(echo,HIGH);
  distance=(duration*0.034)/2;
  Serial.print("Distance= ");
  Serial.println(distance);
}
