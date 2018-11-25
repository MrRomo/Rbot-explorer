
_main:

;SerialComMikro.c,3 :: 		void main(){
;SerialComMikro.c,4 :: 		UART1_Init(9600);
	MOVLW      51
	MOVWF      SPBRG+0
	BSF        TXSTA+0, 2
	CALL       _UART1_Init+0
;SerialComMikro.c,6 :: 		TRISB=0x00;
	CLRF       TRISB+0
;SerialComMikro.c,7 :: 		PORTB=0X00;
	CLRF       PORTB+0
;SerialComMikro.c,8 :: 		delay_ms(100);
	MOVLW      2
	MOVWF      R11+0
	MOVLW      4
	MOVWF      R12+0
	MOVLW      186
	MOVWF      R13+0
L_main0:
	DECFSZ     R13+0, 1
	GOTO       L_main0
	DECFSZ     R12+0, 1
	GOTO       L_main0
	DECFSZ     R11+0, 1
	GOTO       L_main0
	NOP
;SerialComMikro.c,10 :: 		while(1){
L_main1:
;SerialComMikro.c,11 :: 		Transmiter = Data;
	MOVF       _Data+0, 0
	MOVWF      PORTB+0
;SerialComMikro.c,12 :: 		delay_ms(10);
	MOVLW      26
	MOVWF      R12+0
	MOVLW      248
	MOVWF      R13+0
L_main3:
	DECFSZ     R13+0, 1
	GOTO       L_main3
	DECFSZ     R12+0, 1
	GOTO       L_main3
	NOP
;SerialComMikro.c,13 :: 		Data+= 1;
	INCF       _Data+0, 1
;SerialComMikro.c,14 :: 		if(Data>=16){
	MOVLW      16
	SUBWF      _Data+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_main4
;SerialComMikro.c,15 :: 		Data = 0;
	CLRF       _Data+0
;SerialComMikro.c,16 :: 		}
L_main4:
;SerialComMikro.c,17 :: 		}
	GOTO       L_main1
;SerialComMikro.c,18 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
