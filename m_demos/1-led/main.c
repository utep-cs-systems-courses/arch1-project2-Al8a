//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;

  configureClocks();	  	/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
    
  or_sr(0x18);		        /* CPU off, GIE on */
}

static int secondCount = 0;
static int tickCount= 0;

void 
__interrupt_vec(WDT_VECTOR) WDT ()
{
  tickCount++;
  
  if(tickCount >= 250){ 
    switch (secondCount){
      case 0:
        P1OUT |= LED_GREEN;
        P1OUT &= ~LED_RED;
        secondCount++;
        tickCount = 0;
        break;
      
      case 1:
        P1OUT &= ~LED_GREEN;
        P1OUT |= LED_RED;
        secondCount++;
        tickCount = 0;
        break;
      
      case 2:
        P1OUT |= LED_GREEN;
        P1OUT |= LED_RED;
        secondCount++;
        tickCount = 0;
        break;
      
      default:
        P1OUT &= ~LED_GREEN;
        P1OUT &= ~LED_RED;
        secondCount = 0;
        tickCount = 0;
        break;
    }
  }
}
 

