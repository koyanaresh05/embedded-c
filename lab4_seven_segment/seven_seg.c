
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "tm4c123gh6pm.h"
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/sysctl.h>
#include <driverlib/uart.h>
#include <string.h>

#define GPIO_PORTB_CLK_EN  0x02      //enable clock for PORTB
#define GPIO_PORTA_CLK_EN  0x01      //enable clock for PORTA

void delayMs(int n);
void PORTF_Init(void);
void PORTB_Init(void);
void PORTA_Init(void);


void PORTF_Init(void)
{
    SYSCTL_RCGC2_R |= 0x00000020;;      /* enable clock to GPIOF */
    GPIO_PORTF_LOCK_R = 0x4C4F434B;     /* unlock commit register */
    GPIO_PORTF_CR_R = 0x01;             /* make PORTF0 configurable */
    GPIO_PORTF_DIR_R = 0x0E;            /* set PORTF3+PORTF2+PORTF1 pin as output (LED) pin */
                                        /* and PORTF4 and PORTF0 as input, SW1 is on PORTF4  and SW2 is PORTF0*/
    GPIO_PORTF_DEN_R = 0x1F;            /* set PORTF pins 4-3-2-1 as digital pins */
    GPIO_PORTF_PUR_R = 0x11;            /* enable pull up for pin 4 and 0 */

}

void PORTB_Init(void)
{
    SYSCTL_RCGCGPIO_R |= GPIO_PORTB_CLK_EN;           //activate clock for Port B
                                                                         //Delay 10 msec to allow clock to start on PORTB
    GPIO_PORTB_DEN_R = 0xFF;                                        // Enable all pins of PORTB
    GPIO_PORTB_DIR_R = 0xFF;                                        // Make all pins of PORTB as ouptut pin
    GPIO_PORTB_PCTL_R &= ~(0xFF) ;                                      // Regular GPIO of PORTB
    GPIO_PORTB_AMSEL_R &= ~(0xFF);                              // Disable analog function on all pins of PORTB
    GPIO_PORTB_AFSEL_R &= ~(0xFF);                              // Regular port function
}

void PORTA_Init(void)
{
    SYSCTL_RCGCGPIO_R |= GPIO_PORTA_CLK_EN;           //activate clock for Port A
                                        //Delay 10 msec to allow clock to start on PORTB
    GPIO_PORTA_DEN_R |= 0x30; // Enable pin 2 of PORTA
    GPIO_PORTA_DIR_R |= 0x30; // Make pin 2 of PORTA as ouptut pin GPIO_PORTA_PCTL_R &= ~GPIO_PORTA_PIN2_EN; // Regular GPIO of PORTA
    GPIO_PORTA_AMSEL_R &= ~(0x30); // Disable analog function on pin 2 of PORTA GPIO_PORTA_AFSEL_R &= ~GPIO_PORTA_PIN2_EN; // Regular port function
}

void UART0_Init(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

}
/* delay n milliseconds (16 MHz CPU clock) */

void delayMs(int n)

{


        int i, j;
           for(i = 0 ; i < n; i++){
               for(j = 0; j < 3180; j++) {} /* do nothing for 1 ms */
           }

    }

