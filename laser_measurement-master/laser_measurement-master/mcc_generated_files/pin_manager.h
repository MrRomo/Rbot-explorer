/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.35
        Device            :  PIC18LF24K40
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set LED_7 aliases
#define LED_7_TRIS               TRISAbits.TRISA3
#define LED_7_LAT                LATAbits.LATA3
#define LED_7_PORT               PORTAbits.RA3
#define LED_7_WPU                WPUAbits.WPUA3
#define LED_7_OD                ODCONAbits.ODCA3
#define LED_7_ANS                ANSELAbits.ANSELA3
#define LED_7_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define LED_7_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define LED_7_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define LED_7_GetValue()           PORTAbits.RA3
#define LED_7_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define LED_7_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define LED_7_SetPullup()      do { WPUAbits.WPUA3 = 1; } while(0)
#define LED_7_ResetPullup()    do { WPUAbits.WPUA3 = 0; } while(0)
#define LED_7_SetPushPull()    do { ODCONAbits.ODCA3 = 0; } while(0)
#define LED_7_SetOpenDrain()   do { ODCONAbits.ODCA3 = 1; } while(0)
#define LED_7_SetAnalogMode()  do { ANSELAbits.ANSELA3 = 1; } while(0)
#define LED_7_SetDigitalMode() do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set LED_6 aliases
#define LED_6_TRIS               TRISAbits.TRISA4
#define LED_6_LAT                LATAbits.LATA4
#define LED_6_PORT               PORTAbits.RA4
#define LED_6_WPU                WPUAbits.WPUA4
#define LED_6_OD                ODCONAbits.ODCA4
#define LED_6_ANS                ANSELAbits.ANSELA4
#define LED_6_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define LED_6_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define LED_6_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define LED_6_GetValue()           PORTAbits.RA4
#define LED_6_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define LED_6_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define LED_6_SetPullup()      do { WPUAbits.WPUA4 = 1; } while(0)
#define LED_6_ResetPullup()    do { WPUAbits.WPUA4 = 0; } while(0)
#define LED_6_SetPushPull()    do { ODCONAbits.ODCA4 = 0; } while(0)
#define LED_6_SetOpenDrain()   do { ODCONAbits.ODCA4 = 1; } while(0)
#define LED_6_SetAnalogMode()  do { ANSELAbits.ANSELA4 = 1; } while(0)
#define LED_6_SetDigitalMode() do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set LED_5 aliases
#define LED_5_TRIS               TRISAbits.TRISA5
#define LED_5_LAT                LATAbits.LATA5
#define LED_5_PORT               PORTAbits.RA5
#define LED_5_WPU                WPUAbits.WPUA5
#define LED_5_OD                ODCONAbits.ODCA5
#define LED_5_ANS                ANSELAbits.ANSELA5
#define LED_5_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define LED_5_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define LED_5_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define LED_5_GetValue()           PORTAbits.RA5
#define LED_5_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define LED_5_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define LED_5_SetPullup()      do { WPUAbits.WPUA5 = 1; } while(0)
#define LED_5_ResetPullup()    do { WPUAbits.WPUA5 = 0; } while(0)
#define LED_5_SetPushPull()    do { ODCONAbits.ODCA5 = 0; } while(0)
#define LED_5_SetOpenDrain()   do { ODCONAbits.ODCA5 = 1; } while(0)
#define LED_5_SetAnalogMode()  do { ANSELAbits.ANSELA5 = 1; } while(0)
#define LED_5_SetDigitalMode() do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set LED_4 aliases
#define LED_4_TRIS               TRISAbits.TRISA7
#define LED_4_LAT                LATAbits.LATA7
#define LED_4_PORT               PORTAbits.RA7
#define LED_4_WPU                WPUAbits.WPUA7
#define LED_4_OD                ODCONAbits.ODCA7
#define LED_4_ANS                ANSELAbits.ANSELA7
#define LED_4_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define LED_4_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define LED_4_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define LED_4_GetValue()           PORTAbits.RA7
#define LED_4_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define LED_4_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define LED_4_SetPullup()      do { WPUAbits.WPUA7 = 1; } while(0)
#define LED_4_ResetPullup()    do { WPUAbits.WPUA7 = 0; } while(0)
#define LED_4_SetPushPull()    do { ODCONAbits.ODCA7 = 0; } while(0)
#define LED_4_SetOpenDrain()   do { ODCONAbits.ODCA7 = 1; } while(0)
#define LED_4_SetAnalogMode()  do { ANSELAbits.ANSELA7 = 1; } while(0)
#define LED_4_SetDigitalMode() do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set LED aliases
#define LED_TRIS               TRISBbits.TRISB3
#define LED_LAT                LATBbits.LATB3
#define LED_PORT               PORTBbits.RB3
#define LED_WPU                WPUBbits.WPUB3
#define LED_OD                ODCONBbits.ODCB3
#define LED_ANS                ANSELBbits.ANSELB3
#define LED_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define LED_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define LED_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define LED_GetValue()           PORTBbits.RB3
#define LED_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define LED_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define LED_SetPullup()      do { WPUBbits.WPUB3 = 1; } while(0)
#define LED_ResetPullup()    do { WPUBbits.WPUB3 = 0; } while(0)
#define LED_SetPushPull()    do { ODCONBbits.ODCB3 = 0; } while(0)
#define LED_SetOpenDrain()   do { ODCONBbits.ODCB3 = 1; } while(0)
#define LED_SetAnalogMode()  do { ANSELBbits.ANSELB3 = 1; } while(0)
#define LED_SetDigitalMode() do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set LASER1 aliases
#define LASER1_TRIS               TRISBbits.TRISB4
#define LASER1_LAT                LATBbits.LATB4
#define LASER1_PORT               PORTBbits.RB4
#define LASER1_WPU                WPUBbits.WPUB4
#define LASER1_OD                ODCONBbits.ODCB4
#define LASER1_ANS                ANSELBbits.ANSELB4
#define LASER1_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define LASER1_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define LASER1_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define LASER1_GetValue()           PORTBbits.RB4
#define LASER1_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define LASER1_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define LASER1_SetPullup()      do { WPUBbits.WPUB4 = 1; } while(0)
#define LASER1_ResetPullup()    do { WPUBbits.WPUB4 = 0; } while(0)
#define LASER1_SetPushPull()    do { ODCONBbits.ODCB4 = 0; } while(0)
#define LASER1_SetOpenDrain()   do { ODCONBbits.ODCB4 = 1; } while(0)
#define LASER1_SetAnalogMode()  do { ANSELBbits.ANSELB4 = 1; } while(0)
#define LASER1_SetDigitalMode() do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set LASER0 aliases
#define LASER0_TRIS               TRISBbits.TRISB5
#define LASER0_LAT                LATBbits.LATB5
#define LASER0_PORT               PORTBbits.RB5
#define LASER0_WPU                WPUBbits.WPUB5
#define LASER0_OD                ODCONBbits.ODCB5
#define LASER0_ANS                ANSELBbits.ANSELB5
#define LASER0_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define LASER0_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define LASER0_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define LASER0_GetValue()           PORTBbits.RB5
#define LASER0_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define LASER0_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define LASER0_SetPullup()      do { WPUBbits.WPUB5 = 1; } while(0)
#define LASER0_ResetPullup()    do { WPUBbits.WPUB5 = 0; } while(0)
#define LASER0_SetPushPull()    do { ODCONBbits.ODCB5 = 0; } while(0)
#define LASER0_SetOpenDrain()   do { ODCONBbits.ODCB5 = 1; } while(0)
#define LASER0_SetAnalogMode()  do { ANSELBbits.ANSELB5 = 1; } while(0)
#define LASER0_SetDigitalMode() do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set LED_3 aliases
#define LED_3_TRIS               TRISCbits.TRISC0
#define LED_3_LAT                LATCbits.LATC0
#define LED_3_PORT               PORTCbits.RC0
#define LED_3_WPU                WPUCbits.WPUC0
#define LED_3_OD                ODCONCbits.ODCC0
#define LED_3_ANS                ANSELCbits.ANSELC0
#define LED_3_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define LED_3_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define LED_3_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define LED_3_GetValue()           PORTCbits.RC0
#define LED_3_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define LED_3_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define LED_3_SetPullup()      do { WPUCbits.WPUC0 = 1; } while(0)
#define LED_3_ResetPullup()    do { WPUCbits.WPUC0 = 0; } while(0)
#define LED_3_SetPushPull()    do { ODCONCbits.ODCC0 = 0; } while(0)
#define LED_3_SetOpenDrain()   do { ODCONCbits.ODCC0 = 1; } while(0)
#define LED_3_SetAnalogMode()  do { ANSELCbits.ANSELC0 = 1; } while(0)
#define LED_3_SetDigitalMode() do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set LED_1 aliases
#define LED_1_TRIS               TRISCbits.TRISC1
#define LED_1_LAT                LATCbits.LATC1
#define LED_1_PORT               PORTCbits.RC1
#define LED_1_WPU                WPUCbits.WPUC1
#define LED_1_OD                ODCONCbits.ODCC1
#define LED_1_ANS                ANSELCbits.ANSELC1
#define LED_1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define LED_1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define LED_1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define LED_1_GetValue()           PORTCbits.RC1
#define LED_1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define LED_1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define LED_1_SetPullup()      do { WPUCbits.WPUC1 = 1; } while(0)
#define LED_1_ResetPullup()    do { WPUCbits.WPUC1 = 0; } while(0)
#define LED_1_SetPushPull()    do { ODCONCbits.ODCC1 = 0; } while(0)
#define LED_1_SetOpenDrain()   do { ODCONCbits.ODCC1 = 1; } while(0)
#define LED_1_SetAnalogMode()  do { ANSELCbits.ANSELC1 = 1; } while(0)
#define LED_1_SetDigitalMode() do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set LED_2 aliases
#define LED_2_TRIS               TRISCbits.TRISC2
#define LED_2_LAT                LATCbits.LATC2
#define LED_2_PORT               PORTCbits.RC2
#define LED_2_WPU                WPUCbits.WPUC2
#define LED_2_OD                ODCONCbits.ODCC2
#define LED_2_ANS                ANSELCbits.ANSELC2
#define LED_2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define LED_2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define LED_2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define LED_2_GetValue()           PORTCbits.RC2
#define LED_2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define LED_2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define LED_2_SetPullup()      do { WPUCbits.WPUC2 = 1; } while(0)
#define LED_2_ResetPullup()    do { WPUCbits.WPUC2 = 0; } while(0)
#define LED_2_SetPushPull()    do { ODCONCbits.ODCC2 = 0; } while(0)
#define LED_2_SetOpenDrain()   do { ODCONCbits.ODCC2 = 1; } while(0)
#define LED_2_SetAnalogMode()  do { ANSELCbits.ANSELC2 = 1; } while(0)
#define LED_2_SetDigitalMode() do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set SCL1 aliases
#define SCL1_TRIS               TRISCbits.TRISC3
#define SCL1_LAT                LATCbits.LATC3
#define SCL1_PORT               PORTCbits.RC3
#define SCL1_WPU                WPUCbits.WPUC3
#define SCL1_OD                ODCONCbits.ODCC3
#define SCL1_ANS                ANSELCbits.ANSELC3
#define SCL1_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SCL1_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SCL1_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SCL1_GetValue()           PORTCbits.RC3
#define SCL1_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SCL1_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define SCL1_SetPullup()      do { WPUCbits.WPUC3 = 1; } while(0)
#define SCL1_ResetPullup()    do { WPUCbits.WPUC3 = 0; } while(0)
#define SCL1_SetPushPull()    do { ODCONCbits.ODCC3 = 0; } while(0)
#define SCL1_SetOpenDrain()   do { ODCONCbits.ODCC3 = 1; } while(0)
#define SCL1_SetAnalogMode()  do { ANSELCbits.ANSELC3 = 1; } while(0)
#define SCL1_SetDigitalMode() do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set SDA1 aliases
#define SDA1_TRIS               TRISCbits.TRISC4
#define SDA1_LAT                LATCbits.LATC4
#define SDA1_PORT               PORTCbits.RC4
#define SDA1_WPU                WPUCbits.WPUC4
#define SDA1_OD                ODCONCbits.ODCC4
#define SDA1_ANS                ANSELCbits.ANSELC4
#define SDA1_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define SDA1_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define SDA1_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define SDA1_GetValue()           PORTCbits.RC4
#define SDA1_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define SDA1_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define SDA1_SetPullup()      do { WPUCbits.WPUC4 = 1; } while(0)
#define SDA1_ResetPullup()    do { WPUCbits.WPUC4 = 0; } while(0)
#define SDA1_SetPushPull()    do { ODCONCbits.ODCC4 = 0; } while(0)
#define SDA1_SetOpenDrain()   do { ODCONCbits.ODCC4 = 1; } while(0)
#define SDA1_SetAnalogMode()  do { ANSELCbits.ANSELC4 = 1; } while(0)
#define SDA1_SetDigitalMode() do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()    do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()   do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()   do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()         PORTCbits.RC6
#define RC6_SetDigitalInput()   do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()  do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()     do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()   do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode() do { ANSELCbits.ANSELC6 = 1; } while(0)
#define RC6_SetDigitalMode()do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()    do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()   do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()   do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()         PORTCbits.RC7
#define RC7_SetDigitalInput()   do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()  do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetPullup()     do { WPUCbits.WPUC7 = 1; } while(0)
#define RC7_ResetPullup()   do { WPUCbits.WPUC7 = 0; } while(0)
#define RC7_SetAnalogMode() do { ANSELCbits.ANSELC7 = 1; } while(0)
#define RC7_SetDigitalMode()do { ANSELCbits.ANSELC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/