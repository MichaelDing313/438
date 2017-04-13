/* 
 * File:   main.c
 * Author: JamesWu
 *
 * Created on March 19, 2017, 12:48 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "configBits.c"
#include "get_coord.h"
#include "get_control.h"
#include <xc.h>
<<<<<<< HEAD
inline void n10ms_delay(int n){
    for(int i=n; i > 0; i--){
        __delay_ms(10);
    }
    
}
void main(void) {
    
    ADCON0bits.ADON = 0;
    LATB = 0xFF;
    TRISB = 0x00;
    ANSELB = 0x00;
    
    servo_init();
}

void interrupt timers(void){
    if(PIR4bits.TMR6IF && PIE4bits.TMR6IE){
        // Timer 6 interrupt, 2.5ms passed, turn off timer 4 
        // So PWM output is off
        T4CONbits.T4ON = 0;
        // Clear interrupt flag
        PIR4bits.TMR6IF = 0;
    }
    if(PIR4bits.TMR2IF && PIE4bits.TMR2IE){
        // Timer 2 reset, 20ms passed, reset timer 4 and 6
        T4CONbits.T4ON = 1;
        T6CONbits.T6ON = 1;
        // Clear interrupt flag
        PIR4bits.TMR2IF = 0;
    }
}
=======
int Kpx = 1;
int Kix = 0;
int Kdx = 0;
int Kpy = 1;
int Kiy = 0;
int Kdy = 0; 
int int_error_x = 0;
int int_error_y = 0;
int last_error_x = 0;
int last_error_y = 0;
int target_x = 0;
int target_y = 0;

int main(void)
{
  int curr_x, curr_y, control_x, control_y;
  for (;;)
  {
  curr_x, curr_y = get_coord();
  control_x, control_y = get_control(curr_x, curr_y);
  }
    return 0;
}



>>>>>>> 21b06e0242ab7f4107e502f3a949817ae44548d4
