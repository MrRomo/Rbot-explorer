
#include <SoftwareSerial.h>
bool check = false;

SoftwareSerial mySerial(10, 11); // RX, TX
String msg;
void setup(){
  //inicia el puerto serial
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
     
}
void loop(){
  while (mySerial.available()) {
    char conteo = mySerial.read();  
    Serial.print(conteo);
    Serial.print("--");
    check = true;
  }
  if(check){
    Serial.println("");
    check = false;
   }
  
}





  
  
  

