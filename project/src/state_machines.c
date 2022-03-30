#include <msp430.h>
#include "buzzer.h"
#include "led.h"
#include "switches.h"
#include "buzzer_notes.h"
#include "state_machines.h"



// SWITCH 1
void play_song_1()
{
  static char curr_note = 0;
  // All notes of song, 0s are for break in between notes
  int notes[45] = {C5, A4, C5, 0, B4, C5, B4, B4, G4, G4, G4, 0, G4, E5, D5_SHARP, D5_SHARP, C5, B4, B4, G4, G4, G4, 0, C5, A4, C5,0, B4, C5, 0, B4, G4,0, 0, A4, A4, F4, A4, G4, A4, G4, C4, 0, C5, 0};
  int n = 45;

  if (curr_note < n){
    
    buzzer_set_period(notes[curr_note]);
    curr_note++;
  }else
    curr_note = 0;
}




// SWITCH 2
void play_song_2()
{
  static char curr_note = 0;  
  int notes[37] = {G5, D5, E5_FLAT, F5, E5_FLAT, D5, C5, 0, C5, E5_FLAT, G5, F5, E5_FLAT, D5, E5_FLAT, F5, G5, E5_FLAT, C5, 0, C5, 0, 0, 0, F5, A5_FLAT, C6_SHARP, B5_FLAT, A5_FLAT, G5, F5, G5, E5_FLAT, C5, 0, C5, 0}; 
  int n = 37;

  if (curr_note < n){
    buzzer_set_period(notes[curr_note]);
    curr_note++;
  }else
    // LOOP SONG 
    curr_note = 0;
}




// SWITCH 3
void play_song_3()
{
  static char curr_note = 0;
  switch(curr_note){
  case 0:
    buzzer_set_period(C6_SHARP);
    swap_leds(1);
    //dim_sequence();
    curr_note++;
    break;
  case 1:
    buzzer_set_period(F6_SHARP);
    swap_leds(0);
    //dim_sequence();
    curr_note++;
    break;
  case 2:
    buzzer_set_period(G6_SHARP);
    swap_leds(1);
    // dim_sequence();
    curr_note++;
    break;
  case 3:
    buzzer_set_period(A6);
    swap_leds(0);
    //dim_sequence();
    curr_note++;
    break;
  case 5: 
    buzzer_set_period(C6_SHARP);
    swap_leds(1);
    //dim_sequence();
    curr_note++;
    break;
  case 7:
    buzzer_set_period(F6_SHARP);
    swap_leds(0);
    //dim_sequence();
    curr_note++;
    break;
  case 8:  
    buzzer_set_period(G6_SHARP);
    swap_leds(1);
    //dim_sequence();
    curr_note++;
    break;
  case 10:  
    buzzer_set_period(A6);
    swap_leds(0);
    //dim_sequence();
    curr_note++;
    break;
  case 14:
    buzzer_set_period(D6);
    swap_leds(1);
    //dim_sequence();
    curr_note++;
    break;
  case 15:
    buzzer_set_period(F6_SHARP);
    swap_leds(0);
    //dim_sequence();
    curr_note++;
    break;
  case 16:                              
    buzzer_set_period(G6_SHARP);
    swap_leds(1);
    //dim_sequence();
    curr_note++;
    break;
  case 18:
    buzzer_set_period(D6);
    swap_leds(0);
    //dim_sequence();
    curr_note++;
    break;
  case 20:
    buzzer_set_period(F6_SHARP);
    swap_leds(1);
    //dim_sequence();
    curr_note++;
    break;
  case 21:
    buzzer_set_period(G6_SHARP);
    swap_leds(0);
    //dim_sequence();
    curr_note++;
    break;
  case 22:
    buzzer_set_period(A6);
    swap_leds(1);
    // dim_sequence();
    curr_note++;
    break;
  case 26:                              // LOOP BACK TO BEGINNING
    buzzer_set_period(0);
    leds_on(0);
    //   dim_sequence();
    curr_note = 0;
    break;
  default:
    curr_note++;
    break;
  }
}



// SWITCH 4 
void play_song_4()
{
    static int blinkLimit = 7;  // duty cycle = 1/blinkLimit
    static int blinkCount = 0;  // cycles 0...blinkLimit-1
    static int secondCount = 0; // state var representing repeating time 0…1s
  
    blinkCount ++; 
    if (blinkCount >= blinkLimit) { // on for 1 interrupt period
      blinkCount = 0;
      update_state();
    }
    else{		                        // off for blinkLimit - 1 interrupt periods
      update_state();
    }
  
    // measure a second
    secondCount ++;
    if (secondCount >= 250) {       // once each second
      secondCount = 0;
      led_update();
      blinkLimit++;	                // reduce duty cycle
      if (blinkLimit >= 8) {        // but don't let duty cycle go below 1/7.
        blinkLimit = 0;
        update_state();
      }
    }
}
  


void update_state(){
  static char curr_note = 0;
  switch(curr_note){
  case 0:
    buzzer_set_period(G3);
    leds_on(0);
    curr_note++;
    led_update();
    dim_sequence();
    break;
  case 1:
    buzzer_set_period(F2_SHARP);
    swap_leds(1);
    dim_sequence(); 
    led_update();
    curr_note++;
    break;
  case 2:
    buzzer_set_period(E3);
    swap_leds(0);
    dim_sequence(); 
    led_update();
    curr_note++;
  case 3:
    buzzer_set_period(E2);
    swap_leds(1);
    dim_sequence(); 
    led_update();
    curr_note++;
    break;
  case 4:
    buzzer_set_period(A6);
    swap_leds(0);
    dim_sequence(); 
    led_update();
    curr_note++;
    break;
  case 5:
    buzzer_set_period(D5);
    leds_on(0);
    dim_sequence(); 
    led_update();
    swap_leds(1);
    curr_note++;
    break;
  case 6:
    buzzer_set_period(F6);
    swap_leds(0);
    dim_sequence(); 
    led_update();
    curr_note++;
    break;
  case 7:
    buzzer_set_period(D8);
    swap_leds(1);
    dim_sequence(); 
    led_update();
    curr_note++;
    break;
  case 8:
    buzzer_set_period(B2);
    swap_leds(0);
    dim_sequence(); 
    led_update();
    curr_note++;
    break;
  default:
    curr_note = 0;
    leds_on(0);
    led_update();
    dim_sequence();
    break;
  }
}



void toy_reset()
{
buzzer_set_period(0);
led_update();
}

