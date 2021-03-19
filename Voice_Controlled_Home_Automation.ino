int light=5;
int fan=6;
String data;

void setup() 
{
   Serial.begin(9600);
   pinMode(light, OUTPUT);
   pinMode(fan, OUTPUT);

   digitalWrite(light, LOW);
   digitalWrite(fan, LOW);
}

void loop() 
{
    int i=0;
    char ch=0;
    data="";
    while(1)
    { 
      while(Serial.available()<=0);
      ch = Serial.read();
      if(ch=='#')
      break;
      data+=ch;
    }
   Serial.println(data);
    
  
   if(data=="*turn on light")
    {
      digitalWrite(light,HIGH);
      Serial.println("light on");
    }
    
   else if(data=="*turn off light")
    {
      digitalWrite(light,LOW);
      Serial.println("light off");
    }
    
    else if(data=="*turn on fan")
    {
      digitalWrite(fan,HIGH);
      Serial.println("fan on");
    }
    
    else if(data=="*turn off fan")
    {
      digitalWrite(fan,LOW);
      Serial.println("fan off");
    }
    
   
    else if(data=="*turn on all")
    {
      digitalWrite(light,HIGH);
      digitalWrite(fan,HIGH);
      Serial.println("all on");
    }
    
    else if(data=="*turn off all")
    {
      digitalWrite(light,LOW);
      digitalWrite(fan,LOW);
      Serial.println("all off");
    }
    
}
