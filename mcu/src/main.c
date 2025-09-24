// Sadhvi Narayanan, sanarayanan@g.hmc.edu, 9/21/2025
/*

File    : main.c
Purpose : Initialize clocks, provide clocks to timers, and play music by leveraging other functions

*/


 // #include <stdio.h>
 // #include <stm32l432xx.h>

#include "TIMER.h"
#include "PWM.h"
#include "STM32L432KC_FLASH.h"
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_GPIO.h"


// Pitch in Hz, duration in ms
const int fur_elise[][2] = {
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{416,	125},
{494,	125},
{523,	250},
{  0,	125},
{330,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{523,	125},
{494,	125},
{440,	250},
{  0,	125},
{494,	125},
{523,	125},
{587,	125},
{659,	375},
{392,	125},
{699,	125},
{659,	125},
{587,	375},
{349,	125},
{659,	125},
{587,	125},
{523,	375},
{330,	125},
{587,	125},
{523,	125},
{494,	250},
{  0,	125},
{330,	125},
{659,	125},
{  0,	250},
{659,	125},
{1319,	125},
{  0,	250},
{623,	125},
{659,	125},
{  0,	250},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{416,	125},
{494,	125},
{523,	250},
{  0,	125},
{330,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{523,	125},
{494,	125},
{440,	500},
{  0,	500},
{  0,	500}};

// Silent Night - First verse (using your timing table)
// Each note: {frequency_Hz, duration_ms}
const int silent_night[][2] = {
    // "Si-lent night"  
    {392, 250},  // G4 - "Si" (quarter note)
    {440, 250},  // G4 - "lent" (dotted quarter)
    {392, 250},  // A4 - "night" (quarter note)
    {330, 250},
    
    {0, 250}, 

    // "ho-ly night"
    {392, 250}, 
    {440, 250},
    {392, 250},
    {330, 250},

    {0, 250},
    
    // "All is calm"
    {587, 500},
    {587, 250},
    {495, 250},
    {0, 63},
    
    
    // all is bright
    {520, 500},
    {520, 250},
    {392, 250},
    {0, 63},
    
    // round your vir-gin
    {440, 250},
    {440, 250},
    {523, 500},
    {493, 250},
    {440, 250},

    // "mother and child"
    {392, 500},
    {440, 250},
    {392, 250},
    {330, 250},
    {0, 63}, 
   
    
    // "Holy infant"
    {440, 250},
    {440, 250},
    {523, 500},
    {493, 250},
    {440, 250},
    
    // "so tender and mild"
    {392, 500},
    {440, 250},
    {392, 250},
    {330, 250},
    {0, 63}, 
    
    
    // "Sleep in heavenly"
    {588, 500},
    {588, 500},

    {698, 500},
    {588, 250},
    {494, 250},
   
    
    // "peace" (first time)
    {523, 500},
    {659, 500},
    
    // "Sleep in heavenly" (repeat)
    {523, 500},
    {392, 250},
    {330, 250},

    {392, 500},
    {349, 250},
    {293, 250},
    
    // "peace" (final)
    {261, 250},
   
    {0, 0}
};



int main(void) {
    configureFlash();
    configureClock();

    RCC->AHB2ENR |= (1 << 0); // GPIOA clock 
    RCC->APB2ENR |=  (1 << 17); // TIM16 clock
    RCC->APB2ENR |=  (1 << 16); // TIM15 clock
    // GPIO->MODER |=  (2 << (6 * 2));   // set pin A6 mode to 10 (AF) -> AF for pwm
    pinMode(6, 2); // set pin A6 mode to 10 (AF) -> AF for pwm
    GPIO->AFRL |=  (14 << (6 * 4));     // AF14 connects TIM16_CH1 to PA6

    // initialize our system
    init_delay();
    init_PWM();

    // iterate through both arrays to play the music by setting the PWM frequency and having a delay to hold the signal
    int arr_length = sizeof(fur_elise) / sizeof(fur_elise[0]);
    for (int i = 0; i < arr_length; i ++) {
      if (fur_elise[i][1] == 0) {
        PWM_freq(0);
        return 0;
      }
      PWM_freq(fur_elise[i][0]);
      delay(fur_elise[i][1]);
    }

    int arr_length2 = sizeof(silent_night) / sizeof(silent_night[0]);
    for (int i = 0; i < arr_length2; i ++) {
      if (silent_night[i][1] == 0) {
        PWM_freq(0);
        return 0;
      }
      PWM_freq(silent_night[i][0]);
      delay(silent_night[i][1]);
    }
	
}
