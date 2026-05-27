#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <tm4c123gh6pm.h>



void DisableInterrupts(void);
void EnableInterrupts(void);
void WaitForInterrupt(void);
void delayMs(int n);
void UART_Write(char c);
void putString(char *s);
void Init_UART(void);



void UART_Write(char c){


            while ((UART0_FR_R & (1 << 5))); //The UART is busy transmitting data. This bit remains set untilthe complete byte, including all stop bits, has been sent fromthe shift register.
            UART0_DR_R = c;
}
// Writes string s on the terminal
void putString(char * s){

    while (*s != '\0'){
        UART_Write(*s);
        s++;
    }
    UART_Write( '\n'); // to go next line
    UART_Write( '\r');// for going to the initial point of next line
    return;
}

void Init_PORTF(void){
    SYSCTL_RCGC2_R   |= 0x00000020;   /* enable clock to GPIOF */
    GPIO_PORTF_LOCK_R = 0x4C4F434B; /* unlock commit register */
    GPIO_PORTF_CR_R   = 0x01;         /* make PORTF0 configurable */
    GPIO_PORTF_DIR_R  = 0x0E;        /* set PORTF1 pin as output (LED) pin *//* and PORTF0 as input, SW2 is on PORTF0 */
    GPIO_PORTF_DEN_R  = 0x1F;        /* set PORTF pins 1-0 as digital pins */
    GPIO_PORTF_PUR_R  = 0x11;        /* enable pull up for pin 0 */
}

void Init_UART(void){
    //Activate UART0
        SYSCTL_RCGCUART_R |= 0x01;
        //Activate PORTA
        SYSCTL_RCGCGPIO_R |= 0x01;
        // Disable the UART0
        UART0_CTL_R |= UART_CTL_UARTEN;
        // Set the baud rate to 115200

        UART0_IBRD_R = 8;  /* IBRD = int(16,000,000 / (16 * 115200)) = int(8.68) */
        UART0_FBRD_R = 44;
        // line control value for 1 stop bit, no FIFO, no interrupt, no parity, and 8-bit data size

        UART0_LCRH_R |= 0x70;

        //Set TxE and RxE bits in UARTCTL register to enable the transmitter and receiver of UART0.
        UART0_CTL_R |= UART_CTL_TXE | UART_CTL_RXE;
        //Make PA0 and PA1 pins to be used as Digital I/O
        GPIO_PORTA_DEN_R |= 0x03;
        //Select the alternate functions of PA0 (RxD) and PA1 (TxD)
        GPIO_PORTA_AFSEL_R |= 0x03;
        //Configure PA0 and PA1 pins for UART function
        GPIO_PORTA_PCTL_R |= 0x11;
        // diabale analog functionaliuty
        GPIO_PORTA_AMSEL_R = 0;

          // enable interrupt
        UART0_ICR_R = (0x010); // Clear receive interrupt
        UART0_IM_R  |= 0x0010;
        NVIC_PRI7_R = (NVIC_PRI7_R & 0xFFFF1FFF) | 0x0000A000; /*  priority 5 */
        NVIC_EN0_R = 0x00000020;        /*  Enable interrupt 5 in NVIC */
        EnableInterrupts();             /* Enable global Interrupt flag (I) */
}


/*********** DisableInterrupts ***************
*
* disable interrupts
*
* inputs:  none
* outputs: none
*/

void DisableInterrupts(void)
{
    __asm ("    CPSID  I\n");
}

/*********** EnableInterrupts ***************
*
* emable interrupts
*
* inputs:  none
* outputs: none
*/

void EnableInterrupts(void)
{
    __asm  ("    CPSIE  I\n");
}

/*********** WaitForInterrupt ************************
*
* go to low power mode while waiting for the next interrupt
*
* inputs:  none
* outputs: none
*/

void WaitForInterrupt(void)
{
    __asm  ("    WFI\n");
}

