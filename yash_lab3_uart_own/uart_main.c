#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <tm4c123gh6pm.h>

#include "uart.h"


int main()
{
    int iport = 0;
    float ibaudrate = 115200;
    int iparity = 0;
    Init_UARTA(iport, ibaudrate, iparity);

    putString("Welcome to my UART");
    char string[30]="\0";
    int i;
    char *temp;
    Init_PortF();

    // Void UART_Read(int iport, char *pcbyte); functionality
    while(1)
    {
        i = 0;
        char val = 0;
        while((val != '\n') && (val !='\r')){
            switch(iport){
                case 0:
                    if(!(UART0_FR_R & (1 << 4))){ //true when receiver is not empty
                        val = UART0_DR_R;
                        string[i++] = val;
                        UART_Write(iport, val);
                        *temp = val;
                        temp++;

                    }
                    string[i] = '\0';
                    break;
                case 1:
                    if(!(UART1_FR_R & (1 << 4))){ //true when receiver is not empty
                        val = UART1_DR_R;
                        string[i++] = val;
                        UART_Write(iport, val);
                        *temp = val;
                        temp++;

                    }
                    string[i] = '\0';
                    break;
                case 2:
                    if(!(UART2_FR_R & (1 << 4))){ //true when receiver is not empty
                        val = UART2_DR_R;
                        string[i++] = val;
                        UART_Write(iport, val);
                        *temp = val;
                        temp++;

                    }
                    string[i] = '\0';
                    break;
                case 3:
                    if(!(UART3_FR_R & (1 << 4))){ //true when receiver is not empty
                        val = UART3_DR_R;
                        string[i++] = val;
                        UART_Write(iport, val);
                        *temp = val;
                        temp++;

                    }
                    string[i] = '\0';
                    break;
                case 4:
                    if(!(UART4_FR_R & (1 << 4))){ //true when receiver is not empty
                        val = UART4_DR_R;
                        string[i++] = val;
                        UART_Write(iport, val);
                        *temp = val;
                        temp++;

                    }
                    string[i] = '\0';
                    break;
                case 5:
                    if(!(UART5_FR_R & (1 << 4))){ //true when receiver is not empty
                        val = UART5_DR_R;
                        string[i++] = val;
                        UART_Write(iport, val);
                        *temp = val;
                        temp++;

                    }
                    string[i] = '\0';
                    break;
                case 6:
                    if(!(UART6_FR_R & (1 << 4))){ //true when receiver is not empty
                        val = UART6_DR_R;
                        string[i++] = val;
                        UART_Write(iport, val);
                        *temp = val;
                        temp++;

                    }
                    string[i] = '\0';
                    break;
                case 7:
                    if(!(UART7_FR_R & (1 << 4))){ //true when receiver is not empty
                        val = UART7_DR_R;
                        string[i++] = val;
                        UART_Write(iport, val);
                        *temp = val;
                        temp++;

                    }
                    string[i] = '\0';
                    break;
            }
        }
              processString(string);
    }


    return 0;
}
