#define BUS PORTB
#define HBriged PORTA
#define INPUT PORTD>>4
#define true 1
#define false 0
#define Forward 0x0A
#define Backward ~0x0A
#define Left 0x06
#define Right ~0x06
#define Stop 0x00
#define LeftQ 0x02
#define RightQ 0x01
#define ECCHO PORTD.F1
#define TRIGGER PORTD.F0


void servo();
void setup();
void motion();
void watcher();
void test();
void gira(unsigned long grados);
void VDelay_us(unsigned time_us);

unsigned int  a;
unsigned char b;

int pos=0;
char CW = true;
void main(){
  setup();
  while(1){
    servo();
    motion();
    watcher();
    //PORTA = PORTD>>4;
  }
}
void  motion() {
  switch (INPUT) {
    case (Stop||Forward||Backward||Right||Left):
         HBriged = INPUT;
         break;
  }
}
void setup(){
  ANSEL = 0X00;
  ANSELH=0x00;
  TRISA = 0x00;
  TRISB=0x00;
  TRISD = 0X02;           //RD1 as Input PIN (ECHO)
  HBriged = 0x00;
  T1CON = 0x10;                 //Initialize Timer Module
  BUS = 0x69;
  delay_ms(3000);
}

void test() {
    HBriged = 0x0A;
    delay_ms(1000);
    HBriged = 0x00;
    delay_ms(20);
    HBriged = ~0x0A;
    delay_ms(1000);
    HBriged = 0x00;
    delay_ms(20);
    HBriged = 0x06;
    delay_ms(1000);
    HBriged = 0x00;
    delay_ms(20);
    HBriged = ~0x06;
    delay_ms(1000);
    HBriged = 0x00;
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

void watcher(){
    TMR1H = 0;                  //Sets the Initial Value of Timer
    TMR1L = 0;                  //Sets the Initial Value of Timer
    TRIGGER = 1;               //TRIGGER HIGH
    Delay_us(10);               //10uS Delay
    TRIGGER = 0;               //TRIGGER LOW
    while(!ECCHO);           //Waiting for Echo
    T1CON.F0 = 1;               //Timer Starts
    while(ECCHO);            //Waiting for Echo goes LOW
    T1CON.F0 = 0;               //Timer Stops
    a = (TMR1L|(TMR1H<<8));   //Reads Timer Value
    a = a/58.82;                //Converts Time to Distance
    a = (a + 1)*2;                  //Distance Calibration
    if(a<250){
     b = a;
    }
    BUS = b;
}