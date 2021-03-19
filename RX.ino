#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("lifi RX!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(1200);
 mySerial.println("RX!");
}
void loop() { // run over and over
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if(Serial.available())
  {
    mySerial.write(Serial.read());
     Serial.println('H');
  }
  
}

