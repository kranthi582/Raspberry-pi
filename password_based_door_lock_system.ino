#include <Keypad.h>
#include<LiquidCrystal.h>
int RS=A0;
int EN=A1;
int D4=A2;
int D5=A3;
int D6=A4;
int D7=A5;
LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
char key_array[4] , pass[4]="1234";
byte rowPins[ROWS] = {8, 7, 6, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 3, 2}; //connect to the column pinouts of the keypad
int i=0;

//Create an object of keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("PASSWORD BASED");
  lcd.setCursor(0,1);
  lcd.print("DOOR LOCK");
  delay(1000);
  lcd.clear();
}
  
void loop()
{
  //lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("Enter Password:");
//  delay(500);
  char key = keypad.getKey();   // Read the key
  if(key)
  {
  key_array[i]=key;
  i++;
  }
  //Print if key pressed
 if(i==4)
  {
  if (compare(key_array,pass)==1)
  {
    Serial.println("LoggedIn Successfully");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Logged IN");   
  }
    else if (compare(key_array,pass)==0)
    {
      Serial.println("Incorrect Password");
      lcd.setCursor(0,0);
      lcd.print("Incorrect Pass");
    }  
    i=0;
  }
  //lcd.clear();
}


int compare( char *a,char *b)
{
  for(int j=0;j<4;j++)
   {
    if(a[j]!=b[j])
   {
    return 0;
   }
   }
   return 1;
}

