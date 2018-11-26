
_main:

;RbotController.c,15 :: 		void main(){
;RbotController.c,16 :: 		setup();
	CALL       _setup+0
;RbotController.c,17 :: 		while(1){
L_main0:
;RbotController.c,18 :: 		servo();
	CALL       _servo+0
;RbotController.c,19 :: 		PORTA = PORTD>>4;
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
;RbotController.c,21 :: 		}
	GOTO       L_main0
;RbotController.c,22 :: 		}
L_end_main:
	GOTO       $+0
; end of _main

_motion:

;RbotController.c,23 :: 		void  motion() {
;RbotController.c,24 :: 		switch (INPUT) {
	GOTO       L_motion2
;RbotController.c,25 :: 		case ((0x00)||(0xA0)||(0x60)||(~0xA0)||(~0x60)):
L_motion4:
;RbotController.c,27 :: 		break;
	GOTO       L_motion3
;RbotController.c,28 :: 		}
L_motion2:
	MOVF       PORTD+0, 0
	XORLW      1
	BTFSC      STATUS+0, 2
	GOTO       L_motion4
L_motion3:
;RbotController.c,29 :: 		}
L_end_motion:
	RETURN
; end of _motion

_setup:

;RbotController.c,30 :: 		void setup(){
;RbotController.c,31 :: 		ANSEL = 0X00;
	CLRF       ANSEL+0
;RbotController.c,32 :: 		TRISA = 0x00;
	CLRF       TRISA+0
;RbotController.c,33 :: 		TRISD = 0XFF;
	MOVLW      255
	MOVWF      TRISD+0
;RbotController.c,34 :: 		TRISB=0x00;
	CLRF       TRISB+0
;RbotController.c,35 :: 		ANSELH=0x00;
	CLRF       ANSELH+0
;RbotController.c,36 :: 		PORTB=0x00;
	CLRF       PORTB+0
;RbotController.c,37 :: 		HBriged = 0x00;
	CLRF       PORTA+0
;RbotController.c,38 :: 		}
L_end_setup:
	RETURN
; end of _setup

_servo:

;RbotController.c,40 :: 		void servo(){
;RbotController.c,41 :: 		gira(pos);
	MOVF       _pos+0, 0
	MOVWF      FARG_gira_grados+0
	MOVF       _pos+1, 0
	MOVWF      FARG_gira_grados+1
	MOVLW      0
	BTFSC      FARG_gira_grados+1, 7
	MOVLW      255
	MOVWF      FARG_gira_grados+2
	MOVWF      FARG_gira_grados+3
	CALL       _gira+0
;RbotController.c,42 :: 		if(CW){
	MOVF       _CW+0, 0
	BTFSC      STATUS+0, 2
	GOTO       L_servo5
;RbotController.c,43 :: 		pos+=5;
	MOVLW      5
	ADDWF      _pos+0, 1
	BTFSC      STATUS+0, 0
	INCF       _pos+1, 1
;RbotController.c,44 :: 		}else {
	GOTO       L_servo6
L_servo5:
;RbotController.c,45 :: 		pos-=5;
	MOVLW      5
	SUBWF      _pos+0, 1
	BTFSS      STATUS+0, 0
	DECF       _pos+1, 1
;RbotController.c,46 :: 		}
L_servo6:
;RbotController.c,47 :: 		if(pos==180){
	MOVLW      0
	XORWF      _pos+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__servo18
	MOVLW      180
	XORWF      _pos+0, 0
L__servo18:
	BTFSS      STATUS+0, 2
	GOTO       L_servo7
;RbotController.c,48 :: 		CW = false;
	CLRF       _CW+0
;RbotController.c,49 :: 		}
L_servo7:
;RbotController.c,50 :: 		if(pos==0){
	MOVLW      0
	XORWF      _pos+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__servo19
	MOVLW      0
	XORWF      _pos+0, 0
L__servo19:
	BTFSS      STATUS+0, 2
	GOTO       L_servo8
;RbotController.c,51 :: 		CW = true;
	MOVLW      1
	MOVWF      _CW+0
;RbotController.c,52 :: 		}
L_servo8:
;RbotController.c,53 :: 		}
L_end_servo:
	RETURN
; end of _servo

_VDelay_us:

