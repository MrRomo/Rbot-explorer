#line 1 "P:/Google/Universidad/2018_II/Microprocesamiento/Tercer Seguimiento/Rbot-explorer/PIC/SensorController/SensorController.c"

void main()
{
 unsigned int a;

 char txt[7];
 unsigned int mostrar[4];

 ANSEL = 0x00;
 ANSELH = 0x00;
 TRISA = 0X00;
 PORTA = 0X00;
 PORTB = 0X00;
 TRISB = 0X10;


 Delay_ms(3000);

 T1CON = 0x10;

 while(1)
 {
 TMR1H = 0;
 TMR1L = 0;
 PORTB.F0 = 1;
 Delay_us(10);
 PORTB.F0 = 0;
 while(!PORTB.F4);
 T1CON.F0 = 1;
 while(PORTB.F4);
 T1CON.F0 = 0;
 a = (TMR1L | (TMR1H<<8));
 a = a/58.82;
 a = (a + 1)*2;
 PORTA = a;
 }
}
