#line 1 "P:/Google/Universidad/2018_II/Microprocesamiento/Tercer Seguimiento/Rbot-explorer/PIC/RbotController/RbotController.c"



void setup();
void motion();


void main(){
 ANSEL = 0X00;
 TRISA=0x00;
 TRISD=0XFF;
  PORTA  = 0x00;
 while(1){

 motion();

 }
}
void motion() {
 switch ( PORTD<<4 ) {
 case (0x00)||(0x0A)||(0x06)||(~0x0A)||(~0x06):
  PORTA  =  PORTD<<4 ;
 break;
 case (0x01):
  PORTA  =  PORTD<<4 ;
 delay_ms(200);
  PORTA  = 0x00;
 break;
 }
}
void setup(){
 ANSEL = 0X00;
 TRISA = 0x00;
 TRISD = 0XFF;
}
