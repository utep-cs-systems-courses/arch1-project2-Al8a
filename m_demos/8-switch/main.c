#include <msp430.h>
#include "libTimer.h"

#define LED_RED BIT6    // P1.6
#define LED_GREEN BIT0  // P1.0
#define LEDS (BIT0 | BIT6)

#define SW1 BIT3		    /* switch1 is p1.3 */
#define SWITCHES SW1		/* only 1 switch on this board */


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



static int button_down;
static int state = 0;

void update_state(int button_state)
{  
  if(button_down){                    
    switch(state){
      case 0:                       /* GREEN ON | RED OFF */
        P1OUT |= LED_GREEN;
        P1OUT &= ~LED_RED;
        state = 1;
        break;
      case 1:                       /* GREEN OFF | RED ON */ 
        P1OUT |= LED_RED;
        P1OUT &= ~LED_GREEN;
        state = 0;
        break;
      default:
        P1OUT &= ~LED_GREEN;
        P1OUT &= ~LED_RED;
        state = 0; 
    }
  }
  else if(!button_down){             /* UNPRESSED */ 
    switch(state){
      case 0:                       /* GREEN ON | RED OFF */
        P1OUT |= LED_GREEN;
        P1OUT &= ~LED_RED;
        state = 1;
        break;
      case 1:                       /* GREEN OFF | RED ON */ 
        P1OUT |= LED_RED;
        P1OUT &= ~LED_GREEN;
        state = 0;
        break; 
      default:
        P1OUT &= ~LED_GREEN;
        P1OUT &= ~LED_RED;
        state = 0;      
    }
  }
}



void
switch_interrupt_handler()
{
    char p1val = P1IN;		        /* switch is in P1 */

    /* update switch interrupt sense to detect changes from current buttons */
    P1IES |= (p1val & SWITCHES);	/* if switch up, sense down */
    P1IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */

    button_down = p1val & SW1;    // button_state
    update_state(button_down);
}



/* Switch on P1 (S2) */
void
__interrupt_vec(PORT1_VECTOR) Port_1(){
    if (P1IFG & SWITCHES) {	        /* did a button cause this interrupt? */
        P1IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
        switch_interrupt_handler();	/* single handler for all switches */
    }
}