
_main:

;ServoController.c,4 :: 		void main() {
;ServoController.c,5 :: 		int pos=0;
	CLRF       main_pos_L0+0
	CLRF       main_pos_L0+1
;ServoController.c,6 :: 		setup();
	CALL       _setup+0
;ServoController.c,7 :: 		while(1){
L_main0:
;ServoController.c,22 :: 		for(pos=0;pos<=180;pos=pos+10){
	CLRF       main_pos_L0+0
	CLRF       main_pos_L0+1
L_main2:
	MOVLW      128
	MOVWF      R0+0
	MOVLW      128
	XORWF      main_pos_L0+1, 0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main15
	MOVF       main_pos_L0+0, 0
	SUBLW      180
L__main15:
	BTFSS      STATUS+0, 0
	GOTO       L_main3
;ServoController.c,23 :: 		gira(pos);
	MOVF       main_pos_L0+0, 0
	MOVWF      FARG_gira_grados+0
	MOVF       main_pos_L0+1, 0
	MOVWF      FARG_gira_grados+1
	MOVLW      0
	BTFSC      FARG_gira_grados+1, 7
	MOVLW      255
	MOVWF      FARG_gira_grados+2
	MOVWF      FARG_gira_grados+3
	CALL       _gira+0
;ServoController.c,25 :: 		if(pos==180){
	MOVLW      0
	XORWF      main_pos_L0+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main16
	MOVLW      180
	XORWF      main_pos_L0+0, 0
L__main16:
	BTFSS      STATUS+0, 2
	GOTO       L_main5
;ServoController.c,26 :: 		for(pos=180;pos>=0;pos=pos-10){
	MOVLW      180
	MOVWF      main_pos_L0+0
	CLRF       main_pos_L0+1
L_main6:
	MOVLW      128
	XORWF      main_pos_L0+1, 0
	MOVWF      R0+0
	MOVLW      128
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main17
	MOVLW      0
	SUBWF      main_pos_L0+0, 0
L__main17:
	BTFSS      STATUS+0, 0
	GOTO       L_main7
;ServoController.c,27 :: 		gira(pos);
	MOVF       main_pos_L0+0, 0
	MOVWF      FARG_gira_grados+0
	MOVF       main_pos_L0+1, 0
	MOVWF      FARG_gira_grados+1
	MOVLW      0
	BTFSC      FARG_gira_grados+1, 7
	MOVLW      255
	MOVWF      FARG_gira_grados+2
	MOVWF      FARG_gira_grados+3
	CALL       _gira+0
;ServoController.c,26 :: 		for(pos=180;pos>=0;pos=pos-10){
	MOVLW      10
	SUBWF      main_pos_L0+0, 1
	BTFSS      STATUS+0, 0
	DECF       main_pos_L0+1, 1
;ServoController.c,29 :: 		}
	GOTO       L_main6
L_main7:
;ServoController.c,30 :: 		}
L_main5:
;ServoController.c,22 :: 		for(pos=0;pos<=180;pos=pos+10){
	MOVLW      10
	ADDWF      main_pos_L0+0, 1
	BTFSC      STATUS+0, 0
	INCF       main_pos_L0+1, 1
;ServoController.c,31 :: 		}
	GOTO       L_main2
L_main3:
;ServoController.c,32 :: 		pos=0;
	CLRF       main_pos_L0+0
	CLRF       main_pos_L0+1
;ServoController.c,33 :: 		}
	GOTO       L_main0
;ServoController.c,34 :: 		}
L_end_main:
	GOTO       $+0
; end of _main

_setup:

;ServoController.c,35 :: 		void setup(){
;ServoController.c,36 :: 		TRISB=0x00;
	CLRF       TRISB+0
;ServoController.c,37 :: 		ANSELH=0x00;
	CLRF       ANSELH+0
;ServoController.c,38 :: 		PORTB=0x00;
	CLRF       PORTB+0
;ServoController.c,39 :: 		}
L_end_setup:
	RETURN
; end of _setup

_VDelay_us:

;ServoController.c,40 :: 		void VDelay_us(unsigned time_us){
;ServoController.c,41 :: 		time_us/=16;
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
;ServoController.c,42 :: 		while(time_us--){
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
;ServoController.c,43 :: 		asm nop;
	NOP
;ServoController.c,44 :: 		asm nop;
	NOP
;ServoController.c,45 :: 		}
	GOTO       L_VDelay_us9
L_VDelay_us10:
;ServoController.c,46 :: 		}
L_end_VDelay_us:
	RETURN
; end of _VDelay_us

_gira:

;ServoController.c,47 :: 		void gira(unsigned long grados){
;ServoController.c,49 :: 		valor=((grados*1600)/180)+500;
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
;ServoController.c,50 :: 		for (i=0;i<=50;i++){
	CLRF       gira_i_L0+0
	CLRF       gira_i_L0+1
L_gira11:
	MOVLW      128
	MOVWF      R0+0
	MOVLW      128
	XORWF      gira_i_L0+1, 0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__gira21
	MOVF       gira_i_L0+0, 0
	SUBLW      50
L__gira21:
	BTFSS      STATUS+0, 0
	GOTO       L_gira12
;ServoController.c,51 :: 		PORTB.F0=1;
	BSF        PORTB+0, 0
;ServoController.c,52 :: 		VDelay_us(valor);
	MOVF       gira_valor_L0+0, 0
	MOVWF      FARG_VDelay_us_time_us+0
	MOVF       gira_valor_L0+1, 0
	MOVWF      FARG_VDelay_us_time_us+1
	CALL       _VDelay_us+0
;ServoController.c,53 :: 		PORTB.F0=0;
	BCF        PORTB+0, 0
;ServoController.c,54 :: 		VDelay_us(5000);
	MOVLW      136
	MOVWF      FARG_VDelay_us_time_us+0
	MOVLW      19
	MOVWF      FARG_VDelay_us_time_us+1
	CALL       _VDelay_us+0
;ServoController.c,50 :: 		for (i=0;i<=50;i++){
	INCF       gira_i_L0+0, 1
	BTFSC      STATUS+0, 2
	INCF       gira_i_L0+1, 1
;ServoController.c,55 :: 		}
	GOTO       L_gira11
L_gira12:
;ServoController.c,56 :: 		}
L_end_gira:
	RETURN
; end of _gira
