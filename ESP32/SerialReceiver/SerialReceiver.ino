void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
    Serial.println("hola");
    delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available()) {
    char a = Serial.read(); // read the incoming data as string
    Serial.println(a);
  }

}
