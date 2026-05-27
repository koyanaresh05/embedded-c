#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <tm4c123gh6pm.h>

#include "nvic_uart.h"
#define  LED_OFF    (GPIO_PORTF_DATA_R = 0x00)

void delayMs(int n);

int present_color=1;
int blink_state;
void UART0_Handler( void )
    {
        char string[30]="\0";
        int i;
        char *temp;

        // Void UART_Read(int iport, char *pcbyte); functionality

            i = 0;
            char val = 0;
            while((val != '\n') && (val !='\r')){

                if(!(UART0_FR_R & (1 << 4))){ //true when receiver is not empty
                    val = UART0_DR_R;
                    string[i++] = val;
                    UART_Write(val);
                    *temp = val;
                    temp++;

                }
                string[i] = '\0';
            }
            temp = 0;

            if (strstr(string, "led sw1"))  //sw1 is pressed
                {
                    present_color = present_color+1;
                   // putString("hello1111");
                    if(present_color > 4)
                        present_color = 1;

                }
                if(strstr(string, "led sw2")) //sw2 is pressed
                    blink_state ^= 1;
                //putString("hello");

                delayMs(10);
                UART0_ICR_R  = (0x010);

}


int main(void)
{
    Init_PORTF();
    Init_UART();               /* initialize UART0 interrupt */

    uint32_t led_state;

    while(1)
    {
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
        if(blink_state == 0)       //only change  color periodically R/G/B/W
            GPIO_PORTF_DATA_R = led_state;
        else{
            LED_OFF;
            delayMs(100);
            GPIO_PORTF_DATA_R = led_state;
            delayMs(100);
        }
    }

}




//provides delay of n milli secs
void delayMs(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++){
        for(j = 0; j < 3180; j++) {}   /* do nothing for 1 ms */
    }
}


