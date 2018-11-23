 char text  = 'A';
  char txt[5];
void main(){

  UART1_Init(9600);

  ByteToStr(text,txt);
  while(1){

    UART1_Write_text(text);
    delay_ms(500);

  }


}
