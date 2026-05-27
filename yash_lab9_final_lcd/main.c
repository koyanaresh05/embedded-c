#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "tm4c123gh6pm.h"
#include <string.h>

#include "lcd.h"



int main(){
    LCD_init();



    LCD_Cmd(0x01);
    LCD_Cmd(0x80);
    LCD_String("**** Hello ****");
    LCD_Cmd(0xC0);
    LCD_String(" Yashash Jain ");

}




