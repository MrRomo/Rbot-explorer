#line 1 "P:/Google/Universidad/2018_II/Microprocesamiento/Tercer Seguimiento/Rbot-explorer/PIC/RbotController/RbotController.c"






void setup();
void servo();
void motion();

void gira(unsigned long grados);
void VDelay_us(unsigned time_us);
int pos=0;
char CW =  1 ;
void main(){

 ANSEL = 0X00;
 TRISA=0x00;
 TRISD=0XFF;
  PORTA  = 0x00;

 while(1){
 servo();
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
 TRISB=0x00;
 ANSELH=0x00;
 PORTB=0x00;
}

void servo(){
 gira(pos);
 delay_ms(300);
 if(CW){
 pos+=5;
 }else {
 pos-=5;
 }
 if(pos==180){
 CW =  0 ;
 }
 if(pos==0){
 CW =  1 ;
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
 VDelay_us(19000);
 }
}
