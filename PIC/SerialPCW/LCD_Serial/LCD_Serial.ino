HardwareSerial Serial1(1);

void setup(){

  Serial.begin(115200);
  Serial1.begin(115200);
  Serial.println("Goodnight moon!");

}
void loop(){
  if(Serial1.available()) {   
    Serial.println(Serial1.read()>>1);
  }  
}





  
  
  

