#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "inc/tm4c123gh6pm.h"
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/sysctl.h>
#include <driverlib/uart.h>
#include <string.h>

#include "lcd.h"
#define  LED_RED    (GPIO_PORTF_DATA_R = 0x02)
#define  LED_BLUE   (GPIO_PORTF_DATA_R = 0x04)
#define  LED_GREEN  (GPIO_PORTF_DATA_R = 0x08)
#define  LED_WHITE  (GPIO_PORTF_DATA_R = 0x0E)
#define  LED_OFF    (GPIO_PORTF_DATA_R = 0x00)

void delayMs(int n);
unsigned int value;

int main()
{

    unsigned int  temp = 0, i,  flag=0;
    char val;
    char color[8]  = "white";
    char string[30]="\0";
    SYSCTL_RCGC2_R   |= 0x00000020;   /* enable clock to GPIOF */
    GPIO_PORTF_LOCK_R = 0x4C4F434B; /* unlock commit register */
    GPIO_PORTF_CR_R   = 0x01;         /* make PORTF0 configurable */
    GPIO_PORTF_DIR_R  = 0x0E;        /* set PORTF1 pin as output (LED) pin *//* and PORTF0 as input, SW2 is on PORTF0 */
    GPIO_PORTF_DEN_R  = 0x1F;        /* set PORTF pins 1-0 as digital pins */
    GPIO_PORTF_PUR_R  = 0x11;        /* enable pull up for pin 0 */


    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));



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
                if(val!= 0x0d)   //when enter is not press
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
        LCD_init();
            LCD_Cmd(0x01);
            LCD_Cmd(0x80);
            LCD_String(string);
        int x = 1;
        char first[8] = "\0";
        char second[8] = "\0";
        char third[8] = "\0";
        int  speed = 1200;
        char* data = strtok(string, " ");
        while(data != NULL){
            if(x==1)
                strcpy(first, data);

            else if(x == 2)
                strcpy(second, data);

            else if(x == 3)
                strcpy(third, data);

            else
                speed = atoi(data);

            x = x+1;
            data = strtok(NULL, " ");
        }

        if(strstr(first, "led")){
            if(strstr(second, "on"))
            {
                LED_WHITE;
                flag=1;
                strcpy(color, "white");
            }
            else if(strstr(second, "off"))
            {
                LED_OFF;
                flag=0;
            }

            else if(strstr(second, "toggle"))
            {
                if(flag == 0)
                {
                    if(strstr(color, "white")){
                        LED_WHITE;
                        flag = 1;
                    }
                    else if(strstr(color, "red")){
                        LED_RED;
                        flag = 1;
                    }
                    else if(strstr(color, "blue")){
                        LED_BLUE;
                        flag = 1;
                    }
                    else if(strstr(color, "green")){
                        LED_GREEN;
                        flag = 1;
                    }
                    else{
                        LED_WHITE;
                        flag = 1;

                    }

                }
                else
                {
                    LED_OFF;
                    flag=0;

                }
            }

            else if(strstr(second, "color")){
                if(strstr(third, "white")){
                    LED_WHITE;


                }
                else if(strstr(third, "red")){
                    LED_RED;


                }
                else if(strstr(third, "blue")){
                    LED_BLUE;


                }
                else if(strstr(third, "green")){
                    LED_GREEN;

                }
                else
                    LED_WHITE;
                flag = 1;
                strcpy(color, third);
            }



            else if(strstr(second, "blink"))
            {
                int x = 0;
                int y = speed;
                while(x<y)
                    {


                        if(strstr(third, "white")){
                            LED_WHITE;
                        }
                        else if(strstr(third, "red")){
                            LED_RED;

                        }
                        else if(strstr(third, "blue")){
                            LED_BLUE;

                        }
                        else if(strstr(third, "green")){
                            LED_GREEN;

                        }
                        else
                            LED_WHITE;

                        strcpy(color, third);
                        delayMs(60000/(y*2));
                        LED_OFF;
                        delayMs(60000/(y*2));
                        x = x+1;

            }

           }
        }

    }
    return 0;
}


void delayMs(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++){
        value = GPIO_PORTF_DATA_R;
        if ((value & 0x11) == 0x01)
            break;
        for(j = 0; j < 3180; j++) {} /* do nothing for 1 ms */
    }
}
