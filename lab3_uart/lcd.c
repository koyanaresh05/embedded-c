#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "tm4c123gh6pm.h"
#include <string.h>

#include "lcd.h"
//#define LCD_CTRLP GPIO_PORTA
//#define LCD_DATAP GPIO_PORTB
//#define RS 0x20 // PORTA BIT5 mask
//#define RS 0x40 // PORTA BIT6 mask
//#define EN 0x80 // PORTA BIT7 mask
//#define HIGH 1
//#define LOW 0



void LCD_init(void){
SYSCTL_RCGCGPIO_R |= 0x01; //PORTA clock
SYSCTL_RCGCGPIO_R |= 0x02;
GPIO_PORTA_DIR_R |=0xE0; //PORTA controls RS,E and R/W
GPIO_PORTA_DEN_R |=0xE0;
GPIO_PORTB_DIR_R |=0xFF; //PORTB D0-D7
GPIO_PORTB_DEN_R |=0xFF; //PORTB D0-D7
LCD_Cmd(0x01); //clear display
LCD_Cmd(0x38); //8-bits,2 display lines, 5x7 font
LCD_Cmd(0x06); //increments automatically
LCD_Cmd(0x0F); //Turn on display
}

void LCD_Cmd(unsigned char command)
{
GPIO_PORTA_DATA_R = 0x00; //RS =0, E=0, RW=0
GPIO_PORTB_DATA_R = command;
GPIO_PORTA_DATA_R = 0x80; //E=1 to secure command
delay_micro(0);
GPIO_PORTA_DATA_R =0x00;
if(command < 4)
    delay_milli(2);
else
    delay_micro(37);


}

void LCD_Data(unsigned char data)
{
    GPIO_PORTA_DATA_R  =0x40; //RS=1, E=0,RW=0
    GPIO_PORTB_DATA_R  =data;
    GPIO_PORTA_DATA_R |=0x80;
    GPIO_PORTA_DATA_R  = 0x00;
    delay_micro(0);

}

void LCD_String(char *command)
{
    delay_milli(500);
    while (*command != '\0'){
            LCD_Data(*command);
            delay_milli(1);
            command++;
        }
    delay_milli(500);
}
void delay_milli(int n){
int i,j;
for(i=0;i<n;i++)
for(j=0;j<3180;j++)
{}
}

void delay_micro(int n){
int i,j;
for(i=0;i<n;i++)
for(j=0;j<3;j++)
{}
}
