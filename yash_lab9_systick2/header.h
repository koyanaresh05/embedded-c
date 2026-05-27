#ifndef HEADER_H_
#define HEADER_H_



#include <stdint.h>
#include <stdbool.h>
#include <./inc/tm4c123gh6pm.h>
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/systick.h>
#include <driverlib/sysctl.h>
#include <driverlib/uart.h>
#include <string.h>



#define SW1 (GPIO_PORTF_DATA_R&(1<<4))
#define SW2 (GPIO_PORTF_DATA_R&(1<<0))
#define LED_RED (GPIO_PORTF_DATA_R=0x02)
#define LED_BLUE (GPIO_PORTF_DATA_R=0x04)
#define LED_GREEN (GPIO_PORTF_DATA_R=0x08)
#define LED_WHITE (GPIO_PORTF_DATA_R=0x0E)
#define LED_DARK (GPIO_PORTF_DATA_R=0x00)
#define LED_YELLOW (GPIO_PORTF_DATA_R=0x0A)
#define LED_SKYBLUE (GPIO_PORTF_DATA_R=0x0C)
#define LED_OFF (GPIO_PORTF_DATA_R=0x00)
#define NUM0 (GPIO_PORTB_DATA_R=0x3F)
#define NUM1 (GPIO_PORTB_DATA_R=0x06)
#define NUM2 (GPIO_PORTB_DATA_R=0x5B)
#define NUM3 (GPIO_PORTB_DATA_R=0x4F)
#define NUM4 (GPIO_PORTB_DATA_R=0x66)
#define NUM5 (GPIO_PORTB_DATA_R=0x6D)
#define NUM6 (GPIO_PORTB_DATA_R=0x7D)
#define NUM7 (GPIO_PORTB_DATA_R=0x07)
#define NUM8 (GPIO_PORTB_DATA_R=0x7F)
#define NUM9 (GPIO_PORTB_DATA_R=0x6F)
#define PA4 (GPIO_PORTA_DATA_R=0x10) //0010 0000
#define PA5 (GPIO_PORTA_DATA_R=0x20)
#define PA6 (GPIO_PORTA_DATA_R=0x40)
#define PA7 (GPIO_PORTA_DATA_R=0x80)
//#define NUM[10] {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F}
#define DECIMAL 0x80


int printchar(char);
int printstring(char *);
void Sevensegment(int);
void delayMs(long);
void led_blink(long , long);
void reset_string(char *);
void perform_command(char *,bool *, bool *);


void Init_PortF(void);
void Init_PortAB(void);


void DisableInterrupts(void);
void EnableInterrupts(void);
void WaitForInterrupt(void);




void Init_PortF(void)
{
volatile unsigned long delay;


SYSCTL_RCGC2_R |= 0x00000020; /* 1) activate clock for Port F*/
delay = SYSCTL_RCGC2_R; /* allow time for clock to start */


GPIO_PORTF_LOCK_R = 0x4C4F434B; /* 2) unlock GPIO Port F */
GPIO_PORTF_CR_R = 0x1F; /* allow changes to PF4-0 */
GPIO_PORTF_AMSEL_R = 0x00; /* 3) disable analog on PF */
GPIO_PORTF_PCTL_R = 0x00000000; /* 4) PCTL GPIO on PF4-0 */
GPIO_PORTF_DIR_R = 0x0E; /* 5) PF4,PF0 in, PF3-1 out */
GPIO_PORTF_AFSEL_R = 0x00; /* 6) disable alt funct on PF7-0 */
GPIO_PORTF_PUR_R = 0x11; /* enable pull-up on PF0 and PF4 */ //always 1
GPIO_PORTF_DEN_R = 0x1F; /* 7) enable digital I/O on PF4-0 */



GPIO_PORTF_IS_R &= ~0x10; /* PF4 is edge-sensitive */
GPIO_PORTF_IBE_R &= ~0x10; /* PF4 is not both edges */
GPIO_PORTF_IEV_R &= ~0x10; /* PF4 falling edge event */


GPIO_PORTF_IS_R &= ~0x10; /* PF4 is edge-sensitive */
GPIO_PORTF_IBE_R &= ~0x10; /* PF4 is not both edges */
GPIO_PORTF_IEV_R &= ~0x10; /* PF4 falling edge event */



GPIO_PORTF_ICR_R = 0x10;
GPIO_PORTF_ICR_R |= 0x01;
GPIO_PORTF_IM_R |= 0x10; /* arm interrupt on PF4 */
GPIO_PORTF_IM_R |= 0x01; /* arm interrupt on PF0 */
NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF1FFFFF) | 0x00A00000;
NVIC_EN0_R = 0x40000000;


