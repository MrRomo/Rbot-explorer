#define Receiver PORTB
#define HBriged PORTA

void main(){
  ANSEL = 0X00;
  TRISA=0x00;
  TRISD=0XFF;
  HBriged = 0x00;
  while(1){
     HBriged = PORTD>>4;
  }
  
}

void direction(){
    HBriged = 0x00;
    delay_ms(2000);
    HBriged = 0x0A;//derecha
    delay_ms(2000);
    HBriged = 0x06;//atras
    delay_ms(2000);
    HBriged = ~0x0A;//Izquierda
    delay_ms(2000);
    HBriged = ~0x06;//Adelante
    delay_ms(2000);
}