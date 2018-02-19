/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void initApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */
    
    /*CONFIGURE OSCILLATOR*/
    // set oscillator to 8MHz
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;
    /* Setup analog functionality and port direction */

    /* Initialize peripherals */
    TRISDbits.RD2 = 0;  
    YLED = 1;
    
    TRISDbits.RD3 = 0;
    RLED = 0;
    
    int32_t counter = 0;
    
    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

    /* Enable interrupts */
    
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
}

void uartInit(void)
{
        // EUSART setup
    SPBRG = 12; // set baud rate for 9615
    TRISCbits.RC7 = 1; //RX pin
    TRISCbits.RC6 = 1; //TX pin
    RCSTAbits.SPEN = 1; // serial port enabled
    RCSTAbits.RX9 = 0; // 8 bit reception
    RCSTAbits.CREN = 1; // enables receiver
    TXSTAbits.CSRC = 1;
    TXSTAbits.TX9 = 0;  // 8 bit TX
    TXSTAbits.TXEN = 1; // transmit enabled
    TXSTAbits.SYNC = 0; //Asynchronous mode
    TXSTAbits.BRGH = 0; //Low speed
}
void uartPut(uint8_t c)
{
    while(!UART_TX_FLAG);
    UART_TX_REG = c;
}
void uartTx(char *str)
{
    uint8_t c;
    while( c = *str++)
    {
        uartPut(c);
    }
}

void bootMsg(void)
{
    uartTx((char *)"\n\rAuthor:\t\tStephen West\n");
    uartTx((char *)"\rDate:\t\t2-18-2018\n");
    uartTx((char *)"\rVersion:\t1.0\n");
    uartTx((char *)"\rDevice:\t\tpic18LF4620\n");
    uartTx((char *)"\rComplier:\tXC8\n\n");
}

void spiConfig(void)
{
    
    TRISCbits.RC5 = 0; //SDO must have TRISC<5> bit cleared
    TRISCbits.RC3 = 0; //SCK (Master mode) must have TRISC<3> bit cleared
    
    
    SSPCON1bits.SSPEN = 1;  //Enables serial port and configures SCK, SDO, SDI and SS as serial port pins
    SSPCON1bits.CKP = 1;    //Idle state for clock is a high level
    
    //SPI Master mode, clock = FOSC/4
    SSPCON1bits.SSPM3 = 0;
    SSPCON1bits.SSPM2 = 0;
    SSPCON1bits.SSPM1 = 0;
    SSPCON1bits.SSPM0 = 0;
    
    TRISDbits.RD0 = 0;
    CS1 = 1;
    TRISDbits.RD1 = 0;
    CS2 = 1;
            
    
}



void spiWrite(spiDevice dev, uint16_t data)
{
    // select what device to write to
    /*switch(dev)
    {
        case dev1:  CS1 = 0;
        case dev2:  CS2 = 0;
    }*/
    CS1 = 0;
    SSPBUF = (uint8_t)data;
    CS1 = 1;
    
    switch(dev)
    {
        case dev1:  CS1 = 1;
        case dev2:  CS2 = 1;
    } 
}