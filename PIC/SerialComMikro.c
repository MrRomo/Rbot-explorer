#define Transmiter PORTB
unsigned char Data = 0;
void main(){
  UART1_Init(9600);

  TRISB=0x00;
  PORTB=0X00;
  delay_ms(100);

  while(1){
    Transmiter = Data;
    delay_ms(10);
    Data+= 1;
    if(Data>=16){
     Data = 0;
    }
  }
}