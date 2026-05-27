/* Seven Segment Display
 * Author; Yashash Jain
 * Date: 23/02/2022 */


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

#include "seven_seg.h"


void delayMs1(int n);
unsigned int value;
int flag = 0;
int main(void)
{


    int  temp = 0;
    char val;
    char string[30]="\0";
    PORTF_Init();
    PORTB_Init();
    PORTA_Init();
    UART0_Init();

    //unsigned char digitPattern[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};  //common anode
    unsigned char digitPattern[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};  //common cathode
    volatile unsigned int i;


    int  timer = 5;
    while(1)
    {
            i=0;
            val=0;
            string[0]='\0';
            while(!temp)
            {
                if((UARTCharsAvail(UART0_BASE)))
                {
                    val = UARTCharGetNonBlocking(UART0_BASE);
                    UARTCharPut(UART0_BASE, val);
                    if(val!= 0x0d)
                    { string[i++]=val;

                    }
                    else if(val== 0x0d)
                    {
                        string[i]='\0';
                        temp=1;
                    }
                }
            }
            temp=0;

            int x = 1;
            char first[8] = "\0";
            char second[8] = "\0";

            char* data = strtok(string, " ");
            while(data != NULL){
                if(x==1)
                    strcpy(first, data);

                else if(x == 2)
                    strcpy(second, data);



                else
                    timer = atoi(data);

                x = x+1;
                data = strtok(NULL, " ");
            }

            if(strstr(first, "timer")){
                    if(strstr(second, "start"))
                    {


                            while(timer>=0)
                            {
                                value = GPIO_PORTF_DATA_R;

                                if((value & 0x11) != 0x00){
                                    int u,w;
                                    for(int i=0; i<250; i++){
                                        u = floor(timer/10);
                                        GPIO_PORTB_DATA_R = digitPattern[u];   //display digits from 0 to 9
                                        GPIO_PORTA_DATA_R = 0x20;
                                        delayMs1(1);
                                        w = timer%10;
                                        GPIO_PORTB_DATA_R = digitPattern[w];   //display digits from 0 to 9
                                        GPIO_PORTA_DATA_R = 0x10;
                                        delayMs1(1);
                                    }
                                                                                        // delay 1 second between each digit

                                    timer--;
                                    while ((value & 0x11) == 0x01 || flag == 0){
                                        value = GPIO_PORTF_DATA_R;
                                        if((value & 0x11) == 0x10){
                                            flag = 1;
                                            break;
                                    }
                                   }
                                }
                                else{
                                    break;
                                }

                    }
            }

     }
    }

}
/* delay n milliseconds (16 MHz CPU clock) */

void delayMs1(int n)

{


        int i, j;
           for(i = 0 ; i < n; i++){
               value = GPIO_PORTF_DATA_R;
               if ((value & 0x11) == 0x01)
                   flag = 0;
               for(j = 0; j < 3180; j++) {} /* do nothing for 1 ms */
           }

    }

