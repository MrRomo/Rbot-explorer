
_main:

;RbotController.c,15 :: 		void main(){
;RbotController.c,17 :: 		ANSEL = 0X00;
	CLRF       ANSEL+0
;RbotController.c,18 :: 		TRISA=0x00;
	CLRF       TRISA+0
;RbotController.c,19 :: 		TRISD=0XFF;
	MOVLW      255
	MOVWF      TRISD+0
;RbotController.c,20 :: 		HBriged = 0x00;
	CLRF       PORTA+0
;RbotController.c,22 :: 		while(1){
L_main0:
;RbotController.c,23 :: 		servo();
	CALL       _servo+0
;RbotController.c,24 :: 		motion();
	CALL       _motion+0
;RbotController.c,25 :: 		}
	GOTO       L_main0
;RbotController.c,26 :: 		}
L_end_main:
	GOTO       $+0
; end of _main

_motion:

;RbotController.c,27 :: 		void  motion() {
;RbotController.c,28 :: 		switch (INPUT) {
	MOVLW      4
	MOVWF      R0+0
	MOVF       PORTD+0, 0
	MOVWF      R2+0
	CLRF       R2+1
	MOVF       R0+0, 0
L__motion19:
	BTFSC      STATUS+0, 2
	GOTO       L__motion20
	RLF        R2+0, 1
	RLF        R2+1, 1
	BCF        R2+0, 0
	ADDLW      255
	GOTO       L__motion19
L__motion20:
	GOTO       L_motion2
;RbotController.c,29 :: 		case (0x00)||(0x0A)||(0x06)||(~0x0A)||(~0x06):
L_motion4:
;RbotController.c,30 :: 		HBriged = INPUT;
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
;RbotController.c,31 :: 		break;
	GOTO       L_motion3
;RbotController.c,32 :: 		case (0x01):
L_motion5:
;RbotController.c,33 :: 		HBriged = INPUT;
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
;RbotController.c,34 :: 		delay_ms(200);
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
;RbotController.c,35 :: 		HBriged = 0x00;
	CLRF       PORTA+0
;RbotController.c,36 :: 		break;
	GOTO       L_motion3
;RbotController.c,37 :: 		}
L_motion2:
	MOVLW      0
	XORWF      R2+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__motion21
	MOVLW      1
	XORWF      R2+0, 0
L__motion21:
	BTFSC      STATUS+0, 2
	GOTO       L_motion4
	MOVLW      0
	XORWF      R2+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__motion22
	MOVLW      1
	XORWF      R2+0, 0
L__motion22:
	BTFSC      STATUS+0, 2
	GOTO       L_motion5
L_motion3:
;RbotController.c,38 :: 		}
L_end_motion:
	RETURN
; end of _motion

_setup:

;RbotController.c,39 :: 		void setup(){
;RbotController.c,40 :: 		ANSEL = 0X00;
	CLRF       ANSEL+0
;RbotController.c,41 :: 		TRISA = 0x00;
	CLRF       TRISA+0
;RbotController.c,42 :: 		TRISD = 0XFF;
	MOVLW      255
	MOVWF      TRISD+0
;RbotController.c,43 :: 		TRISB=0x00;
	CLRF       TRISB+0
;RbotController.c,44 :: 		ANSELH=0x00;
	CLRF       ANSELH+0
;RbotController.c,45 :: 		PORTB=0x00;
	CLRF       PORTB+0
;RbotController.c,46 :: 		}
L_end_setup:
	RETURN
; end of _setup

_servo:

