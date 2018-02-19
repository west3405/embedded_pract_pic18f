/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */
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


#define UART_TX_FLAG    TXSTAbits.TRMT
#define UART_TX_REG     TXREG



#define MSSP_BUFF_FLAG  SSPSTATbits.BF
#define CS1             LATDbits.LATD0
#define CS2             LATDbits.LATD1


typedef enum { dev1, dev2} spiDevice;




/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void initApp(void);         /* I/O and Peripheral Initialization */

void uartInit(void);
void uartPut(uint8_t c);
void uartTx(char *str);

void bootMsg(void);

void spiConfig(void);
void spiWrite(spiDevice dev, uint16_t data);