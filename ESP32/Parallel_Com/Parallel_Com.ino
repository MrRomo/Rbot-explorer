unsigned char Data;
char receiver[4] = {22,21,17,16};


void setup() {
  // put your setup code here, to run once:
  for (char i = 0; i < 4; i++) {
    pinMode(receiver[i],INPUT);
  }
  Serial.begin(115200);
  Serial.println("Start");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Data = 0;
  for (char i = 0; i < 4; i++) {
    Serial.print(digitalRead(receiver[i]));
    Data = (Data<<1)+digitalRead(receiver[i]);
  }
  Serial.print("Data : ");
  Serial.print(Data);
  Serial.println("");
}


int readPines() {
  Data = 0;
  for (char i = 0; i < 4; i++) {
    Serial.print(digitalRead(receiver[i]));
    Data = (Data<<1)+digitalRead(receiver[i]);
  }
  Serial.print("Data : ");
  Serial.print(Data);
  Serial.println("");
}
