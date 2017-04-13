/*
 * File:   servo.c
 * Author: Michael
 *
 * Created on April 9, 2017, 7:33 PM
 */


#include <xc.h>
#include "servo.h"

void servo_init(){
    // test pwm stuff
        
    // Timer 4 configurations PWM will run off Timer 4
    // Pre-scale 8, post-scale 5
    T4CON = 0b00110100;
    // Clock source, Fosc/4, final freq: 400khz
    T4CLKCON = 0b00000001;
    // Timer4 operation mode: free running
    T4HLT = 0b00000000;
    // Set time tm4 is on, doesnt matter since rolling over
    T4PR = 0b01111111;

    // CCP1 and 2 in PWM Mode, off for now
    CCP1CON = 0b00001100;
    CCP2CON = 0b00001100;
    // All CCP use Timer4 
    CCPTMRS = 0b10101010;
    // Set PWM width for now
    CCPR1H = 0b00000010; // 
    CCPR1L = 0b00000000;
    CCPR2H = 0b00000010; // 
    CCPR2L = 0b00000000;
    
    // Set timer 6 to activate every 2.5ms to stop the PWM, so only one cycle
    // of the pulse is sent
    // Pre-scale 32, post-scale 5
    T6CON = 0b01010100;
    // Clock source, Fosc/4, final freq: 100khz
    T6CLKCON = 0b00000001;
    // Timer6 operation mode: one shot, software reset
    T6HLT = 0b00001000;
    // Set time tm6 is on, need 2.3ms or a bit more, 2.52ms here
    T6PR = 0b11111100;
    
    // Set timer 2 to count 20ms
    // Pre-scale 128, post-scale 10
    T2CON = 0b01111001;
    // Clock source, Fosc/4, final freq: 12.5khz
    T2CLKCON = 0b00000001;
    // Timer2 operation mode: software one shot, sync with tm2
    T2HLT = 0b00000000;
    // Set time 20ms
    T2PR = 0b11111010;
    
    // Enable timer2 only, let the interrrupt start timer 4 and 6
    T2CONbits.T2ON = 1;
    
    // Enable Timer 2 interrupt
    INTCONbits.PEIE = 1;
    INTCONbits.IPEN = 0;
    INTCONbits.GIE = 1;
    PIE4bits.TMR2IE = 1;
    PIE4bits.TMR6IE = 1;
    
    // Turn on CCPs
    CCP1CONbits.EN = 1;
    CCP2CONbits.EN = 1;
    
    // Enable PWM output
    TRISC = 0x00;
    
    // Enable debug output
    TRISB = 0x00;
    
    while(1){
        LATBbits.LATB1 = !LATBbits.LATB1;
        //T4CONbits.T4ON = 1;
        //T6CONbits.T6ON = 1;
        __delay_ms(100);
    }
    
}

void servo_x(unsigned long int){
    
}
void servo_y(unsigned long int){
    
}
void tmr2_set(unsigned int){
    
}
void tmr4_set(unsigned int){
    
}
void tmr6_set(unsigned int){
    
}
