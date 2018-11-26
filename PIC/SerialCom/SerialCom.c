int a = 523;
char txt[6]={0};
void setup();

void main() {
    setup();
    UART1_Init(9600);
    Delay_ms(200);                  // Wait for UART module to stabilize

  while (1) {
    UART1_Write(50);
    delay_ms(1000);
  }
}

void setup () {
  ANSEL = 0X00;
  ANSELH = 0X00;
  TRISA = 0X00;
  TRISB = 0X50;
  TRISD = 0X00;

}