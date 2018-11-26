
_main:

;RbotController.c,8 :: 		void main(){
;RbotController.c,9 :: 		ANSEL = 0X00;
	CLRF       ANSEL+0
;RbotController.c,10 :: 		TRISA=0x00;
	CLRF       TRISA+0
;RbotController.c,11 :: 		TRISD=0XFF;
	MOVLW      255
	MOVWF      TRISD+0
;RbotController.c,12 :: 		HBriged = 0x00;
	CLRF       PORTA+0
;RbotController.c,13 :: 		while(1){
L_main0:
;RbotController.c,15 :: 		motion();
	CALL       _motion+0
;RbotController.c,17 :: 		}
	GOTO       L_main0
;RbotController.c,18 :: 		}
L_end_main:
	GOTO       $+0
; end of _main

_motion:

;RbotController.c,19 :: 		void  motion() {
;RbotController.c,20 :: 		switch (INPUT) {
	MOVLW      4
	MOVWF      R0+0
	MOVF       PORTD+0, 0
	MOVWF      R2+0
	CLRF       R2+1
	MOVF       R0+0, 0
L__motion9:
	BTFSC      STATUS+0, 2
	GOTO       L__motion10
	RLF        R2+0, 1
	RLF        R2+1, 1
	BCF        R2+0, 0
	ADDLW      255
	GOTO       L__motion9
L__motion10:
	GOTO       L_motion2
;RbotController.c,21 :: 		case (0x00)||(0x0A)||(0x06)||(~0x0A)||(~0x06):
L_motion4:
;RbotController.c,22 :: 		HBriged = INPUT;
	MOVF       PORTD+0, 0
	MOVWF      R0+0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	MOVF       R0+0, 0
	MOVWF      PORTA+0
;RbotController.c,23 :: 		break;
	GOTO       L_motion3
;RbotController.c,24 :: 		case (0x01):
L_motion5:
;RbotController.c,25 :: 		HBriged = INPUT;
	MOVF       PORTD+0, 0
	MOVWF      R0+0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	MOVF       R0+0, 0
	MOVWF      PORTA+0
;RbotController.c,26 :: 		delay_ms(200);
	MOVLW      3
	MOVWF      R11+0
	MOVLW      8
	MOVWF      R12+0
	MOVLW      119
	MOVWF      R13+0
L_motion6:
	DECFSZ     R13+0, 1
	GOTO       L_motion6
	DECFSZ     R12+0, 1
	GOTO       L_motion6
	DECFSZ     R11+0, 1
	GOTO       L_motion6
;RbotController.c,27 :: 		HBriged = 0x00;
	CLRF       PORTA+0
;RbotController.c,28 :: 		break;
	GOTO       L_motion3
;RbotController.c,29 :: 		}
L_motion2:
	MOVLW      0
	XORWF      R2+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__motion11
	MOVLW      1
	XORWF      R2+0, 0
L__motion11:
	BTFSC      STATUS+0, 2
	GOTO       L_motion4
	MOVLW      0
	XORWF      R2+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__motion12
	MOVLW      1
	XORWF      R2+0, 0
L__motion12:
	BTFSC      STATUS+0, 2
	GOTO       L_motion5
L_motion3:
;RbotController.c,30 :: 		}
L_end_motion:
	RETURN
; end of _motion

_setup:

;RbotController.c,31 :: 		void setup(){
;RbotController.c,32 :: 		ANSEL = 0X00;
	CLRF       ANSEL+0
;RbotController.c,33 :: 		TRISA = 0x00;
	CLRF       TRISA+0
;RbotController.c,34 :: 		TRISD = 0XFF;
	MOVLW      255
	MOVWF      TRISD+0
;RbotController.c,35 :: 		}
L_end_setup:
	RETURN
; end of _setup
