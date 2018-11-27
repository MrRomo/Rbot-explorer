
_main:

;ParallelCOM2.c,3 :: 		void main(){
;ParallelCOM2.c,4 :: 		TRISB=0x00;
	CLRF       TRISB+0
;ParallelCOM2.c,5 :: 		PORTB=0X00;
	CLRF       PORTB+0
;ParallelCOM2.c,6 :: 		TRISC=0x00;
	CLRF       TRISC+0
;ParallelCOM2.c,7 :: 		PORTC=0X38;
	MOVLW      56
	MOVWF      PORTC+0
;ParallelCOM2.c,8 :: 		delay_ms(100);
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
;ParallelCOM2.c,9 :: 		while(1){
L_main1:
;ParallelCOM2.c,10 :: 		Transmiter = 0xf5;
	MOVLW      245
	MOVWF      PORTB+0
;ParallelCOM2.c,11 :: 		delay_ms(10);
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
;ParallelCOM2.c,12 :: 		Data+= 1;
	INCF       _Data+0, 1
;ParallelCOM2.c,13 :: 		if(Data>=16){
	MOVLW      16
	SUBWF      _Data+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_main4
;ParallelCOM2.c,14 :: 		Data = 0;
	CLRF       _Data+0
;ParallelCOM2.c,15 :: 		}
L_main4:
;ParallelCOM2.c,16 :: 		}
	GOTO       L_main1
;ParallelCOM2.c,17 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
