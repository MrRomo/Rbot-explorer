
_main:

;SerialCom.c,3 :: 		void main() {
;SerialCom.c,4 :: 		UART1_Init(9600);
	MOVLW      51
	MOVWF      SPBRG+0
	BSF        TXSTA+0, 2
	CALL       _UART1_Init+0
;SerialCom.c,5 :: 		setup();
	CALL       _setup+0
;SerialCom.c,6 :: 		while (1) {
L_main0:
;SerialCom.c,7 :: 		UART1_Write(2);
	MOVLW      2
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;SerialCom.c,8 :: 		if(PORTB.f6){
	BTFSS      PORTB+0, 6
	GOTO       L_main2
;SerialCom.c,9 :: 		while(PORTB.f6);
L_main3:
	BTFSS      PORTB+0, 6
	GOTO       L_main4
	GOTO       L_main3
L_main4:
;SerialCom.c,10 :: 		UART1_write(1);
	MOVLW      1
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;SerialCom.c,11 :: 		}
L_main2:
;SerialCom.c,12 :: 		if (UART1_Data_Ready() == 1) {
	CALL       _UART1_Data_Ready+0
	MOVF       R0+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_main5
;SerialCom.c,13 :: 		char receive = UART1_Read();
	CALL       _UART1_Read+0
	MOVF       R0+0, 0
	MOVWF      main_receive_L2+0
;SerialCom.c,14 :: 		UART1_write(receive);
	MOVF       R0+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;SerialCom.c,15 :: 		if(receive>1){
	MOVF       main_receive_L2+0, 0
	SUBLW      1
	BTFSC      STATUS+0, 0
	GOTO       L_main6
;SerialCom.c,16 :: 		PORTD.f2 = 1;
	BSF        PORTD+0, 2
;SerialCom.c,17 :: 		DELAY_MS(500);
	MOVLW      6
	MOVWF      R11+0
	MOVLW      19
	MOVWF      R12+0
	MOVLW      173
	MOVWF      R13+0
L_main7:
	DECFSZ     R13+0, 1
	GOTO       L_main7
	DECFSZ     R12+0, 1
	GOTO       L_main7
	DECFSZ     R11+0, 1
	GOTO       L_main7
	NOP
	NOP
;SerialCom.c,18 :: 		PORTD.f2 = 0;
	BCF        PORTD+0, 2
;SerialCom.c,19 :: 		DELAY_MS(500);
	MOVLW      6
	MOVWF      R11+0
	MOVLW      19
	MOVWF      R12+0
	MOVLW      173
	MOVWF      R13+0
L_main8:
	DECFSZ     R13+0, 1
	GOTO       L_main8
	DECFSZ     R12+0, 1
	GOTO       L_main8
	DECFSZ     R11+0, 1
	GOTO       L_main8
	NOP
	NOP
;SerialCom.c,20 :: 		}
L_main6:
;SerialCom.c,21 :: 		}
L_main5:
;SerialCom.c,22 :: 		}
	GOTO       L_main0
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
;SerialCom.c,31 :: 		}
L_end_setup:
	RETURN
; end of _setup