EnableInterrupts();


}



void Init_PortAB(void)
{
//volatile unsigned long delay;


SYSCTL_RCGC2_R |= 0x00000003; /* 1) activate clock for Port A,B */


GPIO_PORTB_LOCK_R = 0x4C4F434B; /* 2) unlock GPIO Port B */
GPIO_PORTB_CR_R = 0xFF; /* allow changes to PB7-0 */
GPIO_PORTB_AMSEL_R = 0x00; /* 3) disable analog on PB */
GPIO_PORTB_PCTL_R = 0x00000000; /* 4) PCTL GPIO on PBF7-0 */
GPIO_PORTB_DIR_R = 0xFF; /* 5) PB7-0 out */
GPIO_PORTB_AFSEL_R = 0x00; /* 6) disable alt funct on PB7-0 */
GPIO_PORTB_PUR_R = 0x00; /* enable pull-up on PB0 and PB4 */ //always 1
GPIO_PORTB_DEN_R = 0xFF; /* 7) enable digital I/O on PB7-0 */


GPIO_PORTA_LOCK_R |= 0x4C4F434B; /* 2) unlock GPIO Port A */
GPIO_PORTA_CR_R |= 0xF0; /* allow changes to PA7-4 */
GPIO_PORTA_AMSEL_R |= 0x00; /* 3) disable analog on PA */
GPIO_PORTA_PCTL_R |= 0x00000000; /* 4) PCTL GPIO on PA7-4 */
GPIO_PORTA_DIR_R |= 0xF0; /* 5) PA7-4 out */
GPIO_PORTA_AFSEL_R |= 0x00; /* 6) disable alt funct on PA7-4 */
GPIO_PORTA_PUR_R |= 0x00; /* enable pull-up on PA7-4 */ //always 1
GPIO_PORTA_DEN_R |= 0xF0; /* 7) enable digital I/O on PA7-4 */



}



int printchar(char val)
{
UARTCharPut(UART0_BASE, val);
}


int printstring(char *inputstr)
{
char *s=inputstr;
while(*s!=0)
{
printchar(*s);
//UARTCharPut(UART0_BASE, *s);
s++;
}


}


void Sevensegment(int digit)//int i for decimal or not...then if else add kr denge
{
switch (digit)
{
case 0: NUM0; break;
case 1: NUM1; break;
case 2: NUM2; break;
case 3: NUM3; break;
case 4: NUM4; break;
case 5: NUM5; break;
case 6: NUM6; break;
case 7: NUM7; break;
case 8: NUM8; break;
case 9: NUM9; break;
default : NUM1; break;
//delayMs(1);
}


}


void print_time(int time)
{ int d;
d=time%10;
time=time/10;
Sevensegment(d);
PA4;
delayMs(1);


d=time%10;
time=time/10;
Sevensegment(d);
PA5;
delayMs(1);


d=time%10;
time=time/10;


Sevensegment(d); //decimal
PA6;
delayMs(1);


d=time%10;
time=time/10;
Sevensegment(d);
PA7;
delayMs(1);


}



