#include <msp430.h>
#include "led.h"
#include "buzzer.h"
#include "state_machines.h"
#include "switches.h"


int  sw0_status = 0;
int  sw1_status = 0;
int  sw2_status = 0;
int  sw3_status = 0;
int  sw4_status = 0;


static char p1_switch_update_interrupt_sense_p1()
{
  char p1val = P1IN;

  // Update switch interrupt to detect changes from current buttons
  P1IES |= (p1val & P1SWITCH);    // If switch up, sense down
  P1IES &= (p1val | ~P1SWITCH);   // If switch down, sense up
  
  return p1val;
}



static char p2_switch_update_interrupt_sense_p2()
{
  char p2val = P2IN;


  // Update switch interrupt to detect changes from current buttons
  P2IES |= (p2val & SWITCHES);    // If switch up, sense down
  P2IES &= (p2val | ~SWITCHES);   // If switch down, sense up
  
  return p2val;
}

void p1_switch_init()
{

  P1REN |= P1SWITCH;		      /* enables resistors for SW0 */
  P1IE  |= P1SWITCH;		      /* enable interrupts from SW0 */
  P1OUT |= P1SWITCH;		      /* pull-ups for SW0 */
  P1DIR &= ~P1SWITCH;		      /* set switch SW0 bits for input */

  p1_switch_update_interrupt_sense();
  led_update();
}

void p2_switch_init()
{
  // Setup switch
  P2REN |= SWITCHES;    // Enables resistors for switches
  P2IE  |= SWITCHES;    // Enable interrupts from switches
  P2OUT |= SWITCHES;    // Pull-ups for switches
  P2DIR &= ~SWITCHES;   // Set switches' bits for input


  p2_switch_update_interrupt_sense();
  led_update();
}



void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  char p1val = switch_update_interrupt_sense();
  
  int prev_status_sw0 = sw0_status;
  int prev_status_sw1 = sw1_status;
  int prev_status_sw2 = sw2_status;
  int prev_status_sw3 = sw3_status;
  int prev_status_sw4 = sw4_status;

  // Checks if button has been pressed
  sw0_status = (p1val & SW0) ? 0 : 1;
  sw1_status = (p2val & SW1) ? 0 : 1;
  sw2_status = (p2val & SW2) ? 0 : 1;
  sw3_status = (p2val & SW3) ? 0 : 1;
  sw4_status = (p2val & SW4) ? 0 : 1;

  // Switch Selection and reset
  if( (prev_status_sw1 != sw1_status) && sw1_status){
    sw1_press_state ^= 1;
    sw2_press_state = 0;
    sw3_press_state = 0; 
    sw4_press_state = 0;
  }
  else if( (prev_status_sw2 != sw2_status) && sw2_status){
    sw2_press_state ^= 1;
    sw1_press_state = 0; 
    sw3_press_state = 0;
    sw4_press_state = 0;
  }
  else if( (prev_status_sw3 != sw3_status) && sw3_status){
    sw3_press_state ^= 1;
    sw1_press_state = 0; 
    sw2_press_state = 0;
    sw4_press_state = 0;
  }
  else if ( (prev_status_sw4 != sw4_status) && sw4_status){
    sw4_press_state ^= 1;
    sw1_press_state = 0;
    sw2_press_state = 0; 
    sw3_press_state = 0;
  }
  else if ( (prev_status_sw0 != sw0_status) && sw0_status){
    sw0_press_state ^= 1;
    sw1_press_state = 0;
    sw2_press_state = 0;
    sw3_press_state = 0;
    sw4_press_state = 0;
  }
}

