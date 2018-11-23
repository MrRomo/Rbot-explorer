
_main:

;SerialCom.c,5 :: 		void main() {
;SerialCom.c,6 :: 		setup();
	CALL       _setup+0
;SerialCom.c,7 :: 		UART1_Init(9600);
	MOVLW      51
	MOVWF      SPBRG+0
	BSF        TXSTA+0, 2
	CALL       _UART1_Init+0
;SerialCom.c,8 :: 		Delay_ms(200);                  // Wait for UART module to stabilize
	MOVLW      3
	MOVWF      R11+0
	MOVLW      8
	MOVWF      R12+0
	MOVLW      119
	MOVWF      R13+0
L_main0:
	DECFSZ     R13+0, 1
	GOTO       L_main0
	DECFSZ     R12+0, 1
	GOTO       L_main0
	DECFSZ     R11+0, 1
	GOTO       L_main0
;SerialCom.c,12 :: 		while (1) {
L_main1:
;SerialCom.c,13 :: 		UART1_Write_Text("hola como es estas");
	MOVLW      ?lstr1_SerialCom+0
	MOVWF      FARG_UART1_Write_Text_uart_text+0
	CALL       _UART1_Write_Text+0
;SerialCom.c,14 :: 		IntToStr(a,txt);
	MOVF       _a+0, 0
	MOVWF      FARG_IntToStr_input+0
	MOVF       _a+1, 0
	MOVWF      FARG_IntToStr_input+1
	MOVLW      _txt+0
	MOVWF      FARG_IntToStr_output+0
	CALL       _IntToStr+0
;SerialCom.c,15 :: 		UART1_Write_Text(txt);
	MOVLW      _txt+0
	MOVWF      FARG_UART1_Write_Text_uart_text+0
	CALL       _UART1_Write_Text+0
;SerialCom.c,16 :: 		UART1_Write_Text("\n\r");
	MOVLW      ?lstr2_SerialCom+0
	MOVWF      FARG_UART1_Write_Text_uart_text+0
	CALL       _UART1_Write_Text+0
;SerialCom.c,22 :: 		}
	GOTO       L_main1
;SerialCom.c,23 :: 		}
L_end_main:
	GOTO       $+0
; end of _main

_setup:

;SerialCom.c,25 :: 		void setup () {
;SerialCom.c,26 :: 		ANSEL = 0X00;
	CLRF       ANSEL+0
;SerialCom.c,27 :: 		ANSELH = 0X00;
	CLRF       ANSELH+0
;SerialCom.c,28 :: 		TRISA = 0X00;
	CLRF       TRISA+0
;SerialCom.c,29 :: 		TRISB = 0X50;
	MOVLW      80
	MOVWF      TRISB+0
;SerialCom.c,30 :: 		TRISD = 0X00;
	CLRF       TRISD+0
;SerialCom.c,32 :: 		}
L_end_setup:
	RETURN
; end of _setup
