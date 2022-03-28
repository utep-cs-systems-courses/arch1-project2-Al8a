//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_RED;
  P1OUT |= LED_GREEN;

  configureClocks();	  	/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */

  or_sr(0x18);		        /* CPU off, GIE on */
}


static int tick_count = 0;

void
__interrupt_vec(WDT_VECTOR) WDT()	  /* 250 interrupts/sec */
{
  /* 250 / 125 / 62 / 31 / 15 */
  tick_count++;
  if(tick_count <= 64){       
    P1OUT ^= LED_RED;
  }
  else if(tick_count <= 125 && tick_count >= 64){
    P1OUT ^= LED_GREEN; 
  }
  else if(tick_count >= 250){   
    tick_count = 0;
    P1OUT ^= LED_RED;
    P1OUT ^= LED_GREEN;
  }    
}
