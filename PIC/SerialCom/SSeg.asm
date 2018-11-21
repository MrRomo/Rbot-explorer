
_display:

;SSeg.c,10 :: 		void display(int num, char dec[4]) {
;SSeg.c,13 :: 		int div = 1000;
	MOVLW      232
	MOVWF      display_div_L0+0
	MOVLW      3
	MOVWF      display_div_L0+1
;SSeg.c,14 :: 		for (i = 0; i < 4; i++) {
	CLRF       display_i_L0+0
L_display0:
	MOVLW      4
	SUBWF      display_i_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_display1
;SSeg.c,15 :: 		a = num/div;
	MOVF       display_div_L0+0, 0
	MOVWF      R4+0
	MOVF       display_div_L0+1, 0
	MOVWF      R4+1
	MOVF       FARG_display_num+0, 0
	MOVWF      R0+0
	MOVF       FARG_display_num+1, 0
	MOVWF      R0+1
	CALL       _Div_16x16_S+0
	MOVF       R0+0, 0
	MOVWF      FLOC__display+0
	MOVF       R0+1, 0
	MOVWF      FLOC__display+1
	MOVF       FLOC__display+0, 0
	MOVWF      R0+0
	MOVF       FLOC__display+1, 0
	MOVWF      R0+1
	MOVF       display_div_L0+0, 0
	MOVWF      R4+0
	MOVF       display_div_L0+1, 0
	MOVWF      R4+1
	CALL       _Mul_16X16_U+0
;SSeg.c,16 :: 		num = num - (a*div);
	MOVF       R0+0, 0
	SUBWF      FARG_display_num+0, 1
	BTFSS      STATUS+0, 0
	DECF       FARG_display_num+1, 1
	MOVF       R0+1, 0
	SUBWF      FARG_display_num+1, 1
;SSeg.c,17 :: 		div /= 10;
	MOVLW      10
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	MOVF       display_div_L0+0, 0
	MOVWF      R0+0
	MOVF       display_div_L0+1, 0
	MOVWF      R0+1
	CALL       _Div_16x16_S+0
	MOVF       R0+0, 0
	MOVWF      display_div_L0+0
	MOVF       R0+1, 0
	MOVWF      display_div_L0+1
;SSeg.c,18 :: 		disp = seg[a]<<1;
	MOVF       FLOC__display+0, 0
	ADDLW      _seg+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      R2+0
	MOVF       R2+0, 0
	MOVWF      R0+0
	RLF        R0+0, 1
	BCF        R0+0, 0
	MOVF       R0+0, 0
	MOVWF      PORTB+0
;SSeg.c,19 :: 		deco = ~dec[i];
	MOVF       display_i_L0+0, 0
	ADDWF      FARG_display_dec+0, 0
	MOVWF      FSR
	COMF       INDF+0, 0
	MOVWF      PORTD+0
;SSeg.c,20 :: 		DELAY_us(1000);
	MOVLW      3
	MOVWF      R12+0
	MOVLW      151
	MOVWF      R13+0
L_display3:
	DECFSZ     R13+0, 1
	GOTO       L_display3
	DECFSZ     R12+0, 1
	GOTO       L_display3
	NOP
	NOP
;SSeg.c,21 :: 		deco = 0xFF;
	MOVLW      255
	MOVWF      PORTD+0
;SSeg.c,14 :: 		for (i = 0; i < 4; i++) {
	INCF       display_i_L0+0, 1
;SSeg.c,22 :: 		}
	GOTO       L_display0
L_display1:
;SSeg.c,23 :: 		}
L_end_display:
	RETURN
; end of _display
