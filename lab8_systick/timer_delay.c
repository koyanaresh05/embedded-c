    /* systick_int.c

     *

     * Toggle the red LED using the SysTick interrupt

     *

     * This program sets up the SysTick to interrupt at 1 Hz.

     * The system clock is running at 16 MHz.

     * 1sec/62.5ns = 16,000,000 for RELOAD register.

     * In the interrupt handler, the red LED is toggled.

    */


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
    #include <stdint.h>
    #include "tm4c123gh6pm.h"

    #include "seven_seg.h"
    void delayMs(int n);
    void enable_irq(void);
    void SysTick_Handler(void);
    int count = 0,check;
    unsigned char digitPattern[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};  //common cathode
    volatile unsigned int i;
    int main (void)

    {
        PORTA_Init();
        PORTB_Init();
        int x=0,u,w;
        u = floor(count/10);
                GPIO_PORTB_DATA_R = digitPattern[u];   //display digits from 0 to 9
                GPIO_PORTA_DATA_R = 0x20;
                delayMs(1);
                w = count%10;
                GPIO_PORTB_DATA_R = digitPattern[w];   //display digits from 0 to 9
                GPIO_PORTA_DATA_R = 0x10;
                delayMs(1);
        /* enable clock to GPIOF at clock gating control register */

        SYSCTL_RCGC2_R |= 0x20;

        /* enable the GPIO pins for the LED (PF3, 2, 1) as output */

        GPIO_PORTF_DIR_R = 0x0E;

        /* enable the GPIO pins for digital function */

        GPIO_PORTF_DEN_R = 0x0E;



        /* Configure SysTick */

        NVIC_ST_RELOAD_R = 16000000-1;  /* reload with number of clocks per second */

        NVIC_ST_CTRL_R = 7;             /* enable SysTick interrupt, use system clock */



        enable_irq();                   /* global enable interrupt */


        while(1) {

        ;

        }
        //for(int i=0; i<250; i++){

       // }

    }

    void SysTick_Handler(void)
    {

        count++;
        check = count/5; //5 sec delay
        if((check%2) == 0 )  //5 sec
           GPIO_PORTF_DATA_R = 2;         /* toggle the red LED */
        if((check%2) != 0)  //5 sec
            GPIO_PORTF_DATA_R = 0;         /* toggle the red LED */

        /*

        */
    }

    /* delay n milliseconds (16 MHz CPU clock) */

    void delayMs(int n)

    {


            int i, j;
               for(i = 0 ; i < n; i++){
                   for(j = 0; j < 3180; j++) {} /* do nothing for 1 ms */
               }

        }

    /* global enable interrupts */

    void inline enable_irq(void)

    {

        __asm  ("    CPSIE  I\n");

    }
