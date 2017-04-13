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



