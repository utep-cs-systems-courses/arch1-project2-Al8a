#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

int main() {
    configureClocks();
    enableWDTInterrupts();

    buzzer_init();
    buzzer_set_period(300);	/* start buzzing!!! 2MHz/1000 = 2kHz*/

    or_sr(0x18);                // CPU off, GIE on
}

int beepLimit = 200000;
int beepCount = 0;
int secondCount = 0;

void __interrupt_vec(WDT_VECTOR) WDT(){
  beepCount += 450;

  if(beepCount >= beepLimit){
    beepCount = 0;
  }
  else{
    buzzer_set_period(beepCount);
  }


  secondCount++;
  if(secondCount >= 250){
    secondCount = 0;
    beepLimit += 1500;
    if (beepLimit >= 50000){
      beepLimit = 0;
    }
  }
}
