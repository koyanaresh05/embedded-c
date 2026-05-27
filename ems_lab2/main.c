#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "tm4c123gh6pm.h"
#include <string.h>

#include "lcd.h"
#include "keypad.h"



int main(void)
{
unsigned char key;

keypad_init();
LCD_init();

while(1)
{
LCD_Cmd(0x80); /* LCD cursor location */

key = keypad_getkey(); /* read the keypad */
if (key != 0)
{ /* if a key is pressed */
LCD_Data(key); /* display the key label */
}
else
LCD_Data(' ');

delay_milli(20); /* wait for a while */
}
}



