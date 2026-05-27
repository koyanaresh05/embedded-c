#include <stdint.h>
#include <math.h>
#include "tm4c123gh6pm.h"

#include "pwm_motor.h"
#include "ADC.h"

unsigned char digitPattern[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};  //common cathode
unsigned char digitPattern1[] = {0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0x7D, 0x87, 0xFF, 0xEF};  //common cathode

void delayMs(int n);
int main(void)
{
    PWM_Init();
    ADC0_Init();
    PORTA_Init();
    PORTB_Init();
    //clockwise_rotation();

    int z = 4999;
    float temp;
    int temp2;
    volatile int result;
    float x,r;

    while(1){
        ADC0_PSSI_R |= 8;               //start a conversion sequence 3
        while((ADC0_RIS_R & 8) == 0);   //wait for conversion complete
        result = ADC0_SSFIFO3_R;        //read conversion result
        x = ((result*3.3)/4095);

        int u,w,s;
        u = x;
        float t = u;
        r = (x-t)*100;
        int m = r;
        s = (m)%10;
        for(int i=0; i<250; i++){
           GPIO_PORTB_DATA_R = digitPattern1[u];   //display digits from 0 to 9
           GPIO_PORTA_DATA_R = 0x20;
           delayMs(1);

           w = (x-u)*10;
           if(s >= 5)
               w = w+1;
           else
               w = w;
           GPIO_PORTB_DATA_R = digitPattern[w];   //display digits from 0 to 9
           GPIO_PORTA_DATA_R = 0x10;
           delayMs(1);
        }

        ADC0_ISC_R = 8;        /* clear completion flag */

        temp =(((result)/4095.0)*4999.0);
        temp2 = (int)temp;
        z = 4999-temp2;
        PWM1_1_CMPA_R=z;                //if PWM1_3_CMPA_R = 0 meand 100% duty cycle (fast speed)
        //delayMs(1000);
    }





}



