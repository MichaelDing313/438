/*
 * File:   main.c
 * Author: Michael
 *
 * Created on March 19, 2017, 1:00 PM
 */

#include "configBits.c"
#include <xc.h>
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