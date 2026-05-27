#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <tm4c123gh6pm.h>

#define  LED_OFF    (GPIO_PORTF_DATA_R = 0x00)
#define  LED_RED    (GPIO_PORTF_DATA_R = 0x02)
#define  LED_BLUE   (GPIO_PORTF_DATA_R = 0x04)
#define  LED_GREEN  (GPIO_PORTF_DATA_R = 0x08)
#define  LED_WHITE  (GPIO_PORTF_DATA_R = 0x0E)

#define UART_PARTITY_NONE  0
#define UART_PARTITY_ODD   1
#define UART_PARTITY_EVEN  2
#define UART_PARTITY_MARK  3  //1,2,7
#define UART_PARTITY_SPACE 4  //1,7

#define RXFE 4
#define BUSY 3
#define TXFF 5

char color[8]  = "white";
int flag = 0;
int value;
int iPort;
//Initialize the UART functionality in port A
void Init_UARTA(int iport, float baudrate, int iparity){
    iPort = iport;
    switch(iport){
    case 0:
           //Activate UART0
            SYSCTL_RCGCUART_R |= 0x01;
            //Activate PORTA
            SYSCTL_RCGCGPIO_R |= 0x01;
            // Disable the UART0
            UART0_CTL_R |= UART_CTL_UARTEN;
            // Set the baud rate to 115200
            float w;
            w = 1000000;
            float x = w /  baudrate;
            int y = (x);
            float z = (x-y)*64;
            int r = z;
            UART0_IBRD_R = y;  /* IBRD = int(16,000,000 / (16 * 115200)) = int(8.68) */
            if((z-r)>=0.5)
                UART0_FBRD_R = r+1; /* FBRD = round(0.68 * 64 ) = 44 */
            else
                UART0_FBRD_R = r;
            // line control value for 1 stop bit, no FIFO, no interrupt, no parity, and 8-bit data size
            switch(iparity){
            case 0:
                UART0_LCRH_R |= 0x70;
                break;
            case 1:
                UART0_LCRH_R |= 0x72;
                break;
            case 2:
                UART0_LCRH_R |= 0x76;
                break;
            case 3:
                UART0_LCRH_R |= 0x72;
                break;
            case 4:
                UART0_LCRH_R |= 0xF6;
                break;
            default:
                UART0_LCRH_R |= 0xF2;
            }

            //Set TxE and RxE bits in UARTCTL register to enable the transmitter and receiver of UART0.
            UART0_CTL_R |= UART_CTL_TXE | UART_CTL_RXE;
            //Make PA0 and PA1 pins to be used as Digital I/O
            GPIO_PORTA_DEN_R |= 0x03;
            //Select the alternate functions of PA0 (RxD) and PA1 (TxD)
            GPIO_PORTA_AFSEL_R |= 0x03;
            //Configure PA0 and PA1 pins for UART function
            GPIO_PORTA_PCTL_R |= 0x11;
            // diabale analog functionaliuty
            GPIO_PORTA_AMSEL_R = 0;
            break;

    case 1:
           //Activate UART1
            SYSCTL_RCGCUART_R |= 0x02;
            //Activate PORTB
            SYSCTL_RCGCGPIO_R |= 0x02;
            // Disable the UART1
            UART1_CTL_R |= UART_CTL_UARTEN;
            // Set the baud rate to 115200
            float w1;
            w1 = 1000000;
            float x1 = w1 /  baudrate;
            int y1 = (x1);
            float z1 = (x1-y1)*64;
            int r1 = z1;
            UART1_IBRD_R = y1;  /* IBRD = int(16,000,000 / (16 * 115200)) = int(8.68) */
            if((z1-r1)>=0.5)
                UART1_FBRD_R = r1+1; /* FBRD = round(0.68 * 64 ) = 44 */
            else
                UART1_FBRD_R = r1;
            // line control value for 1 stop bit, no FIFO, no interrupt, no parity, and 8-bit data size
            switch(iparity){
            case 0:
                UART1_LCRH_R |= 0x70;
                break;
            case 1:
                UART1_LCRH_R |= 0x02;
                break;
            case 2:
                UART1_LCRH_R |= 0x06;
                break;
            case 3:
                UART1_LCRH_R |= 0x72;
                break;
            case 4:
                UART1_LCRH_R |= 0xF6;
                break;
            default:
                UART1_LCRH_R |= 0x70;
            }

            //Set TxE and RxE bits in UARTCTL register to enable the transmitter and receiver of UART1.
            UART1_CTL_R |= 0x0301;
            //Make PB0 and PB1 pins to be used as Digital I/O
            GPIO_PORTB_DEN_R |= 0x03;
            //Select the alternate functions of PC4 (RxD) and PC5 (TxD)
            GPIO_PORTB_AFSEL_R |= 0x03;
            //Configure PB0 and PB1 pins for UART function
            GPIO_PORTB_PCTL_R |= 0x11;
            // diabale analog functionaliuty
            GPIO_PORTB_AMSEL_R = 0;
            break;


    case 2:
               //Activate UART2
                SYSCTL_RCGCUART_R |= 0x04;
                //Activate PORTD
                SYSCTL_RCGCGPIO_R |= 0x08;
                // Disable the UART0
                UART2_CTL_R |= UART_CTL_UARTEN;
                // Set the baud rate to 115200
                float w2;
                w2 = 1000000;
                float x2 = w2 /  baudrate;
                int y2 = (x2);
                float z2 = (x2-y2)*64;
                int r2 = z2;
                UART2_IBRD_R = y2;  /* IBRD = int(16,000,000 / (16 * 115200)) = int(8.68) */
                if((z2-r2)>=0.5)
                    UART2_FBRD_R = r2+1; /* FBRD = round(0.68 * 64 ) = 44 */
                else
                    UART2_FBRD_R = r2;
                // line control value for 1 stop bit, no FIFO, no interrupt, no parity, and 8-bit data size
                switch(iparity){
                case 0:
                    UART2_LCRH_R |= 0x70;
                    break;
                case 1:
                    UART2_LCRH_R |= 0x02;
                    break;
                case 2:
                    UART2_LCRH_R |= 0x06;
                    break;
                case 3:
                    UART2_LCRH_R |= 0x72;
                    break;
                case 4:
                    UART2_LCRH_R |= 0xF6;
                    break;
                default:
                    UART2_LCRH_R |= 0x70;
                }

                //Set TxE and RxE bits in UARTCTL register to enable the transmitter and receiver of UART2.
                UART2_CTL_R |= UART_CTL_TXE | UART_CTL_RXE;
                //Make PD7 and PD6 pins to be used as Digital I/O
                GPIO_PORTD_DEN_R |= 0xC0;
                //Select the alternate functions of PA0 (RxD) and PA1 (TxD)
                GPIO_PORTD_AFSEL_R |= 0xC0;
                //Configure PD7 and PD6 pins for UART function
                GPIO_PORTD_PCTL_R |= 0x11000000;
                // diabale analog functionaliuty
                GPIO_PORTD_AMSEL_R = 0;
                break;


    case 3:
           //Activate UART3
            SYSCTL_RCGCUART_R |= 0x08;
            //Activate PORTC
            SYSCTL_RCGCGPIO_R |= 0x04;
            // Disable the UART0
            UART3_CTL_R |= UART_CTL_UARTEN;
            // Set the baud rate to 115200
            float w3;
            w3 = 1000000;
            float x3 = w3 /  baudrate;
            int y3 = (x3);
            float z3 = (x3-y3)*64;
            int r3 = z3;
            UART3_IBRD_R = y3;  /* IBRD = int(16,000,000 / (16 * 115200)) = int(8.68) */
            if((z3-r3)>=0.5)
                UART3_FBRD_R = r3+1; /* FBRD = round(0.68 * 64 ) = 44 */
            else
                UART3_FBRD_R = r3;
            // line control value for 1 stop bit, no FIFO, no interrupt, no parity, and 8-bit data size
            switch(iparity){
            case 0:
                UART3_LCRH_R |= 0x70;
                break;
            case 1:
                UART3_LCRH_R |= 0x02;
                break;
            case 2:
                UART3_LCRH_R |= 0x06;
                break;
            case 3:
                UART3_LCRH_R |= 0x72;
                break;
            case 4:
                UART3_LCRH_R |= 0xF6;
                break;
            default:
                UART3_LCRH_R |= 0x70;
            }

            //Set TxE and RxE bits in UARTCTL register to enable the transmitter and receiver of UART3.
            UART3_CTL_R |= UART_CTL_TXE | UART_CTL_RXE;
            //Make PC6 and PC7 pins to be used as Digital I/O
            GPIO_PORTC_DEN_R |= 0xC0;
            //Select the alternate functions of PA0 (RxD) and PA1 (TxD)
            GPIO_PORTC_AFSEL_R |= 0xC0;
            //Configure PC6 and PC7 pins for UART function
            GPIO_PORTC_PCTL_R |= 0x11000000;
            // diabale analog functionaliuty
            GPIO_PORTC_AMSEL_R = 0;
            break;


    case 4:
           //Activate UART4
            SYSCTL_RCGCUART_R |= 0x10;
            //Activate PORTC
            SYSCTL_RCGCGPIO_R |= 0x04;
            // Disable the UART0
            UART4_CTL_R |= UART_CTL_UARTEN;
            // Set the baud rate to 115200
            float w4;
            w4 = 1000000;
            float x4 = w4 /  baudrate;
            int y4 = (x4);
            float z4 = (x4-y4)*64;
            int r4 = z4;
            UART4_IBRD_R = y4;  /* IBRD = int(16,000,000 / (16 * 115200)) = int(8.68) */
            if((z4-r4)>=0.5)
                UART4_FBRD_R = r4+1; /* FBRD = round(0.68 * 64 ) = 44 */
            else
                UART4_FBRD_R = r4;
            // line control value for 1 stop bit, no FIFO, no interrupt, no parity, and 8-bit data size
            switch(iparity){
            case 0:
                UART4_LCRH_R |= 0x70;
                break;
            case 1:
                UART4_LCRH_R |= 0x02;
                break;
            case 2:
                UART4_LCRH_R |= 0x06;
                break;
            case 3:
                UART4_LCRH_R |= 0x72;
                break;
            case 4:
                UART4_LCRH_R |= 0xF6;
                break;
            default:
                UART4_LCRH_R |= 0x70;
            }

            //Set TxE and RxE bits in UARTCTL register to enable the transmitter and receiver of UART4.
            UART4_CTL_R |= UART_CTL_TXE | UART_CTL_RXE;
            //Make PC4 and PC5 pins to be used as Digital I/O
            GPIO_PORTC_DEN_R |= 0x30;
            //Select the alternate functions of PA0 (RxD) and PA1 (TxD)
            GPIO_PORTC_AFSEL_R |= 0x30;
            //Configure PC4 and PC% pins for UART function
            GPIO_PORTC_PCTL_R |= 0x00110000;
            // diabale analog functionaliuty
            GPIO_PORTC_AMSEL_R = 0;
            break;


    case 5:
           //Activate UART5
            SYSCTL_RCGCUART_R |= 0x20;
            //Activate PORTE
            SYSCTL_RCGCGPIO_R |= 0x10;
            // Disable the UART0
            UART5_CTL_R |= UART_CTL_UARTEN;
            // Set the baud rate to 115200
            float w5;
            w5 = 1000000;
            float x5 = w5 /  baudrate;
            int y5 = (x5);
            float z5 = (x5-y5)*64;
            int r5 = z5;
            UART5_IBRD_R = y5;  /* IBRD = int(16,000,000 / (16 * 115200)) = int(8.68) */
            if((z5-r5)>=0.5)
                UART5_FBRD_R = r5+1; /* FBRD = round(0.68 * 64 ) = 44 */
            else
                UART5_FBRD_R = r5;
            // line control value for 1 stop bit, no FIFO, no interrupt, no parity, and 8-bit data size
            switch(iparity){
            case 0:
                UART5_LCRH_R |= 0x70;
                break;
            case 1:
                UART5_LCRH_R |= 0x02;
                break;
            case 2:
                UART5_LCRH_R |= 0x06;
                break;
            case 3:
                UART5_LCRH_R |= 0x72;
                break;
            case 4:
                UART5_LCRH_R |= 0xF6;
                break;
            default:
                UART5_LCRH_R |= 0x70;
            }

            //Set TxE and RxE bits in UARTCTL register to enable the transmitter and receiver of UART5
            UART5_CTL_R |= UART_CTL_TXE | UART_CTL_RXE;
            //Make PE4 and PE5 pins to be used as Digital I/O
            GPIO_PORTE_DEN_R |= 0x30;
            //Select the alternate functions of PA0 (RxD) and PA1 (TxD)
            GPIO_PORTE_AFSEL_R |= 0x30;
            //Configure PE4 and PE5 pins for UART function
            GPIO_PORTE_PCTL_R |= 0x00110000;
            // diabale analog functionaliuty
            GPIO_PORTE_AMSEL_R = 0;
            break;


    case 6:
           //Activate UART6
            SYSCTL_RCGCUART_R |= 0x40;
            //Activate PORTD
            SYSCTL_RCGCGPIO_R |= 0x08;
            // Disable the UART0
            UART6_CTL_R |= UART_CTL_UARTEN;
            // Set the baud rate to 115200
            float w6;
            w6 = 1000000;
            float x6 = w6 /  baudrate;
            int y6 = (x6);
            float z6 = (x6-y6)*64;
            int r6 = z6;
            UART6_IBRD_R = y6;  /* IBRD = int(16,000,000 / (16 * 115200)) = int(8.68) */
            if((z6-r6)>=0.5)
                UART1_FBRD_R = r6+1; /* FBRD = round(0.68 * 64 ) = 44 */
            else
                UART1_FBRD_R = r6;
            // line control value for 1 stop bit, no FIFO, no interrupt, no parity, and 8-bit data size
            switch(iparity){
            case 0:
                UART6_LCRH_R |= 0x70;
                break;
            case 1:
                UART6_LCRH_R |= 0x02;
                break;
            case 2:
                UART6_LCRH_R |= 0x06;
                break;
            case 3:
                UART6_LCRH_R |= 0x72;
                break;
            case 4:
                UART6_LCRH_R |= 0xF6;
                break;
            default:
                UART6_LCRH_R |= 0x70;
            }

            //Set TxE and RxE bits in UARTCTL register to enable the transmitter and receiver of UART6.
            UART6_CTL_R |= UART_CTL_TXE | UART_CTL_RXE;
            //Make PD4 and PD5 pins to be used as Digital I/O
            GPIO_PORTD_DEN_R |= 0x30;
            //Select the alternate functions of PA0 (RxD) and PA1 (TxD)
            GPIO_PORTD_AFSEL_R |= 0x30;
            //Configure PD4 and PD5 pins for UART function
            GPIO_PORTD_PCTL_R |= 0x00110000;
            // diabale analog functionaliuty
            GPIO_PORTD_AMSEL_R = 0;
            break;


    case 7:
           //Activate UART7
            SYSCTL_RCGCUART_R |= 0x80;
            //Activate PORTE
            SYSCTL_RCGCGPIO_R |= 0x10;
            // Disable the UART0
            UART7_CTL_R |= UART_CTL_UARTEN;
            // Set the baud rate to 115200
            float w7;
            w7 = 1000000;
            float x7 = w7 /  baudrate;
            int y7 = (x7);
            float z7 = (x7-y7)*64;
            int r7 = z7;
            UART7_IBRD_R = y7;  /* IBRD = int(16,000,000 / (16 * 115200)) = int(8.68) */
            if((z7-r7)>=0.5)
                UART7_FBRD_R = r7+1; /* FBRD = round(0.68 * 64 ) = 44 */
            else
                UART7_FBRD_R = r7;
            // line control value for 1 stop bit, no FIFO, no interrupt, no parity, and 8-bit data size
            switch(iparity){
            case 0:
                UART7_LCRH_R |= 0x70;
                break;
            case 1:
                UART7_LCRH_R |= 0x02;
                break;
            case 2:
                UART7_LCRH_R |= 0x06;
                break;
            case 3:
                UART7_LCRH_R |= 0x72;
                break;
            case 4:
                UART7_LCRH_R |= 0xF6;
                break;
            default:
                UART7_LCRH_R |= 0x70;
            }

            //Set TxE and RxE bits in UARTCTL register to enable the transmitter and receiver of UART7.
            UART7_CTL_R |= UART_CTL_TXE | UART_CTL_RXE;
            //Make PE0 and PE1 pins to be used as Digital I/O
            GPIO_PORTE_DEN_R |= 0x03;
            //Select the alternate functions of PA0 (RxD) and PA1 (TxD)
            GPIO_PORTE_AFSEL_R |= 0x03;
            //Configure PE0 and PE1 pins for UART function
            GPIO_PORTE_PCTL_R |= 0x11;
            // diabale analog functionaliuty
            GPIO_PORTE_AMSEL_R = 0;
            break;

    }


}

