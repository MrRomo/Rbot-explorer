#define Receiver PORTB
#define HBriged PORTA
#define INPUT PORTD
#define true 1
#define false 0
#define Forward 0x0A;
#define Backward ~0x0A;
#define Left 0x06;
#define Right ~0x06;
#define Stop 0x00;
#define LeftQ 0x02;
#define RightQ 0x01;

void setup();
void servo();
void  motion();

void gira(unsigned long grados);
void VDelay_us(unsigned time_us);
int pos=0;
char CW = true;
void main(){
  setup();
  while(1){
    servo();
    //PORTA = PORTD>>4;

  }
}
void  motion() {
  switch (PORTD>>4) {
    case ((Stop)||(Forward)||(Backward)||(Left)||(Right)):
      PORTA = PORTD>>4;
      break;
    case (LeftQ)
      PORTA = Left;
      delay_ms(20);
      PORTA = Stop;
      break;
    case (RightQ)
      PORTA = Right;
      delay_ms(20);
      PORTA = Stop;
      break;
  }
}
void setup(){
  ANSEL = 0X00;
  TRISA = 0x00;
  TRISD = 0XFF;
  TRISB=0x00;
  ANSELH=0x00;
  PORTB=0x00;
  HBriged = 0x00;
}
void test() {
    PORTA = 0x0A;
    delay_ms(1000);
    PORTA = 0x00;
    delay_ms(20);
    PORTA = ~0x0A;
    delay_ms(1000);
    PORTA = 0x00;
    delay_ms(20);
    PORTA = 0x06;
    delay_ms(1000);
    PORTA = 0x00;
    delay_ms(20);
    PORTA = ~0x06;
    delay_ms(1000);
    PORTA = 0x00;
    delay_ms(20);
}
void servo(){
    gira(pos);
    if(CW){
      pos+=5;
    }else {
      pos-=5;
    }
    if(pos==180){
       CW = false;
    }
    if(pos==0){
       CW = true;
    }
  }

void VDelay_us(unsigned time_us){
     time_us/=16;
     while(time_us--){
          asm nop;
          asm nop;
      }
}
void gira(unsigned long grados){
     int i,valor;
     valor=((grados*1600)/180)+500;
     for (i=0;i<=50;i++){
         PORTB.F0=1;
         VDelay_us(valor);
         PORTB.F0=0;
         VDelay_us(5000);
     }
}
