
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


void PORTB_Init(void);
void PORTA_Init(void);




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


