#include "configBits.c"
#include <xc.h>
#include "main.h"
int get_control(int curr_x, int curr_y) {   
    int error_x= curr_x - target_x;
    int error_y = curr_y - target_y;
    int int_error_x = int_error_x + error_x;
    int int_error_y = int_error_y + error_y;
    int diff_error_x = last_error_x - error_x;
    int diff_error_y = last_error_y - error_y;
    last_error_x = error_x;
    last_error_y = error_y;
    int control_x = Kpx*error_x+Kix*int_error_x+Kdx*diff_error_x;
    int control_y = Kpy*error_y+Kiy*int_error_y+Kdy*diff_error_y;
    return control_x, control_y;
}