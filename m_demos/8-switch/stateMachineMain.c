#include <msp430.h>
#include "libTimer.h"

#define LED_RED BIT6    // P1.6
#define LED_GREEN BIT0  // P1.0
#define LEDS (BIT0 | BIT6)

#define SW1 BIT3		    /* switch1 is p1.3 */
#define SWITCHES SW1		/* only 1 switch on this board */

enum State{OFF, RED_PRESSED, RED_UNPRESSED, GREEN_PRESSED, GREEN_UNPRESSED};



void main(void) 
{  
  configureClocks();

  P1DIR |= LEDS;
  P1OUT &= ~LEDS;		    /* leds initially off */
  
  P1REN |= SWITCHES;		/* enables resistors for switches */
  P1IE |= SWITCHES;		  /* enable interrupts from switches */
  P1OUT |= SWITCHES;		/* pull-ups for switches */
  P1DIR &= ~SWITCHES;		/* set switches' bits for input */

  or_sr(0x18);          // CPU off, GIE on
} 



void handle_unpressed(enum State* state)
{
  switch (*state) {
    
    case GREEN_UNPRESSED:
    case GREEN_PRESSED: 
    case OFF: 
      *state = GREEN_UNPRESSED;     // start with green from off state
      P1OUT |= LED_GREEN;
      P1OUT &= ~LED_RED;
      break;
   
    case RED_UNPRESSED:             // stay at red unpressed
    case RED_PRESSED:               // goto red unpressed
      *state = RED_UNPRESSED;
      P1OUT |= LED_RED;
      P1OUT &= ~LED_GREEN;
      break;
  }
}



void handle_pressed(enum State* state)
{
  switch(*state){
    
    case RED_UNPRESSED:             // go to green pressed
    case GREEN_PRESSED:             // stay at green pressed
    case OFF:                       // default to green pressed
      *state = GREEN_PRESSED;       // Start with green from off state
      P1OUT |= LED_GREEN;
      P1OUT &= ~LED_RED;
      break;
    
    case RED_PRESSED:               // stay at red pressed
    case GREEN_UNPRESSED:           // go to red pressed
      *state = RED_PRESSED;
      P1OUT |= LED_RED;
      P1OUT &= ~LED_GREEN;
      break;
  }
}



void update_state(char unpressed)
{
  static enum State state = OFF;    // Default to everything off
  if (unpressed)
    handle_unpressed(&state);
  else
    handle_pressed(&state);
  
}



void
switch_interrupt_handler()
{
    char p1val = P1IN;		        /* switch is in P1 */

    /* update switch interrupt sense to detect changes from current buttons */
    P1IES |= (p1val & SWITCHES);	/* if switch up, sense down */
    P1IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */

    update_state(p1val & SW1);
}



/* Switch on P1 (S2) */
void
__interrupt_vec(PORT1_VECTOR) Port_1(){
    if (P1IFG & SWITCHES) {	        /* did a button cause this interrupt? */
        P1IFG &= ~SWITCHES;		    /* clear pending sw interrupts */
        switch_interrupt_handler();	/* single handler for all switches */
    }
}