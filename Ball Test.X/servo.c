/*
 * File:   servo.c
 * Author: Michael
 *
 * Created on April 9, 2017, 7:33 PM
 */


#include <xc.h>
#include "servo.h"
#include "configBits.c"
#include "main.h"

void servo_init(){
    // test pwm stuff
        
    // Timer 4 configurations PWM will run off Timer 4
    // Pre-scale 16, post-scale 1
    T4CON = 0b11110000;
    // Clock source, Fosc/4, final freq: 400khz
    T4CLKCON = 0b00000001;
    // Timer4 operation mode: one shot operation
    T4HLT = 0b00001000;
    // Set time for PWM period, 
    T4PR = 0b11111111;

    // CCP1 and 2 in PWM Mode, off for now
    CCP1CON = 0b00001100;
    CCP2CON = 0b00001100;
    // All CCP use Timer4 
    CCPTMRS = 0b10101010;
    // Set PWM width for now
    CCPR1H = 0b00000011; // 
    CCPR1L = 0b10000000;
    CCPR2H = 0b00000011; // 
    CCPR2L = 0b10000000;
    
    // Set timer 2 to count 20ms
    // Pre-scale 128, post-scale 10
    T2CON = 0b01111001;
    // Clock source, Fosc/4, final freq: 12.5khz
    T2CLKCON = 0b00000001;
    // Timer2 operation mode: software one shot, sync with tm2
    T2HLT = 0b00000000;
    // Set time 20ms
    T2PR = 0b11111011;
    
    // Set Timer 4 and 6 to be automatically reset by timer 2
    //T4RST = 0b00000001;
    
    
    // Enable timer2 only, let the interrrupt start timer 4 and 6
    T2CONbits.T2ON = 1;
    
    // Enable Timer 2 interrupt
    PIE4bits.TMR2IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.IPEN = 0;
    INTCONbits.GIE = 1;
    
    // Turn on CCPs
    CCP1CONbits.EN = 1;
    CCP2CONbits.EN = 1;
    
    // Enable PWM output
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC1 = 0;
    
    
    RC2PPS = 0b00000101;
    RC1PPS = 0b00000110;
}

void servo_x(unsigned int ang){
    // Angles are in 1/10s of degrees
    // zero point: 2ms, CCPRxH:CCPRxL = 1000 = 0b 01 11110100
    // Full range, ~90 degrees, 1.35ms, CCPRxH:CCPRxL = 675 = 0b 10 1010 0011
    // mid point 1.72ms CCPRxH:CCPRxL = 860 450
    if (ang > 900){
        ang = 900;
    }
    ang = 1000 - (ang * 14 / 45);
    if (ang > 767){
        CCPR1H = 0b00000011;
    }else if (ang > 511){
        CCPR1H = 0b00000010;
    } else {
        CCPR1H = 0b00000001;
    }
    CCPR1L = ang & 0xFF;
}
void servo_y(unsigned int ang){
    // Angles are in 1/10s of degrees
    // zero point: 2ms, CCPRxH:CCPRxL = 1000 = 0b 01 11110100
    // Full range, ~90 degrees, 1.56ms, CCPRxH:CCPRxL = 780 = 0b 10 1010 0011
    // mid point 1.78ms CCPRxH:CCPRxL = 890 450
    if (ang > 900){
        ang = 900;
    }
    
    ang = (ang * 11 / 45) + 780;
    
    if (ang > 767){
        CCPR2H = 0b00000011;
    }else if (ang > 511){
        CCPR2H = 0b00000010;
    } else {
        CCPR2H = 0b00000001;
    }
    
    CCPR2L = ang & 0xFF;
}
