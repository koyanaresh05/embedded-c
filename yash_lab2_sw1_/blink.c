/*
 * switch_blink.c
 *
 *  Created on: 02-Feb-2022
 *      Author: yashash
 */


#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "driverlib/can.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "inc/tm4c123gh6pm.h"


#include "uartstdio.h"


void delayMs(int n);

int main(void)
{

    unsigned int value, value1;

    SYSCTL_RCGC2_R |= 0x00000020;;      /* enable clock to GPIOF */
    GPIO_PORTF_LOCK_R = 0x4C4F434B;     /* unlock commit register */
    GPIO_PORTF_CR_R = 0x01;             /* make PORTF0 configurable */
    GPIO_PORTF_DIR_R = 0x0E;            /* set PORTF3+PORTF2+PORTF1 pin as output (LED) pin */
    /* and PORTF4 and PORTF0 as input, SW1 is on PORTF4  and SW2 is PORTF0*/
    GPIO_PORTF_DEN_R = 0x1F;            /* set PORTF pins 4-3-2-1 as digital pins */
    GPIO_PORTF_PUR_R = 0x11;            /* enable pull up for pin 4 and 0 */


    // Set up debugging UART
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    GPIOPinConfigure(GPIO_PC4_U1RX);
    GPIOPinConfigure(GPIO_PC5_U1TX);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    UARTStdioConfig(1, 9600, SysCtlClockGet());

    UARTprintf("BOHAHA");

    while (1)

    {

        value = GPIO_PORTF_DATA_R;
        value1 = 0x11;
        value = value & value1;


        if (value == 0x01)  //sw1 is pressed
        {
            GPIO_PORTF_DATA_R = 0x02;
            UARTprintf("sw1 is pressed");
        }
        else if(value == 0x10) //sw2 is pressed
        {
            GPIO_PORTF_DATA_R = 0x04;
            UARTprintf("sw2 is pressed");

        }
        else if(value == 0x00) //sw1 and sw2 both pressed
        {
            GPIO_PORTF_DATA_R = 0x08;
            UARTprintf("sw2 and sw2 is pressed");
        }
        else
            GPIO_PORTF_DATA_R = 0x0E;

        delayMs(100);
    }

}

void delayMs(int n)

{


        int i, j;
           for(i = 0 ; i < n; i++){
               for(j = 0; j < 3180; j++) {} /* do nothing for 1 ms */
           }

    }