//Initialize the PORT F
void Init_PortF(void)
{

    SYSCTL_RCGC2_R |= 0x00000020;     /* 1) activate clock for Port F */
    GPIO_PORTF_LOCK_R = 0x4C4F434B;   /* 2) unlock GPIO Port F */
    GPIO_PORTF_CR_R = 0x1F;           /* allow changes to PF4-0 */
    GPIO_PORTF_AMSEL_R = 0x00;        /* 3) disable analog on PF */
    GPIO_PORTF_PCTL_R = 0x00000000;   /* 4) PCTL GPIO on PF4-0 */
    GPIO_PORTF_DIR_R = 0x0E;          /* 5) PF4,PF0 in, PF3-1 out */
    GPIO_PORTF_AFSEL_R = 0x00;        /* 6) disable alt funct on PF7-0 */
    GPIO_PORTF_PUR_R = 0x11;          /* enable pull-up on PF0 and PF4 */ //always 1
    GPIO_PORTF_DEN_R = 0x1F;          /* 7) enable digital I/O on PF4-0 */
 }

//provides delay of n milli secs
void delayMs(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++){
        value = GPIO_PORTF_DATA_R;
                if ((value & 0x11) == 0x01)
                    break;
        for(j = 0; j < 3180; j++) {}   /* do nothing for 1 ms */
    }
}


