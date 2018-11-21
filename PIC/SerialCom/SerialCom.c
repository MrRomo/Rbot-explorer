void setup();

void main() {
  UART1_Init(9600);
  setup();
  while (1) {
    UART1_Write(2);
    if(PORTB.f6){
      while(PORTB.f6);
      UART1_write(1);
       UART1_write(1);
        UART1_write(1); UART1_write(1);
    }
    if (UART1_Data_Ready() == 1) {
     char receive = UART1_Read();
     UART1_write(receive);
     if(receive>1){
      PORTD.f2 = 1;
      DELAY_MS(500);
      PORTD.f2 = 0;
      DELAY_MS(500);
     }
    }
  }
}

void setup () {
  ANSEL = 0X00;
  ANSELH = 0X00;
  TRISA = 0X00;
  TRISB = 0X50;
  TRISD = 0X00;
}