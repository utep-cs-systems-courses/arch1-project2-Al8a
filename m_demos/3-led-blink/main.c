//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT |= LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		  /* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);			      /* CPU off, GIE on */
}


int secondCount = 0;            /* global state var to count time */
int led_swap = 0;               /* swap between red(1) and green(1) LEDS */

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  secondCount ++;
  if (secondCount <= 32 && led_swap == 0) { 	  /* once each sec... */
    P1OUT ^= LED_GREEN;		                      /* toggle green LED */
    led_swap = 1;               
  }
  else if (secondCount <= 32 && led_swap == 1){
    P1OUT ^= LED_RED;                           /* Toggle red LED  */
    led_swap = 0;               
  }
  else if (secondCount <= 63 && led_swap == 0) { 
    P1OUT ^= LED_GREEN;		                    
    led_swap = 1;               
  }
  else if (secondCount <= 63 && led_swap == 1){
    P1OUT ^= LED_RED;                          
    led_swap = 0;               
  }
  else if (secondCount < 125 && led_swap == 0) {
    P1OUT ^= LED_GREEN;		                      
    led_swap = 1;               
  }
  else if (secondCount < 125 && led_swap == 1){
    P1OUT ^= LED_RED;                          
    led_swap = 0;               
  }       
  else if(secondCount >= 250 && led_swap == 0) {
    secondCount = 0;		                        /* reset count */
    P1OUT ^= LED_GREEN;		                      
    led_swap = 1;               
  }
  else if (secondCount >= 250 && led_swap == 1){
    secondCount = 0;
    P1OUT ^= LED_RED;                           
    led_swap = 0;               
  }
} 

