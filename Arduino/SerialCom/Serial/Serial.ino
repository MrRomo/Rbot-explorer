void setup() {

  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

}

void loop() {
  while (Serial.available()) {
    char a = Serial.read(); // read the incoming data as string
    Serial.println(a);
  }
}
