#define ECCHO PORTD.F1
#define TRIGGER PORTD.F0
void main()
{
  unsigned int  a;
  unsigned char b;
  ANSEL = 0x00;
  ANSELH = 0x00;
  TRISB = 0X00;
  PORTB = 0X00;
  TRISD = 0X02;           //RD1 as Input PIN (ECHO)
  PORTD = 0X00;
  Delay_ms(3000);
  T1CON = 0x10;                 //Initialize Timer Module
  PORTB = 0x69;
  delay_ms(3000);

  while(1)
  {
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
    PORTB = b;
  }
}