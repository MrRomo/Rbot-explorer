#define Transmiter PORTB
unsigned char Data = 0;
void main(){
  TRISB=0x00;
  PORTB=0X00;
  TRISC=0x00;
  PORTC=0X38;
  delay_ms(100);
  while(1){
    Transmiter = 0xf5;
    delay_ms(10);
    Data+= 1;
    if(Data>=16){
     Data = 0;
    }
  }
}