
_main:

;RbotController.c,30 :: 		void main(){
;RbotController.c,31 :: 		setup();
	CALL       _setup+0
;RbotController.c,32 :: 		while(1){
L_main0:
;RbotController.c,33 :: 		servo();
	CALL       _servo+0
;RbotController.c,34 :: 		motion();
	CALL       _motion+0
;RbotController.c,35 :: 		watcher();
	CALL       _watcher+0
;RbotController.c,37 :: 		}
	GOTO       L_main0
;RbotController.c,38 :: 		}
L_end_main:
	GOTO       $+0
; end of _main

_motion:

;RbotController.c,39 :: 		void  motion() {
;RbotController.c,40 :: 		switch (INPUT) {
	MOVF       PORTD+0, 0
	MOVWF      R2+0
	RRF        R2+0, 1
	BCF        R2+0, 7
	RRF        R2+0, 1
	BCF        R2+0, 7
	RRF        R2+0, 1
	BCF        R2+0, 7
	RRF        R2+0, 1
	BCF        R2+0, 7
	GOTO       L_motion2
;RbotController.c,41 :: 		case (Stop||Forward||Backward||Right||Left):
L_motion4:
;RbotController.c,42 :: 		HBriged = INPUT;
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
;RbotController.c,43 :: 		break;
	GOTO       L_motion3
;RbotController.c,44 :: 		}
L_motion2:
	MOVF       R2+0, 0
	XORLW      1
	BTFSC      STATUS+0, 2
	GOTO       L_motion4
L_motion3:
;RbotController.c,45 :: 		}
L_end_motion:
	RETURN
; end of _motion

_setup:

;RbotController.c,46 :: 		void setup(){
;RbotController.c,47 :: 		ANSEL = 0X00;
	CLRF       ANSEL+0
;RbotController.c,48 :: 		ANSELH=0x00;
	CLRF       ANSELH+0
;RbotController.c,49 :: 		TRISA = 0x00;
	CLRF       TRISA+0
;RbotController.c,50 :: 		TRISB=0x00;
	CLRF       TRISB+0
;RbotController.c,51 :: 		TRISD = 0X02;           //RD1 as Input PIN (ECHO)
	MOVLW      2
	MOVWF      TRISD+0
;RbotController.c,52 :: 		HBriged = 0x00;
	CLRF       PORTA+0
;RbotController.c,53 :: 		T1CON = 0x10;                 //Initialize Timer Module
	MOVLW      16
	MOVWF      T1CON+0
;RbotController.c,54 :: 		BUS = 0x69;
	MOVLW      105
	MOVWF      PORTB+0
;RbotController.c,55 :: 		delay_ms(3000);
	MOVLW      31
	MOVWF      R11+0
	MOVLW      113
	MOVWF      R12+0
	MOVLW      30
	MOVWF      R13+0
L_setup5:
	DECFSZ     R13+0, 1
	GOTO       L_setup5
	DECFSZ     R12+0, 1
	GOTO       L_setup5
	DECFSZ     R11+0, 1
	GOTO       L_setup5
	NOP
;RbotController.c,56 :: 		}
L_end_setup:
	RETURN
; end of _setup

_test:

;RbotController.c,58 :: 		void test() {
;RbotController.c,59 :: 		HBriged = 0x0A;
	MOVLW      10
	MOVWF      PORTA+0
;RbotController.c,60 :: 		delay_ms(1000);
	MOVLW      11
	MOVWF      R11+0
	MOVLW      38
	MOVWF      R12+0
	MOVLW      93
	MOVWF      R13+0
L_test6:
	DECFSZ     R13+0, 1
	GOTO       L_test6
	DECFSZ     R12+0, 1
	GOTO       L_test6
	DECFSZ     R11+0, 1
	GOTO       L_test6
	NOP
	NOP
;RbotController.c,61 :: 		HBriged = 0x00;
	CLRF       PORTA+0
;RbotController.c,62 :: 		delay_ms(20);
	MOVLW      52
	MOVWF      R12+0
	MOVLW      241
	MOVWF      R13+0
L_test7:
	DECFSZ     R13+0, 1
	GOTO       L_test7
	DECFSZ     R12+0, 1
	GOTO       L_test7
	NOP
	NOP
;RbotController.c,63 :: 		HBriged = ~0x0A;
	MOVLW      245
	MOVWF      PORTA+0
;RbotController.c,64 :: 		delay_ms(1000);
	MOVLW      11
	MOVWF      R11+0
	MOVLW      38
	MOVWF      R12+0
	MOVLW      93
	MOVWF      R13+0
L_test8:
	DECFSZ     R13+0, 1
	GOTO       L_test8
	DECFSZ     R12+0, 1
	GOTO       L_test8
	DECFSZ     R11+0, 1
	GOTO       L_test8
	NOP
	NOP
;RbotController.c,65 :: 		HBriged = 0x00;
	CLRF       PORTA+0
;RbotController.c,66 :: 		delay_ms(20);
	MOVLW      52
	MOVWF      R12+0
	MOVLW      241
	MOVWF      R13+0
L_test9:
	DECFSZ     R13+0, 1
	GOTO       L_test9
	DECFSZ     R12+0, 1
	GOTO       L_test9
	NOP
	NOP
;RbotController.c,67 :: 		HBriged = 0x06;
	MOVLW      6
	MOVWF      PORTA+0
;RbotController.c,68 :: 		delay_ms(1000);
	MOVLW      11
	MOVWF      R11+0
	MOVLW      38
	MOVWF      R12+0
	MOVLW      93
	MOVWF      R13+0
L_test10:
	DECFSZ     R13+0, 1
	GOTO       L_test10
	DECFSZ     R12+0, 1
	GOTO       L_test10
	DECFSZ     R11+0, 1
	GOTO       L_test10
	NOP
	NOP
;RbotController.c,69 :: 		HBriged = 0x00;
	CLRF       PORTA+0
;RbotController.c,70 :: 		delay_ms(20);
	MOVLW      52
	MOVWF      R12+0
	MOVLW      241
	MOVWF      R13+0
L_test11:
	DECFSZ     R13+0, 1
	GOTO       L_test11
	DECFSZ     R12+0, 1
	GOTO       L_test11
	NOP
	NOP
;RbotController.c,71 :: 		HBriged = ~0x06;
	MOVLW      249
	MOVWF      PORTA+0
;RbotController.c,72 :: 		delay_ms(1000);
	MOVLW      11
	MOVWF      R11+0
	MOVLW      38
	MOVWF      R12+0
	MOVLW      93
	MOVWF      R13+0
L_test12:
	DECFSZ     R13+0, 1
	GOTO       L_test12
	DECFSZ     R12+0, 1
	GOTO       L_test12
	DECFSZ     R11+0, 1
	GOTO       L_test12
	NOP
	NOP
;RbotController.c,73 :: 		HBriged = 0x00;
	CLRF       PORTA+0
;RbotController.c,74 :: 		delay_ms(20);
	MOVLW      52
	MOVWF      R12+0
	MOVLW      241
	MOVWF      R13+0
L_test13:
	DECFSZ     R13+0, 1
	GOTO       L_test13
	DECFSZ     R12+0, 1
	GOTO       L_test13
	NOP
	NOP
;RbotController.c,75 :: 		}
L_end_test:
	RETURN
; end of _test

_servo:

;RbotController.c,76 :: 		void servo(){
;RbotController.c,77 :: 		gira(pos);
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
;RbotController.c,78 :: 		if(CW){
	MOVF       _CW+0, 0
	BTFSC      STATUS+0, 2
	GOTO       L_servo14
;RbotController.c,79 :: 		pos+=5;
	MOVLW      5
	ADDWF      _pos+0, 1
	BTFSC      STATUS+0, 0
	INCF       _pos+1, 1
;RbotController.c,80 :: 		}else {
	GOTO       L_servo15
L_servo14:
;RbotController.c,81 :: 		pos-=5;
	MOVLW      5
	SUBWF      _pos+0, 1
	BTFSS      STATUS+0, 0
	DECF       _pos+1, 1
;RbotController.c,82 :: 		}
L_servo15:
;RbotController.c,83 :: 		if(pos==180){
	MOVLW      0
	XORWF      _pos+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__servo34
	MOVLW      180
	XORWF      _pos+0, 0
L__servo34:
	BTFSS      STATUS+0, 2
	GOTO       L_servo16
;RbotController.c,84 :: 		CW = false;
	CLRF       _CW+0
;RbotController.c,85 :: 		}
L_servo16:
;RbotController.c,86 :: 		if(pos==0){
	MOVLW      0
	XORWF      _pos+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__servo35
	MOVLW      0
	XORWF      _pos+0, 0
L__servo35:
	BTFSS      STATUS+0, 2
	GOTO       L_servo17
;RbotController.c,87 :: 		CW = true;
	MOVLW      1
	MOVWF      _CW+0
;RbotController.c,88 :: 		}
L_servo17:
;RbotController.c,89 :: 		}
L_end_servo:
	RETURN
; end of _servo

_VDelay_us:

;RbotController.c,91 :: 		void VDelay_us(unsigned time_us){
;RbotController.c,92 :: 		time_us/=16;
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
;RbotController.c,93 :: 		while(time_us--){
L_VDelay_us18:
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
	GOTO       L_VDelay_us19
;RbotController.c,94 :: 		asm nop;
	NOP
;RbotController.c,95 :: 		asm nop;
	NOP
;RbotController.c,96 :: 		}
	GOTO       L_VDelay_us18
L_VDelay_us19:
;RbotController.c,97 :: 		}
L_end_VDelay_us:
	RETURN
; end of _VDelay_us

_gira:

;RbotController.c,98 :: 		void gira(unsigned long grados){
;RbotController.c,100 :: 		valor=((grados*1600)/180)+500;
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
;RbotController.c,101 :: 		for (i=0;i<=50;i++){
	CLRF       gira_i_L0+0
	CLRF       gira_i_L0+1
L_gira20:
	MOVLW      128
	MOVWF      R0+0
	MOVLW      128
	XORWF      gira_i_L0+1, 0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__gira38
	MOVF       gira_i_L0+0, 0
	SUBLW      50
L__gira38:
	BTFSS      STATUS+0, 0
	GOTO       L_gira21
;RbotController.c,102 :: 		PORTB.F0=1;
	BSF        PORTB+0, 0
;RbotController.c,103 :: 		VDelay_us(valor);
	MOVF       gira_valor_L0+0, 0
	MOVWF      FARG_VDelay_us_time_us+0
	MOVF       gira_valor_L0+1, 0
	MOVWF      FARG_VDelay_us_time_us+1
	CALL       _VDelay_us+0
;RbotController.c,104 :: 		PORTB.F0=0;
	BCF        PORTB+0, 0
;RbotController.c,105 :: 		VDelay_us(5000);
	MOVLW      136
	MOVWF      FARG_VDelay_us_time_us+0
	MOVLW      19
	MOVWF      FARG_VDelay_us_time_us+1
	CALL       _VDelay_us+0
;RbotController.c,101 :: 		for (i=0;i<=50;i++){
	INCF       gira_i_L0+0, 1
	BTFSC      STATUS+0, 2
	INCF       gira_i_L0+1, 1
;RbotController.c,106 :: 		}
	GOTO       L_gira20
L_gira21:
;RbotController.c,107 :: 		}
L_end_gira:
	RETURN
; end of _gira

_watcher:

;RbotController.c,109 :: 		void watcher(){
;RbotController.c,110 :: 		TMR1H = 0;                  //Sets the Initial Value of Timer
	CLRF       TMR1H+0
;RbotController.c,111 :: 		TMR1L = 0;                  //Sets the Initial Value of Timer
	CLRF       TMR1L+0
;RbotController.c,112 :: 		TRIGGER = 1;               //TRIGGER HIGH
	BSF        PORTD+0, 0
;RbotController.c,113 :: 		Delay_us(10);               //10uS Delay
	MOVLW      6
	MOVWF      R13+0
L_watcher23:
	DECFSZ     R13+0, 1
	GOTO       L_watcher23
	NOP
;RbotController.c,114 :: 		TRIGGER = 0;               //TRIGGER LOW
	BCF        PORTD+0, 0
;RbotController.c,115 :: 		while(!ECCHO);           //Waiting for Echo
L_watcher24:
	BTFSC      PORTD+0, 1
	GOTO       L_watcher25
	GOTO       L_watcher24
L_watcher25:
;RbotController.c,116 :: 		T1CON.F0 = 1;               //Timer Starts
	BSF        T1CON+0, 0
;RbotController.c,117 :: 		while(ECCHO);            //Waiting for Echo goes LOW
L_watcher26:
	BTFSS      PORTD+0, 1
	GOTO       L_watcher27
	GOTO       L_watcher26
L_watcher27:
;RbotController.c,118 :: 		T1CON.F0 = 0;               //Timer Stops
	BCF        T1CON+0, 0
;RbotController.c,119 :: 		a = (TMR1L|(TMR1H<<8));   //Reads Timer Value
	MOVF       TMR1H+0, 0
	MOVWF      R0+1
	CLRF       R0+0
	MOVF       TMR1L+0, 0
	IORWF      R0+0, 1
	MOVLW      0
	IORWF      R0+1, 1
	MOVF       R0+0, 0
	MOVWF      _a+0
	MOVF       R0+1, 0
	MOVWF      _a+1
;RbotController.c,120 :: 		a = a/58.82;                //Converts Time to Distance
	CALL       _word2double+0
	MOVLW      174
	MOVWF      R4+0
	MOVLW      71
	MOVWF      R4+1
	MOVLW      107
	MOVWF      R4+2
	MOVLW      132
	MOVWF      R4+3
	CALL       _Div_32x32_FP+0
	CALL       _double2word+0
	MOVF       R0+0, 0
	MOVWF      _a+0
	MOVF       R0+1, 0
	MOVWF      _a+1
;RbotController.c,121 :: 		a = (a + 1)*2;                  //Distance Calibration
	MOVF       R0+0, 0
	ADDLW      1
	MOVWF      R3+0
	MOVLW      0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 0
	MOVWF      R3+1
	MOVF       R3+0, 0
	MOVWF      R1+0
	MOVF       R3+1, 0
	MOVWF      R1+1
	RLF        R1+0, 1
	RLF        R1+1, 1
	BCF        R1+0, 0
	MOVF       R1+0, 0
	MOVWF      _a+0
	MOVF       R1+1, 0
	MOVWF      _a+1
;RbotController.c,122 :: 		if(a<250){
	MOVLW      0
	SUBWF      R1+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__watcher40
	MOVLW      250
	SUBWF      R1+0, 0
L__watcher40:
	BTFSC      STATUS+0, 0
	GOTO       L_watcher28
;RbotController.c,123 :: 		b = a;
	MOVF       _a+0, 0
	MOVWF      _b+0
;RbotController.c,124 :: 		}
L_watcher28:
;RbotController.c,125 :: 		BUS = b;
	MOVF       _b+0, 0
	MOVWF      PORTB+0
;RbotController.c,126 :: 		}
L_end_watcher:
	RETURN
; end of _watcher