;RbotController.c,55 :: 		void VDelay_us(unsigned time_us){
;RbotController.c,56 :: 		time_us/=16;
	RRF        FARG_VDelay_us_time_us+1, 1
	RRF        FARG_VDelay_us_time_us+0, 1
	BCF        FARG_VDelay_us_time_us+1, 7
	RRF        FARG_VDelay_us_time_us+1, 1
	RRF        FARG_VDelay_us_time_us+0, 1
	BCF        FARG_VDelay_us_time_us+1, 7
	RRF        FARG_VDelay_us_time_us+1, 1
	RRF        FARG_VDelay_us_time_us+0, 1
	BCF        FARG_VDelay_us_time_us+1, 7
	RRF        FARG_VDelay_us_time_us+1, 1
	RRF        FARG_VDelay_us_time_us+0, 1
	BCF        FARG_VDelay_us_time_us+1, 7
;RbotController.c,57 :: 		while(time_us--){
L_VDelay_us9:
	MOVF       FARG_VDelay_us_time_us+0, 0
	MOVWF      R0+0
	MOVF       FARG_VDelay_us_time_us+1, 0
	MOVWF      R0+1
	MOVLW      1
	SUBWF      FARG_VDelay_us_time_us+0, 1
	BTFSS      STATUS+0, 0
	DECF       FARG_VDelay_us_time_us+1, 1
	MOVF       R0+0, 0
	IORWF      R0+1, 0
	BTFSC      STATUS+0, 2
	GOTO       L_VDelay_us10
;RbotController.c,58 :: 		asm nop;
	NOP
;RbotController.c,59 :: 		asm nop;
	NOP
;RbotController.c,60 :: 		}
	GOTO       L_VDelay_us9
L_VDelay_us10:
;RbotController.c,61 :: 		}
L_end_VDelay_us:
	RETURN
; end of _VDelay_us

_gira:

;RbotController.c,62 :: 		void gira(unsigned long grados){
;RbotController.c,64 :: 		valor=((grados*1600)/180)+500;
	MOVF       FARG_gira_grados+0, 0
	MOVWF      R0+0
	MOVF       FARG_gira_grados+1, 0
	MOVWF      R0+1
	MOVF       FARG_gira_grados+2, 0
	MOVWF      R0+2
	MOVF       FARG_gira_grados+3, 0
	MOVWF      R0+3
	MOVLW      64
	MOVWF      R4+0
	MOVLW      6
	MOVWF      R4+1
	CLRF       R4+2
	CLRF       R4+3
	CALL       _Mul_32x32_U+0
	MOVLW      180
	MOVWF      R4+0
	CLRF       R4+1
	CLRF       R4+2
	CLRF       R4+3
	CALL       _Div_32x32_U+0
	MOVLW      244
	ADDWF      R0+0, 0
	MOVWF      gira_valor_L0+0
	MOVF       R0+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDLW      1
	MOVWF      gira_valor_L0+1
;RbotController.c,65 :: 		for (i=0;i<=50;i++){
	CLRF       gira_i_L0+0
	CLRF       gira_i_L0+1
L_gira11:
	MOVLW      128
	MOVWF      R0+0
	MOVLW      128
	XORWF      gira_i_L0+1, 0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__gira22
	MOVF       gira_i_L0+0, 0
	SUBLW      50
L__gira22:
	BTFSS      STATUS+0, 0
	GOTO       L_gira12
;RbotController.c,66 :: 		PORTB.F0=1;
	BSF        PORTB+0, 0
;RbotController.c,67 :: 		VDelay_us(valor);
	MOVF       gira_valor_L0+0, 0
	MOVWF      FARG_VDelay_us_time_us+0
	MOVF       gira_valor_L0+1, 0
	MOVWF      FARG_VDelay_us_time_us+1
	CALL       _VDelay_us+0
;RbotController.c,68 :: 		PORTB.F0=0;
	BCF        PORTB+0, 0
;RbotController.c,69 :: 		VDelay_us(5000);
	MOVLW      136
	MOVWF      FARG_VDelay_us_time_us+0
	MOVLW      19
	MOVWF      FARG_VDelay_us_time_us+1
	CALL       _VDelay_us+0
;RbotController.c,65 :: 		for (i=0;i<=50;i++){
	INCF       gira_i_L0+0, 1
	BTFSC      STATUS+0, 2
	INCF       gira_i_L0+1, 1
;RbotController.c,70 :: 		}
	GOTO       L_gira11
L_gira12:
;RbotController.c,71 :: 		}
L_end_gira:
	RETURN
; end of _gira
