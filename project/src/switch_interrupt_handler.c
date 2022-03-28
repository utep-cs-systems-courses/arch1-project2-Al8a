#include <msp430.h>
#include "switches.h"


/* Switch on P1  */
void
p1__interrupt_vec(PORT1_VECTOR) Port_1(){
    if (P1IFG & P1SWITCH) {	        /* did a button cause this interrupt? */
        P1IFG &= P1SWITCH;		      /* clear pending sw interrupts */
        switch_interrupt_handler();	/* single handler for all switches */
    }
}


// Switches on P2
void 
p2__interrupt_vec(PORT2_VECTOR) PORT_2()
{
  if(P2IFG & SWITCHES) {          // Did a button cause this interrupt?
    P2IFG &= ~SWITCHES;           // Clear pending sw interrupts
    switch_interrupt_handler();   // Single handler for all switches
  }
}


