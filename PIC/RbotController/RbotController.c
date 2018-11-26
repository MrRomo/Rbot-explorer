#define Receiver PORTB
#define HBriged PORTA
#define INPUT PORTD<<4
void setup();
void  motion();


void main(){
  ANSEL = 0X00;
  TRISA=0x00;
  TRISD=0XFF;
  HBriged = 0x00;
  while(1){

    motion();

  }
}
void  motion() {
  switch (INPUT) {
    case (0x00)||(0x0A)||(0x06)||(~0x0A)||(~0x06):
      HBriged = INPUT;
      break;
    case (0x01):
      HBriged = INPUT;
      delay_ms(200);
      HBriged = 0x00;
      break;
  }
}
void setup(){
  ANSEL = 0X00;
  TRISA = 0x00;
  TRISD = 0XFF;
}