;RbotController.c,48 :: 		void servo(){
;RbotController.c,49 :: 		gira(pos);
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
;RbotController.c,50 :: 		delay_ms(300);
	MOVLW      4
	MOVWF      R11+0
	MOVLW      12
	MOVWF      R12+0
	MOVLW      51
	MOVWF      R13+0
L_servo7:
	DECFSZ     R13+0, 1
	GOTO       L_servo7
	DECFSZ     R12+0, 1
	GOTO       L_servo7
	DECFSZ     R11+0, 1
	GOTO       L_servo7
	NOP
	NOP
;RbotController.c,51 :: 		if(CW){
	MOVF       _CW+0, 0
	BTFSC      STATUS+0, 2
	GOTO       L_servo8
;RbotController.c,52 :: 		pos+=5;
	MOVLW      5
	ADDWF      _pos+0, 1
	BTFSC      STATUS+0, 0
	INCF       _pos+1, 1
;RbotController.c,53 :: 		}else {
	GOTO       L_servo9
L_servo8:
;RbotController.c,54 :: 		pos-=5;
	MOVLW      5
	SUBWF      _pos+0, 1
	BTFSS      STATUS+0, 0
	DECF       _pos+1, 1
;RbotController.c,55 :: 		}
L_servo9:
;RbotController.c,56 :: 		if(pos==180){
	MOVLW      0
	XORWF      _pos+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__servo25
	MOVLW      180
	XORWF      _pos+0, 0
L__servo25:
	BTFSS      STATUS+0, 2
	GOTO       L_servo10
;RbotController.c,57 :: 		CW = false;
	CLRF       _CW+0
;RbotController.c,58 :: 		}
L_servo10:
;RbotController.c,59 :: 		if(pos==0){
	MOVLW      0
	XORWF      _pos+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__servo26
	MOVLW      0
	XORWF      _pos+0, 0
L__servo26:
	BTFSS      STATUS+0, 2
	GOTO       L_servo11
;RbotController.c,60 :: 		CW = true;
	MOVLW      1
	MOVWF      _CW+0
;RbotController.c,61 :: 		}
L_servo11:
;RbotController.c,62 :: 		}
L_end_servo:
	RETURN
; end of _servo

_VDelay_us:

;RbotController.c,64 :: 		void VDelay_us(unsigned time_us){
;RbotController.c,65 :: 		time_us/=16;
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
;RbotController.c,66 :: 		while(time_us--){
L_VDelay_us12:
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
	GOTO       L_VDelay_us13
;RbotController.c,67 :: 		asm nop;
	NOP
;RbotController.c,68 :: 		asm nop;
	NOP
;RbotController.c,69 :: 		}
	GOTO       L_VDelay_us12
L_VDelay_us13:
;RbotController.c,70 :: 		}
L_end_VDelay_us:
	RETURN
; end of _VDelay_us

_gira:

;RbotController.c,71 :: 		void gira(unsigned long grados){
;RbotController.c,73 :: 		valor=((grados*1600)/180)+500;
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
;RbotController.c,74 :: 		for (i=0;i<=50;i++){
	CLRF       gira_i_L0+0
	CLRF       gira_i_L0+1
L_gira14:
	MOVLW      128
	MOVWF      R0+0
	MOVLW      128
	XORWF      gira_i_L0+1, 0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__gira29
	MOVF       gira_i_L0+0, 0
	SUBLW      50
L__gira29:
	BTFSS      STATUS+0, 0
	GOTO       L_gira15
;RbotController.c,75 :: 		PORTB.F0=1;
	BSF        PORTB+0, 0
;RbotController.c,76 :: 		VDelay_us(valor);
	MOVF       gira_valor_L0+0, 0
	MOVWF      FARG_VDelay_us_time_us+0
	MOVF       gira_valor_L0+1, 0
	MOVWF      FARG_VDelay_us_time_us+1
	CALL       _VDelay_us+0
;RbotController.c,77 :: 		PORTB.F0=0;
	BCF        PORTB+0, 0
;RbotController.c,78 :: 		VDelay_us(19000);
	MOVLW      56
	MOVWF      FARG_VDelay_us_time_us+0
	MOVLW      74
	MOVWF      FARG_VDelay_us_time_us+1
	CALL       _VDelay_us+0
;RbotController.c,74 :: 		for (i=0;i<=50;i++){
	INCF       gira_i_L0+0, 1
	BTFSC      STATUS+0, 2
	INCF       gira_i_L0+1, 1
;RbotController.c,79 :: 		}
	GOTO       L_gira14
L_gira15:
;RbotController.c,80 :: 		}
L_end_gira:
	RETURN
; end of _gira
