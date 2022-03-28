#include <msp430.h>
#include "led.h"
#include "state_machines.h"

void dim_sequence()
{
  static int dim_state = 0;

  switch (dim_state){
  case 0:
    red_dim_75();
    green_dim_25();
    dim_state++;
    break;
  case 1:
    red_dim_25();
    green_dim_75();
    dim_state++;
    break;
  case 2:
    red_dim_50();
    green_dim_50();
    dim_state = 0;
    break;
  default:
    dim_state = 0;
    break;
  }
}



static int red_led_state = 0;
static int green_led_state = 0;


void red_dim_25(){
  switch (red_led_state){
  case 0:
    red_on(0);
    red_led_state++;
  case 1:
    red_led_state++;
  case 2:
    red_led_state++;
    break;
  case 3:
    red_on(1);
    red_led_state = 0;
    break;
  default:
    break;
  }
}


void red_dim_50(){
  switch (red_led_state){
  case 0:
    red_on(1);
    red_led_state++;
    break;
  case 1:
    red_on(0);
    red_led_state++;
    break;
  case 2:
    red_led_state++;
    break;
  case 3:
    red_on(1);
    red_led_state = 0;
  default:
    break;
  }
}

void red_dim_75(){
switch(red_led_state){
  case 0:
    red_on(0);
    red_led_state++;
    break;
  case 1:
    red_led_state++;
    break;
  case 2:
    red_led_state++;
    break;
  case 3:
    red_on(1);
    red_led_state = 0;
    break;
  default:
    break;
  }
}

void green_dim_25(){
   switch (green_led_state){
  case 0:
    green_on(0);
    green_led_state++;
  case 1:
    green_led_state++;
  case 2:
    green_led_state++;
    break;
  case 3:
    green_on(1);
    green_led_state = 0;
    break;
  default:
    break;
  }
}

void green_dim_50(){
   switch (green_led_state){
  case 0:
    green_on(1);
    green_led_state++;
    break;
  case 1:
    green_on(0);
    green_led_state++;
    break;
  case 2:
    green_led_state++;
    break;
  case 3:
    green_on(1);
    green_led_state = 0;
  default:
    break;
  }
}


void green_dim_75(){
  switch(green_led_state){
  case 0:
    green_on(0);
    green_led_state++;
    break;
  case 1:
    green_led_state++;
    break;
  case 2:
    green_led_state++;
    break;
  case 3:
    green_on(1);
    green_led_state = 0;
    break;
  default:
    break;
  }
}