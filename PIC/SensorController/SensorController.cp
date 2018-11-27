#line 1 "P:/Google/Universidad/2018_II/Microprocesamiento/Tercer Seguimiento/Rbot-explorer/PIC/SensorController/SensorController.c"


void main()
{
 unsigned int a;
 unsigned char b;
 ANSEL = 0x00;
 ANSELH = 0x00;
 TRISB = 0X00;
 PORTB = 0X00;
 TRISD = 0X02;
 PORTD = 0X00;
 Delay_ms(3000);
 T1CON = 0x10;
 PORTB = 0x69;
 delay_ms(3000);

 while(1)
 {
 TMR1H = 0;
 TMR1L = 0;
  PORTD.F0  = 1;
 Delay_us(10);
  PORTD.F0  = 0;
 while(! PORTD.F1 );
 T1CON.F0 = 1;
 while( PORTD.F1 );
 T1CON.F0 = 0;
 a = (TMR1L|(TMR1H<<8));
 a = a/58.82;
 a = (a + 1)*2;
 if(a<250){
 b = a;
 }
 PORTB = b;
 }
}
