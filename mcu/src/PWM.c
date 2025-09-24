// Sadhvi Narayanan, sanarayanan@g.hmc.edu, 9/21/2025
/*

File    : PWM.c
Purpose : Set up TIM16_CH1 to enable and setup PWM signal to play the frequency of our note

*/


#include "PWM.h"

void init_PWM() {
    // setting the pre-scalar capture value (timer clock)
    TIM16->PSC = PSC_VAL_PWM;
  
    // setting the output compare 1 mode to PWM mode 1 (110) --> channel 1 is active when cnt < ccr1 (or 111?)
    TIM16->CCMR1_output |= (1 << 6 | 1 << 5); // OC1M
    TIM16->CCMR1_output &= ~(1 << 4); // OC1M

    // setting the capture/compare enable register pwm polarity to active high (setting bit value to 0)
    TIM16->CCER &= ~(1 << 1); // CC1P

    // setting the capture/compare output enable to 1
    TIM16->CCER |= (1 << 0); // CC1E

    // setting the output compare 1 preload enable to 1 (to enable the shadow register updating)
    TIM16->CCMR1_output |= (1 << 3); // OC1PE

    // setting MOE to 1 to enable global output
    TIM16->BTDR |= (1 << 15); // MOE

    // setting the UG (update generation) bit to 1 (to enable shadow register updating)
    TIM16->EGR |= (1 << 0); // UG

    // setting the clock enable to 1
    TIM16->CR1 |= (1 << 0); // CEN
}

void PWM_freq(int freq){
    // calculating the length of the notes array

    // calculating the ARR value (max_counter value)
    uint32_t arr_val = 0;
    if (freq == 0) {
     arr_val = 0;
    }
    else {
      arr_val = ((80000000 / (PSC_VAL_PWM + 1)) / freq) - 1;
    }

    // set the counter max value to the calculated amount
    TIM16->ARR = arr_val; // ARR

    // set the duty cycle to 50% of the counter
    TIM16->CCR1 = arr_val / 2; // CCR1

    // setting the UG (update generation) bit to 1 (to enable shadow register updating)
    TIM16->EGR |= (1 << 0); // UG

    // reset the counter for safety
    TIM16->CNT = 0; // CNT

    //// make sure the UIF bit is 0 for safety
    //TIM16->SR &= ~(1 << 0); // UIF

    //// wait until the UIF bit turns to 1 --> this means we reached our max counter value in ARR
    //while ((TIM16->SR & 1) == 0); // UIF
}

