
_main:

;RbotController.c,15 :: 		void main(){
;RbotController.c,16 :: 		setup();
	CALL       _setup+0
;RbotController.c,17 :: 		while(1){
L_main0:
;RbotController.c,18 :: 		servo();
	CALL       _servo+0
;RbotController.c,20 :: 		PORTA = 0x0A;
	MOVLW      10
	MOVWF      PORTA+0
;RbotController.c,21 :: 		delay_ms(1000);
	MOVLW      11
	MOVWF      R11+0
	MOVLW      38
	MOVWF      R12+0
	MOVLW      93
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
;RbotController.c,22 :: 		PORTA = 0x00;
	CLRF       PORTA+0
;RbotController.c,23 :: 		delay_ms(20);
	MOVLW      52
	MOVWF      R12+0
	MOVLW      241
	MOVWF      R13+0
L_main3:
	DECFSZ     R13+0, 1
	GOTO       L_main3
	DECFSZ     R12+0, 1
	GOTO       L_main3
	NOP
	NOP
;RbotController.c,24 :: 		PORTA = ~0x0A;
	MOVLW      245
	MOVWF      PORTA+0
;RbotController.c,25 :: 		delay_ms(1000);
	MOVLW      11
	MOVWF      R11+0
	MOVLW      38
	MOVWF      R12+0
	MOVLW      93
	MOVWF      R13+0
L_main4:
	DECFSZ     R13+0, 1
	GOTO       L_main4
	DECFSZ     R12+0, 1
	GOTO       L_main4
	DECFSZ     R11+0, 1
	GOTO       L_main4
	NOP
	NOP
;RbotController.c,26 :: 		PORTA = 0x00;
	CLRF       PORTA+0
;RbotController.c,27 :: 		delay_ms(20);
	MOVLW      52
	MOVWF      R12+0
	MOVLW      241
	MOVWF      R13+0
L_main5:
	DECFSZ     R13+0, 1
	GOTO       L_main5
	DECFSZ     R12+0, 1
	GOTO       L_main5
	NOP
	NOP
;RbotController.c,28 :: 		PORTA = 0x06;
	MOVLW      6
	MOVWF      PORTA+0
;RbotController.c,29 :: 		delay_ms(1000);
	MOVLW      11
	MOVWF      R11+0
	MOVLW      38
	MOVWF      R12+0
	MOVLW      93
	MOVWF      R13+0
L_main6:
	DECFSZ     R13+0, 1
	GOTO       L_main6
	DECFSZ     R12+0, 1
	GOTO       L_main6
	DECFSZ     R11+0, 1
	GOTO       L_main6
	NOP
	NOP
;RbotController.c,30 :: 		PORTA = 0x00;
	CLRF       PORTA+0
;RbotController.c,31 :: 		delay_ms(20);
	MOVLW      52
	MOVWF      R12+0
	MOVLW      241
	MOVWF      R13+0
L_main7:
	DECFSZ     R13+0, 1
	GOTO       L_main7
	DECFSZ     R12+0, 1
	GOTO       L_main7
	NOP
	NOP
;RbotController.c,32 :: 		PORTA = ~0x06;
	MOVLW      249
	MOVWF      PORTA+0
;RbotController.c,33 :: 		delay_ms(1000);
	MOVLW      11
	MOVWF      R11+0
	MOVLW      38
	MOVWF      R12+0
	MOVLW      93
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
;RbotController.c,34 :: 		PORTA = 0x00;
	CLRF       PORTA+0
;RbotController.c,35 :: 		delay_ms(20);
	MOVLW      52
	MOVWF      R12+0
	MOVLW      241
	MOVWF      R13+0
L_main9:
	DECFSZ     R13+0, 1
	GOTO       L_main9
	DECFSZ     R12+0, 1
	GOTO       L_main9
	NOP
	NOP
;RbotController.c,36 :: 		}
	GOTO       L_main0
;RbotController.c,37 :: 		}
L_end_main:
	GOTO       $+0
; end of _main

_motion:

;RbotController.c,38 :: 		void  motion() {
;RbotController.c,39 :: 		switch (INPUT) {
	GOTO       L_motion10
;RbotController.c,40 :: 		case ((0x00)||(0xA0)||(0x60)||(~0xA0)||(~0x60)):
L_motion12:
;RbotController.c,42 :: 		break;
	GOTO       L_motion11
;RbotController.c,43 :: 		}
L_motion10:
	MOVF       PORTD+0, 0
	XORLW      1
	BTFSC      STATUS+0, 2
	GOTO       L_motion12
L_motion11:
;RbotController.c,44 :: 		}
L_end_motion:
	RETURN
; end of _motion

_setup:

;RbotController.c,45 :: 		void setup(){
;RbotController.c,46 :: 		ANSEL = 0X00;
	CLRF       ANSEL+0
;RbotController.c,47 :: 		TRISA = 0x00;
	CLRF       TRISA+0
;RbotController.c,48 :: 		TRISD = 0XFF;
	MOVLW      255
	MOVWF      TRISD+0
;RbotController.c,49 :: 		TRISB=0x00;
	CLRF       TRISB+0
;RbotController.c,50 :: 		ANSELH=0x00;
	CLRF       ANSELH+0
;RbotController.c,51 :: 		PORTB=0x00;
	CLRF       PORTB+0
;RbotController.c,52 :: 		HBriged = 0x00;
	CLRF       PORTA+0
;RbotController.c,53 :: 		}
L_end_setup:
	RETURN
; end of _setup

_servo:

;RbotController.c,55 :: 		void servo(){
;RbotController.c,56 :: 		gira(pos);
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
;RbotController.c,57 :: 		if(CW){
	MOVF       _CW+0, 0
	BTFSC      STATUS+0, 2
	GOTO       L_servo13
;RbotController.c,58 :: 		pos+=5;
	MOVLW      5
	ADDWF      _pos+0, 1
	BTFSC      STATUS+0, 0
	INCF       _pos+1, 1
;RbotController.c,59 :: 		}else {
	GOTO       L_servo14
L_servo13:
;RbotController.c,60 :: 		pos-=5;
	MOVLW      5
	SUBWF      _pos+0, 1
	BTFSS      STATUS+0, 0
	DECF       _pos+1, 1
;RbotController.c,61 :: 		}
L_servo14:
;RbotController.c,62 :: 		if(pos==180){
	MOVLW      0
	XORWF      _pos+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__servo26
	MOVLW      180
	XORWF      _pos+0, 0
L__servo26:
	BTFSS      STATUS+0, 2
	GOTO       L_servo15
;RbotController.c,63 :: 		CW = false;
	CLRF       _CW+0
;RbotController.c,64 :: 		}
L_servo15:
;RbotController.c,65 :: 		if(pos==0){
	MOVLW      0
	XORWF      _pos+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__servo27
	MOVLW      0
	XORWF      _pos+0, 0
L__servo27:
	BTFSS      STATUS+0, 2
	GOTO       L_servo16
;RbotController.c,66 :: 		CW = true;
	MOVLW      1
	MOVWF      _CW+0
;RbotController.c,67 :: 		}
L_servo16:
;RbotController.c,68 :: 		}
L_end_servo:
	RETURN
; end of _servo

_VDelay_us:

;RbotController.c,70 :: 		void VDelay_us(unsigned time_us){
;RbotController.c,71 :: 		time_us/=16;
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
;RbotController.c,72 :: 		while(time_us--){
L_VDelay_us17:
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
	GOTO       L_VDelay_us18
;RbotController.c,73 :: 		asm nop;
	NOP
;RbotController.c,74 :: 		asm nop;
	NOP
;RbotController.c,75 :: 		}
	GOTO       L_VDelay_us17
L_VDelay_us18:
;RbotController.c,76 :: 		}
L_end_VDelay_us:
	RETURN
; end of _VDelay_us

_gira:

;RbotController.c,77 :: 		void gira(unsigned long grados){
;RbotController.c,79 :: 		valor=((grados*1600)/180)+500;
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
;RbotController.c,80 :: 		for (i=0;i<=50;i++){
	CLRF       gira_i_L0+0
	CLRF       gira_i_L0+1
L_gira19:
	MOVLW      128
	MOVWF      R0+0
	MOVLW      128
	XORWF      gira_i_L0+1, 0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__gira30
	MOVF       gira_i_L0+0, 0
	SUBLW      50
L__gira30:
	BTFSS      STATUS+0, 0
	GOTO       L_gira20
;RbotController.c,81 :: 		PORTB.F0=1;
	BSF        PORTB+0, 0
;RbotController.c,82 :: 		VDelay_us(valor);
	MOVF       gira_valor_L0+0, 0
	MOVWF      FARG_VDelay_us_time_us+0
	MOVF       gira_valor_L0+1, 0
	MOVWF      FARG_VDelay_us_time_us+1
	CALL       _VDelay_us+0
;RbotController.c,83 :: 		PORTB.F0=0;
	BCF        PORTB+0, 0
;RbotController.c,84 :: 		VDelay_us(5000);
	MOVLW      136
	MOVWF      FARG_VDelay_us_time_us+0
	MOVLW      19
	MOVWF      FARG_VDelay_us_time_us+1
	CALL       _VDelay_us+0
;RbotController.c,80 :: 		for (i=0;i<=50;i++){
	INCF       gira_i_L0+0, 1
	BTFSC      STATUS+0, 2
	INCF       gira_i_L0+1, 1
;RbotController.c,85 :: 		}
	GOTO       L_gira19
L_gira20:
;RbotController.c,86 :: 		}
L_end_gira:
	RETURN
; end of _gira
