// Definiciones de pines usados para los motores//
#define PIN_MOTOR_R_FWD 26
#define PIN_MOTOR_R_BWD 18
#define PIN_MOTOR_L_FWD 19
#define PIN_MOTOR_L_BWD 23

char transmiter[4] = {26,18,19,23};
char value[4];
void setup() {
 
  pinMode(PIN_MOTOR_R_FWD, OUTPUT);
  pinMode(PIN_MOTOR_R_BWD, OUTPUT);
  pinMode(PIN_MOTOR_L_FWD, OUTPUT);
  pinMode(PIN_MOTOR_L_BWD, OUTPUT);
  Serial.begin(115200);
}

void loop() {
    motion(LOW, HIGH, HIGH, LOW);
    delay(2000);
    motion(HIGH, LOW, LOW, HIGH);
    delay(2000);
    motion(HIGH, LOW, HIGH, LOW);
    delay(2000);
    motion(LOW, HIGH, LOW, HIGH);
    delay(2000);
    motion(LOW, LOW, LOW, LOW);
    delay(2000); 
}


void motion(int R_FWD, int R_BWD, int L_FWD, int L_BWD) {
  digitalWrite(PIN_MOTOR_R_FWD, R_FWD);
  digitalWrite(PIN_MOTOR_R_BWD, R_BWD);
  digitalWrite(PIN_MOTOR_L_FWD, L_FWD);
  digitalWrite(PIN_MOTOR_L_BWD, L_BWD);
}
