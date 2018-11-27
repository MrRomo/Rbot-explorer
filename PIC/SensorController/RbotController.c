
void main()
{
  unsigned int  a;

  char txt[7];
  unsigned int mostrar[4];

  ANSEL = 0x00;
  ANSELH = 0x00;
  TRISA = 0X00;
  PORTA = 0X00;
  PORTB = 0X00;
  TRISB = 0X10;           //RB4 as Input PIN (ECHO)

  Lcd_Out(1,1,"Developed By");
  Lcd_Out(2,1,"electroSome");

  Delay_ms(3000);
  Lcd_Cmd(_LCD_CLEAR);

  T1CON = 0x10;                 //Initialize Timer Module

  while(1)
  {
    TMR1H = 0;                  //Sets the Initial Value of Timer
    TMR1L = 0;                  //Sets the Initial Value of Timer

    PORTB.F0 = 1;               //TRIGGER HIGH
    Delay_us(10);               //10uS Delay
    PORTB.F0 = 0;               //TRIGGER LOW

    while(!PORTB.F4);           //Waiting for Echo
    T1CON.F0 = 1;               //Timer Starts
    while(PORTB.F4);            //Waiting for Echo goes LOW
    T1CON.F0 = 0;               //Timer Stops

    a = (TMR1L | (TMR1H<<8));   //Reads Timer Value
    a = a/58.82;                //Converts Time to Distance
    a = (a + 1)*2;                  //Distance Calibration
    PORTA=a;

    if(a>=2 && a<=400)          //Check whether the result is valid or not
    {
      IntToStr(a,txt);
      Ltrim(txt);
      Lcd_Cmd(_LCD_CLEAR);
      Lcd_Out(1,1,"Distance = ");
      Lcd_Out(1,12,txt);
      Lcd_Out(1,15,"cm");
    }
    else
    {
      Lcd_Cmd(_LCD_CLEAR);
      Lcd_Out(1,1,"Out of Range");
    }
    Delay_ms(400);
  }
}