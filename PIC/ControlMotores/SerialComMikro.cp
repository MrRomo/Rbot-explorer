#line 1 "P:/Google/Universidad/2018_II/Microprocesamiento/Tercer Seguimiento/Rbot-explorer/PIC/ControlMotores/SerialComMikro.c"



void main(){
 ANSEL = 0X00;
 TRISA=0x00;
 TRISD=0XFF;
  PORTA  = 0x00;
 while(1){
  PORTA  = PORTD>>4;
 }

}

void direction(){
  PORTA  = 0x00;
 delay_ms(2000);
  PORTA  = 0x0A;
 delay_ms(2000);
  PORTA  = 0x06;
 delay_ms(2000);
  PORTA  = ~0x0A;
 delay_ms(2000);
  PORTA  = ~0x06;
 delay_ms(2000);
}
