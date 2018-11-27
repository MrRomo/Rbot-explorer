unsigned char Data;
char receiver[8] = {16,17,21,22,23,19,18,26};


void setup() {
  // put your setup code here, to run once:
  for (char i = 0; i < 8; i++) {
    pinMode(receiver[i],INPUT);
  }
  Serial.begin(115200);
  Serial.println("Start");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Data = 0;
  for (char i = 0; i < 8; i++) {
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