//Writes the charecter c on the terminal
void UART_Write(int iport, char c){

    switch(iport){
        case 0:
            while ((UART0_FR_R & (1 << BUSY))); //The UART is busy transmitting data. This bit remains set untilthe complete byte, including all stop bits, has been sent fromthe shift register.
            UART0_DR_R = c;
            break;
        case 1:
            while ((UART1_FR_R & (1 << BUSY)));
            UART1_DR_R = c;
            break;
        case 2:
            while ((UART2_FR_R & (1 << BUSY)));
            UART2_DR_R = c;
            break;
        case 3:
            while ((UART3_FR_R & (1 << BUSY)));
            UART3_DR_R = c;
            break;
        case 4:
            while ((UART4_FR_R & (1 << BUSY)));
            UART4_DR_R = c;
            break;
        case 5:
            while ((UART5_FR_R & (1 << BUSY)));
            UART5_DR_R = c;
            break;
        case 6:
            while ((UART6_FR_R & (1 << BUSY)));
            UART6_DR_R = c;
            break;
        case 7:
            while ((UART7_FR_R & (1 << BUSY)));
            UART7_DR_R = c;
            break;
        default:
            while ((UART0_FR_R & (1 << BUSY)));
            UART0_DR_R = c;
        }
}

// Writes string s on the terminal
void putString(char * s){

    while (*s != '\0'){
        UART_Write(iPort, *s);
        s++;
    }
    UART_Write(iPort, '\n'); // to go next line
    UART_Write(iPort, '\r');// for going to the initial point of next line
    return;
}


// processes the string with * inplace of space and takes the arguments separate in the blink functionality
void processString(char * str){
    int x = 1;
            char first[8] = "\0";
            char second[8] = "\0";
            char third[8] = "\0";
            int  speed = 1200;
            char* data = strtok(str, " ");
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

          else {
              putString("Command Not Found\n\n\r Write one from the following: \n\r 1. led on  (default is white)\n\r 2. led off   \n\r 3. led toggle (recent color will on or off) \n\r 4. led color  [optional colour: default all] \n\r 5. led blink [optinal color: all, default: white] [speed (# of on or off in 1 minute )]\n\r");
    }
}


