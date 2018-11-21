#define true 1
#define disp PORTB
#define deco PORTD
#define sensor PORTA.F5

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
    disp = seg[a]<<1;
    deco = ~dec[i];
    DELAY_us(1000);
    deco = 0xFF;
  }
}