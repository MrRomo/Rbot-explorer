#line 1 "P:/Google/Universidad/2018_II/Microprocesamiento/Tercer Seguimiento/Rbot-explorer/PIC/RbotController/RbotController.c"
#line 15 "P:/Google/Universidad/2018_II/Microprocesamiento/Tercer Seguimiento/Rbot-explorer/PIC/RbotController/RbotController.c"
void servo();
void setup();
void motion();
void gira(unsigned long grados);
void VDelay_us(unsigned time_us);

int pos=0;
unsigned int a;
char CW =  1 ;
void main(){
 setup();
 while(1){
 servo();


 }
}
void motion() {
 switch (PORTD) {
 case  0x00; :
 PORTA = PORTD>>4;
 break;
 case ( 0x02; )
 PORTA =  0x06; ;
 delay_ms(20);
 PORTA =  0x00; ;
 break;
 case ( 0x01; )
 PORTA =  ~0x06; ;
 delay_ms(20);
 PORTA =  0x00; ;
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
  PORTA  = 0x00;
 TRISB = 0X10;
T1CON = 0x10;

 PORTA = 0x0A;
 delay_ms(1000);
 PORTA = 0x00;
 delay_ms(20);
 PORTA = ~0x0A;
 delay_ms(1000);
 PORTA = 0x00;
 delay_ms(20);
 PORTA = 0x06;
 delay_ms(1000);
 PORTA = 0x00;
 delay_ms(20);
 PORTA = ~0x06;
 delay_ms(1000);
 PORTA = 0x00;
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
