
_main:

;SerialComMikro.c,3 :: 		void main(){
;SerialComMikro.c,5 :: 		UART1_Init(9600);
	MOVLW      51
	MOVWF      SPBRG+0
	BSF        TXSTA+0, 2
	CALL       _UART1_Init+0
;SerialComMikro.c,7 :: 		ByteToStr(text,txt);
	MOVF       _text+0, 0
	MOVWF      FARG_ByteToStr_input+0
	MOVLW      _txt+0
	MOVWF      FARG_ByteToStr_output+0
	CALL       _ByteToStr+0
;SerialComMikro.c,8 :: 		while(1){
L_main0:
;SerialComMikro.c,10 :: 		UART1_Write_text(text);
	MOVF       _text+0, 0
	MOVWF      FARG_UART1_Write_Text_uart_text+0
	CALL       _UART1_Write_Text+0
;SerialComMikro.c,11 :: 		delay_ms(500);
	MOVLW      6
	MOVWF      R11+0
	MOVLW      19
	MOVWF      R12+0
	MOVLW      173
	MOVWF      R13+0
L_main2:
	DECFSZ     R13+0, 1
	GOTO       L_main2
	DECFSZ     R12+0, 1
	GOTO       L_main2
	DECFSZ     R11+0, 1
	GOTO       L_main2
	NOP
	NOP
;SerialComMikro.c,13 :: 		}
	GOTO       L_main0
;SerialComMikro.c,16 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
