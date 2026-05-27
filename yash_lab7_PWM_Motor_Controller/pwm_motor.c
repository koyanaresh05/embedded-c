#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <tm4c123gh6pm.h>





void PWM_Init()
{
//int x = 15999;


/* Enable Peripheral Clocks */
SYSCTL_RCGCPWM_R |= 2; /* enable clock to PWM1 */
SYSCTL_RCGCGPIO_R |= 0x10; /* enable clock to PORTE */
SYSCTL_RCC_R &= ~0x00100000; /* no pre-divide for PWM clock */


/* Enable port PE5 for PWM1 M1PWM3 */
GPIO_PORTE_AFSEL_R = 0x20; /* PE5 uses alternate function */
GPIO_PORTE_PCTL_R &= ~0x00F00000; /* make PF3 PWM output pin */
GPIO_PORTE_PCTL_R |= 0x00500000;
GPIO_PORTE_DEN_R |= 0x20; /* pin digital */


PWM1_1_CTL_R = 0; /* stop counter */
PWM1_1_GENB_R = 0x0000008C; /* M1PWM7 output set when reload, */
/* clear when match PWMCMPA */
PWM1_1_LOAD_R = 5000; /* set load value for 1kHz (16MHz/16000) */
PWM1_1_CMPA_R = 4999; /* set duty cycle to min */
PWM1_1_CTL_R = 1; /* start timer */
PWM1_ENABLE_R = 0x08; /* start PWM1 ch4 */
}