void perform_command(char *string_i,bool* start,bool* pause)
{


long delay=0 , iteration=0;



printstring("\t \t"); //so that "command read" appears to side of "given command"
printstring(string_i);



if((!strcmp(string_i,"ledonwhite")) || (!strcmp(string_i,"ledon")) )
{
LED_WHITE;
}
else if((!strcmp(string_i,"ledonred")))
{
LED_RED;
}
else if((!strcmp(string_i,"ledongreen")))
{
LED_GREEN;
}
else if((!strcmp(string_i,"ledonblue")))
{
LED_BLUE;
}
else if((!strcmp(string_i,"ledoffred")))
{
GPIO_PORTF_DATA_R &= 0xFD; // toggle LED
}
else if((!strcmp(string_i,"ledoffblue")))
{
GPIO_PORTF_DATA_R &= 0xFB; // toggle LED
}
else if((!strcmp(string_i,"ledoffgreen")))
{
GPIO_PORTF_DATA_R &= 0xF7; // toggle LED
}
else if ((!strcmp(string_i,"ledoffwhite")) || (!strcmp(string_i,"ledoff")) )
{
GPIO_PORTF_DATA_R &= 0xF1; // toggle LED
}
else if ((!strcmp(string_i,"ledblink")))
{
printstring("\n\r Please enter delay value");


while(1)
{
if(UARTCharsAvail(UART0_BASE))
{ char tmpchr = UARTCharGet(UART0_BASE);
printchar(tmpchr);
if((tmpchr <= 57) && (tmpchr >= 48))
{
delay=delay*10+(tmpchr-48);
}
else if(tmpchr==13)
{
break;
}
}
}


printstring("\n\r Please enter iteration value");
while(1)
{
if(UARTCharsAvail(UART0_BASE))
{ char tmpchr = UARTCharGet(UART0_BASE);
printchar(tmpchr);
if((tmpchr <= 57) && (tmpchr >= 48))
{
iteration=iteration*10+(tmpchr-48);
}
else if(tmpchr==13)
{
break;
}
}
}


led_blink(iteration, delay);
}
else if((!strcmp(string_i,"stopwatchstart")))
{
*start=1;
printstring("aa gya");
}
else if((!strcmp(string_i,"stopwatchstop")))
{
*start=0;
*pause=0;
}
else if((!strcmp(string_i,"stopwatchpause")))
{
*pause=1;
}
else if((!strcmp(string_i,"stopwatchresume")))
{
*pause=0;
}
else
{
printstring("\n\rCOMMAND NOT FOUND\n\r");
}


// printchar(start + 48);
//printchar(pause + 48);
}



/* to reset string after performing command*/
void reset_string(char *ptr)
{
int i;
for (i=0 ; i<=50 ; i++)
{
*ptr = 0;
ptr++;
}
}






/* delay n milliseconds (16 MHz CPU clock) */
void delayMs(long delay)
{
long i, j;
for(i = 0 ; i < delay; i++)
for(j = 0; j < 3180; j++) {__asm("nop");} /* do nothing for 1 ms */
}




void led_blink(long iteration , long delay)
{
long i=0;
for (i=0 ; i<=iteration ; i++)
{
GPIO_PORTF_DATA_R = 0x0E; /* turn on all LEDs */
delayMs(delay);
GPIO_PORTF_DATA_R = 0; /* turn off all LEDs */
delayMs(delay);


}


}



/*********** DisableInterrupts ***************
*
* disable interrupts
*
* inputs: none
* outputs: none
*/


void DisableInterrupts(void)
{
__asm (" CPSID I\n");
}


/*********** EnableInterrupts ***************
*
* emable interrupts
*
* inputs: none
* outputs: none
*/


void EnableInterrupts(void)
{
__asm (" CPSIE I\n");
}


/*********** WaitForInterrupt ************************
*
* go to low power mode while waiting for the next interrupt
*
* inputs: none
* outputs: none
*/


void WaitForInterrupt(void)
{
__asm (" WFI\n");
}



#endif /* HEADER_H_ */
