
_main:

;SensorController.c,2 :: 		void main()
;SensorController.c,9 :: 		ANSEL = 0x00;
	CLRF       ANSEL+0
;SensorController.c,10 :: 		ANSELH = 0x00;
	CLRF       ANSELH+0
;SensorController.c,11 :: 		TRISA = 0X00;
	CLRF       TRISA+0
;SensorController.c,12 :: 		PORTA = 0X00;
	CLRF       PORTA+0
;SensorController.c,13 :: 		PORTB = 0X00;
	CLRF       PORTB+0
;SensorController.c,14 :: 		TRISB = 0X10;           //RB4 as Input PIN (ECHO)
	MOVLW      16
	MOVWF      TRISB+0
;SensorController.c,17 :: 		Delay_ms(3000);
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
;SensorController.c,19 :: 		T1CON = 0x10;                 //Initialize Timer Module
	MOVLW      16
	MOVWF      T1CON+0
;SensorController.c,21 :: 		while(1)
L_main1:
;SensorController.c,23 :: 		TMR1H = 0;                  //Sets the Initial Value of Timer
	CLRF       TMR1H+0
;SensorController.c,24 :: 		TMR1L = 0;                  //Sets the Initial Value of Timer
	CLRF       TMR1L+0
;SensorController.c,25 :: 		PORTB.F0 = 1;               //TRIGGER HIGH
	BSF        PORTB+0, 0
;SensorController.c,26 :: 		Delay_us(10);               //10uS Delay
	MOVLW      6
	MOVWF      R13+0
L_main3:
	DECFSZ     R13+0, 1
	GOTO       L_main3
	NOP
;SensorController.c,27 :: 		PORTB.F0 = 0;               //TRIGGER LOW
	BCF        PORTB+0, 0
;SensorController.c,28 :: 		while(!PORTB.F4);           //Waiting for Echo
L_main4:
	BTFSC      PORTB+0, 4
	GOTO       L_main5
	GOTO       L_main4
L_main5:
;SensorController.c,29 :: 		T1CON.F0 = 1;               //Timer Starts
	BSF        T1CON+0, 0
;SensorController.c,30 :: 		while(PORTB.F4);            //Waiting for Echo goes LOW
L_main6:
	BTFSS      PORTB+0, 4
	GOTO       L_main7
	GOTO       L_main6
L_main7:
;SensorController.c,31 :: 		T1CON.F0 = 0;               //Timer Stops
	BCF        T1CON+0, 0
;SensorController.c,32 :: 		a = (TMR1L | (TMR1H<<8));   //Reads Timer Value
	MOVF       TMR1H+0, 0
	MOVWF      R0+1
	CLRF       R0+0
	MOVF       TMR1L+0, 0
	IORWF      R0+0, 1
	MOVLW      0
	IORWF      R0+1, 1
;SensorController.c,33 :: 		a = a/58.82;                //Converts Time to Distance
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
;SensorController.c,34 :: 		a = (a + 1)*2;                  //Distance Calibration
	MOVF       R0+0, 0
	ADDLW      1
	MOVWF      R3+0
	MOVLW      0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 0
	MOVWF      R3+1
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R3+1, 0
	MOVWF      R0+1
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
;SensorController.c,35 :: 		PORTA = a;
	MOVF       R0+0, 0
	MOVWF      PORTA+0
;SensorController.c,36 :: 		}
	GOTO       L_main1
;SensorController.c,37 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
