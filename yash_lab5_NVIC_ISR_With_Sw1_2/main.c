/* sw1_int.c
 *
 * Runs on EK-TM4C123GXL LaunchPad
 *
 * GPIO PORTF interrupt that will toggle the on board Blue LED
 * on rising edge whenever a user switch (SW1) is pressed.
 *
 */
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "nvic_sw.h"

#define  LED_RED    (GPIO_PORTF_DATA_R = 0x02)
#define  LED_BLUE   (GPIO_PORTF_DATA_R = 0x04)
#define  LED_GREEN  (GPIO_PORTF_DATA_R = 0x08)
#define  LED_WHITE  (GPIO_PORTF_DATA_R = 0x0E)
#define  LED_YELLOW  (GPIO_PORTF_DATA_R = 0x0A)
#define  LED_OFF    (GPIO_PORTF_DATA_R = 0x00)

void delayMs1(int n);
int value;
int present_color=1;
int blink_state;

//provides delay of n milli secs
void delayMs1(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++){
        for(j = 0; j < 3180; j++) {}   /* do nothing for 1 ms */
    }
}

void GPIOPortF_Handler(void)
{

    value = GPIO_PORTF_DATA_R;
    if ((value & 0x11) == 0x01)  //sw1 is pressed
    {
        present_color = present_color+1;
        if(present_color > 4)
            present_color = 1;

    }
    if((value & 0x11) == 0x10) //sw2 is pressed
        blink_state ^= 1;


    delayMs1(50);
    GPIO_PORTF_ICR_R = 0x11;        /* clear PF4-0 int */

}


int main(void)
{
    GPIOPortF_Init();               /* initialize GPIO Port F interrupt */
    uint32_t led_state;
    while(1) {
        switch(present_color){
        case 1:
            led_state = 0x02;
            break;
        case 2:
            led_state = 0x08;
            break;
        case 3:
            led_state = 0x04;
            break;
        case 4:
            led_state = 0x0E;
        default:
            led_state = 0x0E;

        }
        if(blink_state == 0)
            GPIO_PORTF_DATA_R = led_state;
        else{
            LED_OFF;
            delayMs1(100);
            GPIO_PORTF_DATA_R = led_state;
            delayMs1(100);
        }

    }
}
