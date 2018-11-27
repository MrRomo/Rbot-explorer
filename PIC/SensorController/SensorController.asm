
_main:

;SensorController.c,3 :: 		void main()
;SensorController.c,7 :: 		ANSEL = 0x00;
	CLRF       ANSEL+0
;SensorController.c,8 :: 		ANSELH = 0x00;
	CLRF       ANSELH+0
;SensorController.c,9 :: 		TRISB = 0X00;
	CLRF       TRISB+0
;SensorController.c,10 :: 		PORTB = 0X00;
	CLRF       PORTB+0
;SensorController.c,11 :: 		TRISD = 0X02;           //RD1 as Input PIN (ECHO)
	MOVLW      2
	MOVWF      TRISD+0
;SensorController.c,12 :: 		PORTD = 0X00;
	CLRF       PORTD+0
;SensorController.c,13 :: 		Delay_ms(3000);
	MOVLW      31
	MOVWF      R11+0
	MOVLW      113
	MOVWF      R12+0
	MOVLW      30
	MOVWF      R13+0
L_main0:
	DECFSZ     R13+0, 1
	GOTO       L_main0
	DECFSZ     R12+0, 1
	GOTO       L_main0
	DECFSZ     R11+0, 1
	GOTO       L_main0
	NOP
;SensorController.c,14 :: 		T1CON = 0x10;                 //Initialize Timer Module
	MOVLW      16
	MOVWF      T1CON+0
;SensorController.c,15 :: 		PORTB = 0x69;
	MOVLW      105
	MOVWF      PORTB+0
;SensorController.c,16 :: 		delay_ms(3000);
	MOVLW      31
	MOVWF      R11+0
	MOVLW      113
	MOVWF      R12+0
	MOVLW      30
	MOVWF      R13+0
L_main1:
	DECFSZ     R13+0, 1
	GOTO       L_main1
	DECFSZ     R12+0, 1
	GOTO       L_main1
	DECFSZ     R11+0, 1
	GOTO       L_main1
	NOP
;SensorController.c,18 :: 		while(1)
L_main2:
;SensorController.c,20 :: 		TMR1H = 0;                  //Sets the Initial Value of Timer
	CLRF       TMR1H+0
;SensorController.c,21 :: 		TMR1L = 0;                  //Sets the Initial Value of Timer
	CLRF       TMR1L+0
;SensorController.c,22 :: 		TRIGGER = 1;               //TRIGGER HIGH
	BSF        PORTD+0, 0
;SensorController.c,23 :: 		Delay_us(10);               //10uS Delay
	MOVLW      6
	MOVWF      R13+0
L_main4:
	DECFSZ     R13+0, 1
	GOTO       L_main4
	NOP
;SensorController.c,24 :: 		TRIGGER = 0;               //TRIGGER LOW
	BCF        PORTD+0, 0
;SensorController.c,25 :: 		while(!ECCHO);           //Waiting for Echo
L_main5:
	BTFSC      PORTD+0, 1
	GOTO       L_main6
	GOTO       L_main5
L_main6:
;SensorController.c,26 :: 		T1CON.F0 = 1;               //Timer Starts
	BSF        T1CON+0, 0
;SensorController.c,27 :: 		while(ECCHO);            //Waiting for Echo goes LOW
L_main7:
	BTFSS      PORTD+0, 1
	GOTO       L_main8
	GOTO       L_main7
L_main8:
;SensorController.c,28 :: 		T1CON.F0 = 0;               //Timer Stops
	BCF        T1CON+0, 0
;SensorController.c,29 :: 		a = (TMR1L|(TMR1H<<8));   //Reads Timer Value
	MOVF       TMR1H+0, 0
	MOVWF      R0+1
	CLRF       R0+0
	MOVF       TMR1L+0, 0
	IORWF      R0+0, 1
	MOVLW      0
	IORWF      R0+1, 1
	MOVF       R0+0, 0
	MOVWF      main_a_L0+0
	MOVF       R0+1, 0
	MOVWF      main_a_L0+1
;SensorController.c,30 :: 		a = a/58.82;                //Converts Time to Distance
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
	MOVWF      main_a_L0+0
	MOVF       R0+1, 0
	MOVWF      main_a_L0+1
;SensorController.c,31 :: 		a = (a + 1)*2;                  //Distance Calibration
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
	MOVWF      main_a_L0+0
	MOVF       R1+1, 0
	MOVWF      main_a_L0+1
;SensorController.c,32 :: 		if(a<250){
	MOVLW      0
	SUBWF      R1+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main11
	MOVLW      250
	SUBWF      R1+0, 0
L__main11:
	BTFSC      STATUS+0, 0
	GOTO       L_main9
;SensorController.c,33 :: 		b = a;
	MOVF       main_a_L0+0, 0
	MOVWF      main_b_L0+0
;SensorController.c,34 :: 		}
L_main9:
;SensorController.c,35 :: 		PORTB = b;
	MOVF       main_b_L0+0, 0
	MOVWF      PORTB+0
;SensorController.c,36 :: 		}
	GOTO       L_main2
;SensorController.c,37 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
