#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "tm4c123gh6pm.h"
#include <string.h>


#define GPIO_PORTB_CLK_EN  0x02      //enable clock for PORTB
#define GPIO_PORTA_CLK_EN  0x01      //enable clock for PORTA

void ADC0_Init(void);
void delayMs(int n);
void PORTB_Init(void);
void PORTA_Init(void);


void ADC0_Init(){
    /* enable clocks */

       SYSCTL_RCGCGPIO_R |= 0x10; /* enable clock to PE (AIN0 is on PE3) */

       SYSCTL_RCGCADC_R |= 1;     /* enable clock to ADC0 */



       /* initialize PE3 for AIN0 input  */

       GPIO_PORTE_AFSEL_R |= 8;   /* enable alternate function */

       GPIO_PORTE_DEN_R &= ~8;    /* disable digital function */

       GPIO_PORTE_AMSEL_R |= 8;   /* enable analog function */



       /* initialize ADC0 */

       ADC0_ACTSS_R &= ~8;        /* disable SS3 during configuration */

       ADC0_EMUX_R &= ~0xF000;    /* software trigger conversion */

       ADC0_SSMUX3_R = 0;         /* get input from channel 0 */

       ADC0_SSCTL3_R |= 6;        /* take one sample at a time, set flag at 1st sample */

       ADC0_ACTSS_R |= 8;         /* enable ADC0 sequencer 3 */


}

void PORTB_Init(void)
    {
        SYSCTL_RCGCGPIO_R |= GPIO_PORTB_CLK_EN;           //activate clock for Port B
        //delayMs(10);                                                                      //Delay 10 msec to allow clock to start on PORTB
        GPIO_PORTB_DEN_R = 0xFF;                                        // Enable all pins of PORTB
        GPIO_PORTB_DIR_R = 0xFF;                                        // Make all pins of PORTB as ouptut pin
        GPIO_PORTB_PCTL_R &= ~(0xFF) ;                                      // Regular GPIO of PORTB
        GPIO_PORTB_AMSEL_R &= ~(0xFF);                              // Disable analog function on all pins of PORTB
        GPIO_PORTB_AFSEL_R &= ~(0xFF);                              // Regular port function
    }

void PORTA_Init(void)
{
    SYSCTL_RCGCGPIO_R |= GPIO_PORTA_CLK_EN;           //activate clock for Port A
    //delayMs(10);                                      //Delay 10 msec to allow clock to start on PORTB
    GPIO_PORTA_DEN_R |= 0x30; // Enable pin 2 of PORTA
    GPIO_PORTA_DIR_R |= 0x30; // Make pin 2 of PORTA as ouptut pin GPIO_PORTA_PCTL_R &= ~GPIO_PORTA_PIN2_EN; // Regular GPIO of PORTA
    GPIO_PORTA_AMSEL_R &= ~(0x30); // Disable analog function on pin 2 of PORTA GPIO_PORTA_AFSEL_R &= ~GPIO_PORTA_PIN2_EN; // Regular port function
}

void delayMs(int n)

    {

    int i, j;
       for(i = 0 ; i < n; i++){
           for(j = 0; j < 3180; j++) {} /* do nothing for 1 ms */
       }

    }
