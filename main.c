/*
 * CONFIGURATION
 *
 * 
 */

// CONFIG1H
// CONFIG1H
#pragma config OSC = INTIO67    // Oscillator Selection bits (Internal oscillator block, port function on RA6 and RA7)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (00C000-00FFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (00C000-00FFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <pic18LF4620.h>

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#endif

//#include "system.h"        /* System funct/params, like osc/peripheral config */
//#include "user.h"          /* User funct/params, such as InitApp */


/// defines to be put in headers

#define SYS_FREQ        8000000L
#define FCY             SYS_FREQ/4

// timer defines
#define TMR0_IF         INTCONbits.TMR0IF
#define TMR0L           TMR0L
#define TMR0_ON         T0CONbits.TMR0ON

// int 0 defines
#define INT0_IF         INTCONbits.INT0IF
#define INT0_ON         INTCONbits.INT0IE

#define YLED            LATDbits.LATD2
#define RLED            LATDbits.LATD3
/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    /*CONFIGURE OSCILLATOR*/
    // set oscillator to 8MHz
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;
    
    /*
    Set IO
    */
    
    // set pin 21 as output
    TRISDbits.RD2 = 0;  
    YLED = 1;
    
    // set pin 22 as output
    TRISDbits.RD3 = 0;
    RLED = 0;
    
    int32_t counter = 0;
    
    /**
     * enable interrupts 
     */
       
    RCONbits.IPEN = 1; //  priority levels on interrupts

    
    // TIMER0 ISR
    INTCON2bits.TMR0IP  = 1; //timeer0 is high priority
    INTCONbits.TMR0IE = 1; // Enable the TMR0 overflow interrupt
    T0CONbits.TMR0ON = 1; // Enable timer 0 
    T0CONbits.T08BIT = 1; // timer0 is 8 bir timer/counter
    T0CONbits.T0CS = 0; // Transition on fosc/4 pin
    T0CONbits.T0SE = 0; // increment on low to high transition on T0CKI pin
    T0CONbits.PSA = 1; // Timer0 pre scalar not assigned
    TMR0L = 0xfe;
    /*
    T0CONbits.T0PS0 = 0; // pre scale bits
    T0CONbits.T0PS1 = 0;
    T0CONbits.T0PS2 = 0;
     */
    INTCONbits.TMR0IF = 0; // set interrupt flag to 0
    
    // INT 0 ISR
    INTCONbits.INT0IE = 1; // enable int0 external interrupt
    INTCON2bits.INTEDG0 = 0; // Interrupt on falling edge
    
    
    
    
    INTCONbits.GIEH = 1; // Global high priority interrupt enable
    INTCONbits.GIEL = 1; // Global low priority interrupt enable

    while(1)
    {
        if(counter++ > 1000)
        {
            //YLED = ~YLED;
            counter = 0;
        }
            
    }

}
void interrupt high_isr(void)
{
    
    if (TMR0_IF && TMR0_ON) // check if timer0 interrupt occurred
    {
        
        TMR0_IF = 0; // clear flag
        static int iii = 0;
        if(iii++)
        {
            RLED = ~RLED;
            iii = 0;
        }
        /*else
        {
            iii++;
        }*/
            
            
        
    }
    
    if (INT0_IF && INT0_ON)
    {
        INT0_IF = 0;
        YLED = ~YLED;
    }
}
 