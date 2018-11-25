
_main:

;SerialComMikro.c,4 :: 		void main(){
;SerialComMikro.c,5 :: 		ANSEL = 0X00;
	CLRF       ANSEL+0
;SerialComMikro.c,6 :: 		TRISA=0x00;
	CLRF       TRISA+0
;SerialComMikro.c,7 :: 		TRISD=0XFF;
	MOVLW      255
	MOVWF      TRISD+0
;SerialComMikro.c,8 :: 		HBriged = 0x00;
	CLRF       PORTA+0
;SerialComMikro.c,9 :: 		while(1){
L_main0:
;SerialComMikro.c,10 :: 		HBriged = PORTD>>4;
	MOVF       PORTD+0, 0
	MOVWF      R0+0
	RRF        R0+0, 1
	BCF        R0+0, 7
	RRF        R0+0, 1
	BCF        R0+0, 7
	RRF        R0+0, 1
	BCF        R0+0, 7
	RRF        R0+0, 1
	BCF        R0+0, 7
	MOVF       R0+0, 0
	MOVWF      PORTA+0
;SerialComMikro.c,11 :: 		}
	GOTO       L_main0
;SerialComMikro.c,13 :: 		}
L_end_main:
	GOTO       $+0
; end of _main

_direction:

;SerialComMikro.c,15 :: 		void direction(){
;SerialComMikro.c,16 :: 		HBriged = 0x00;
	CLRF       PORTA+0
;SerialComMikro.c,17 :: 		delay_ms(2000);
	MOVLW      21
	MOVWF      R11+0
	MOVLW      75
	MOVWF      R12+0
	MOVLW      190
	MOVWF      R13+0
L_direction2:
	DECFSZ     R13+0, 1
	GOTO       L_direction2
	DECFSZ     R12+0, 1
	GOTO       L_direction2
	DECFSZ     R11+0, 1
	GOTO       L_direction2
	NOP
;SerialComMikro.c,18 :: 		HBriged = 0x0A;//derecha
	MOVLW      10
	MOVWF      PORTA+0
;SerialComMikro.c,19 :: 		delay_ms(2000);
	MOVLW      21
	MOVWF      R11+0
	MOVLW      75
	MOVWF      R12+0
	MOVLW      190
	MOVWF      R13+0
L_direction3:
	DECFSZ     R13+0, 1
	GOTO       L_direction3
	DECFSZ     R12+0, 1
	GOTO       L_direction3
	DECFSZ     R11+0, 1
	GOTO       L_direction3
	NOP
;SerialComMikro.c,20 :: 		HBriged = 0x06;//atras
	MOVLW      6
	MOVWF      PORTA+0
;SerialComMikro.c,21 :: 		delay_ms(2000);
	MOVLW      21
	MOVWF      R11+0
	MOVLW      75
	MOVWF      R12+0
	MOVLW      190
	MOVWF      R13+0
L_direction4:
	DECFSZ     R13+0, 1
	GOTO       L_direction4
	DECFSZ     R12+0, 1
	GOTO       L_direction4
	DECFSZ     R11+0, 1
	GOTO       L_direction4
	NOP
;SerialComMikro.c,22 :: 		HBriged = ~0x0A;//Izquierda
	MOVLW      245
	MOVWF      PORTA+0
;SerialComMikro.c,23 :: 		delay_ms(2000);
	MOVLW      21
	MOVWF      R11+0
	MOVLW      75
	MOVWF      R12+0
	MOVLW      190
	MOVWF      R13+0
L_direction5:
	DECFSZ     R13+0, 1
	GOTO       L_direction5
	DECFSZ     R12+0, 1
	GOTO       L_direction5
	DECFSZ     R11+0, 1
	GOTO       L_direction5
	NOP
;SerialComMikro.c,24 :: 		HBriged = ~0x06;//Adelante
	MOVLW      249
	MOVWF      PORTA+0
;SerialComMikro.c,25 :: 		delay_ms(2000);
	MOVLW      21
	MOVWF      R11+0
	MOVLW      75
	MOVWF      R12+0
	MOVLW      190
	MOVWF      R13+0
L_direction6:
	DECFSZ     R13+0, 1
	GOTO       L_direction6
	DECFSZ     R12+0, 1
	GOTO       L_direction6
	DECFSZ     R11+0, 1
	GOTO       L_direction6
	NOP
;SerialComMikro.c,26 :: 		}
L_end_direction:
	RETURN
; end of _direction
