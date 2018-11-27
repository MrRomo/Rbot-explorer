#line 1 "P:/Google/Universidad/2018_II/Microprocesamiento/Tercer Seguimiento/Rbot-explorer/PIC/RbotControllerFinal/RbotController.c"
#line 17 "P:/Google/Universidad/2018_II/Microprocesamiento/Tercer Seguimiento/Rbot-explorer/PIC/RbotControllerFinal/RbotController.c"
void servo();
void setup();
void motion();
void watcher();
void test();
void gira(unsigned long grados);
void VDelay_us(unsigned time_us);

unsigned int a;
unsigned char b;

int pos=0;
char CW =  1 ;
void main(){
 setup();
 while(1){
 servo();
 motion();
 watcher();

 }
}
void motion() {
 switch ( PORTD>>4 ) {
 case ( 0x00 || 0x0A || ~0x0A || ~0x06 || 0x06 ):
  PORTA  =  PORTD>>4 ;
 break;
 }
}
void setup(){
 ANSEL = 0X00;
 ANSELH=0x00;
 TRISA = 0x00;
 TRISB=0x00;
 TRISD = 0X02;
  PORTA  = 0x00;
 T1CON = 0x10;
  PORTB  = 0x69;
 delay_ms(3000);
}

void test() {
  PORTA  = 0x0A;
 delay_ms(1000);
  PORTA  = 0x00;
 delay_ms(20);
  PORTA  = ~0x0A;
 delay_ms(1000);
  PORTA  = 0x00;
 delay_ms(20);
  PORTA  = 0x06;
 delay_ms(1000);
  PORTA  = 0x00;
 delay_ms(20);
  PORTA  = ~0x06;
 delay_ms(1000);
  PORTA  = 0x00;
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
 VDelay_us(5000);
 }
}

void watcher(){
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
  PORTB  = b;
}
