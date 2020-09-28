#import <stio.h>
#import <stdint.h>

#define Board_UART_RX               IOID_2          /* RXD  */
#define Board_UART_TX               IOID_3          /* TXD  */

#define RX_CFG                      CC2650_LAUNCHXL_IOCFG2
#define TX_CFG                      CC2650_LAUNCHXL_IOCFG3

void initiate_uart(){

    //Map UART_RX to Pin 2, TX to Pin 3
    RX_CFG | 0x0F;
    TX_CFG | 0x10;

    //Enable serial power domain and UART module
    CC2650_LAUNCHXL_UARTCLKGR | 0x01;
    CC2650_LAUNCHXL_UARTCLKGDS | 0x01;

    //Load settings to clock controller
    CC2650_LAUNCHXL_CLKLOADCTL | 0x01;

    //Disable UART
    CC2650_LAUNCHXL_CTL & 0XFFFFFFFE;

    //Set baud rate to 115200
    CC2650_LAUNCHXL_IBRD | 0x0D;
    CC2650_LAUNCHXL_FBRD | 0x01;

    //Word length of 8 bits, char mode (FIFOs disabled), one stop bit,
    //No parity, No interrupts
    //Write UART configuration to module
    CC2650_LAUNCHXL_LCRH | 0x60;

    //Enable UART
    CC2650_LAUNCHXL_CTL | 0x01;
}

void send_char(char data){
    CC2650_LAUNCHXL_DR | data;
}

/**
 * main.c
 */
int main(void)
{
    initiate_uart();
    send_char('U');
    send_char('V');
    send_char('A');

	return 0;
}
