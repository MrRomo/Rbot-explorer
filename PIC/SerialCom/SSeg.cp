#line 1 "P:/Google/Universidad/2018_II/Microprocesamiento/Tercer Seguimiento/RbotExplorerProject/PIC/SerialCom/SSeg.c"





char seg[10]= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
char dec[4] = {0x01,0x02,0x04,0x08};
char dec2[4] = {0x10,0x20,0x40,0x80};

void display(int num, char dec[4]) {
 char i;
 int a;
 int div = 1000;
 for (i = 0; i < 4; i++) {
 a = num/div;
 num = num - (a*div);
 div /= 10;
  PORTB  = seg[a]<<1;
  PORTD  = ~dec[i];
 DELAY_us(1000);
  PORTD  = 0xFF;
 }
}
