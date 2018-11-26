void gira(unsigned long grados);
void VDelay_us(unsigned time_us);
void setup();
void main() {
     int pos=0;
     setup();
     while(1){
         /*gira(pos);
         delay_ms(1000);
         gira(30);
         delay_ms(1000);
         gira(60);
         delay_ms(1000);
         gira(90);
         delay_ms(1000);
         gira(120);
         delay_ms(1000);
         gira(150);
         delay_ms(1000);
         gira(180);
         delay_ms(1000);*/
          for(pos=0;pos<=180;pos=pos+10){
              gira(pos);
//              delay_ms(50);
              if(pos==180){
                  for(pos=180;pos>=0;pos=pos-10){
                      gira(pos);
                     // delay_ms(50);
                   }
               }
           }
           pos=0;
      }
}
void setup(){
     TRISB=0x00;
     ANSELH=0x00;
     PORTB=0x00;
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