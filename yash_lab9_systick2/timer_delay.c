#include <stdint.h>
#include <stdbool.h>
#include "header.h"
int time;
bool start=0;
bool pause=0;



void switch_handler(void);
void SysTick_Handler(void);


int main (void)
{ int s,ms,i,j;
char temp[50];
char tempchar=0;
char prevchar;
char string_i[50];
int curr = 0 ;




SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);


GPIOPinConfigure(GPIO_PA0_U0RX);
GPIOPinConfigure(GPIO_PA1_U0TX);
GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);


UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));





/* Configure SysTick */
//NVIC_ST_RELOAD_R = 16000000-1; /*(<--for1sdelay) reload with number of clocks per second i.e.(clkfreq*Time delay)-1*/
NVIC_ST_RELOAD_R = 16000000*0.01-1; /*(<--for 0.01s delay.....after 0.01s systickhandler will be called)*/
NVIC_ST_CTRL_R = 7; /* enable SysTick interrupt, use system clock */



Init_PortF();
Init_PortAB();



time=0;
while(1)
{ if(time==10000)
{ time=0;
}


WaitForInterrupt();
print_time(time);




while(UARTCharsAvail(UART0_BASE))
{ prevchar=tempchar;
tempchar = UARTCharGet(UART0_BASE);
if(tempchar!= 9) //not to print tab as it creates confusion because of 8 spaces
{
UARTCharPut(UART0_BASE, tempchar);
}
if(tempchar == 13) //enter is pressed
{
string_i[curr]=0;
perform_command(string_i,&start,&pause);
curr = 0;
printchar('\n');
printchar('\r');
printchar('=>');
reset_string(string_i); // string="";


}


else if(tempchar == 8) //backspace
{
if (curr > 0 && ((prevchar<=90 && prevchar>=65)||(prevchar<=122&& prevchar>=97)))
curr--; //current pos should only be decremented if prev char was an alphabet


string_i[curr] = 0; /*if prev char was alphabet then only prev will be overwritten otherwise current positon becomes null
which will be overwritten in next alphabet or enter press*/



printchar(32); //last char is now overwritten with space(ASCII value 32) , so it appears that last char is not there
printchar(8); // backspace so current position of cursor is on 2nd last char


// summary data| is converted to dat|





}




else if(tempchar<= 90 && tempchar>=65)
{
string_i[curr]= tempchar+'a'-'A';
curr++;
}


else if(tempchar<=122 && tempchar>=97)
{
string_i[curr] = tempchar;
curr++;
}


else
{ string_i[curr]=0; //no use since enter condition itself performs that action


//no data is stored , since character entered is not an alphabet and curr is not modified


}



if(curr==50)
{
curr=0;
reset_string(string_i);
}
}


}
}


void SysTick_Handler(void)
{ int s,i,size;
char temp[10];
char tmp[10];


if(start==1 && pause==0)
{
time++;
}
else if(start==1 && pause==1)
{
time=time;
}
else //start = 0 i.e. stop
{ pause=0; // necessary to be done so that after start it doesnt go on pause state automatically
time=0;
}





/*following code is to display stopwatch in serial terminal
 i=0;
size=0;
s=time;
while(s!=0)
{ temp[i]=(s%10)+48;
i++;
s=s/10;
}
temp[i]=' ';
temp[i+1]=0;
while(temp[size]!=0)
{ size++;


}
for(i=size-1,s=0;i>=0;i--,s++)
{
tmp[s]=temp[i];
}
//tmp[s+1]=' ';
tmp[s+1]=0;



printstring(tmp);*/
}


void switch_handler(void)
{
volatile int readback;



if(SW1!=1 && SW2!=0)
{
start = !start;


}



if(SW2!=1 && SW1!=0)
{
pause=!pause;


}


//print_time(time);



GPIO_PORTF_ICR_R |= 0x11;
// readback = GPIO_PORTF_ICR_R; /* a read to force clearing of interrupt flag */
// readback = readback;
//GPIO_PORTF_ICR_R |= 0x01;
readback = GPIO_PORTF_ICR_R; /* a read to force clearing of interrupt flag */
readback = readback;
}
