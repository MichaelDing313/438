#include "configBits.c"
#include <xc.h>
#include "main.h"
#define Y1 RA0
#define Y2 RA2
#define X1 RA1
#define X2 RA3
//
inline void n10ms_delay(int n){
    for(int i=n; i > 0; i--){
        __delay_ms(10);
    }
    
}
//
//void shortWait(int ms){
//    int i, j;
//    for (i=0; i<ms; i++){
//        for (j=0; j<4000; j++);
//    }
//}

int getY(void) {
    ADON = 1;
    ADPCH = 0b00001;
    
    // Set y1 y2 as 5 and 0 
    TRISA = 0b1010;
    PORTA = 0x01;
    ANSELA = 0b0000; 
    ADCS = 1;
//    shortWait(1);
    int ret = 0;
    ADGO = 1;
    while (ADGO == 1) {
        continue;
    }
    ret = ADRESH;
    ret = ret >> 1;
    return(ret);
}


int getX(void) {
    ADON = 1;
    ADPCH = 0b00000;
    
    // Set y1 y2 as 5 and 0 
    TRISA = 0b0101;
    PORTA = 0x02;
    ANSELA = 0b0000; 
    ADCS = 1;
//    shortWait(1);
    int ret = 0;
    ADGO = 1;
    while (ADGO == 1) {
        continue;
    }
    ret = ADRESH;
    ret = ret >> 1;
    return(ret);
}


int get_coord(void) {
    
//    int ADC_wait = 1;
    INTCON = 0x00;
    TRISD = 0x00;
    TRISC = 0x00;
    ADCON0 = 0b10000000;
    // Setting up for ADC interrupts
    ADIE = 0;
    ADIF = 0;
    PEIE = 0;
    
    RA4 = 1;
    int curr_x= getX();
    n10ms_delay(3);
    int curr_y =  getY();
    n10ms_delay(2);
    PORTD = curr_x;
    PORTC = curr_y;
    return curr_x, curr_y;
}
