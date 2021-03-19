#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("LIFI TX!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(2400);
    mySerial.write('h');
      mySerial.write('e');
        mySerial.write('l');
 
}

void loop() { // run over and over
 
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}



