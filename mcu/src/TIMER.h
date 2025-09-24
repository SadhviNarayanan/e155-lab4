// Sadhvi Narayanan, sanarayanan@g.hmc.edu, 9/21/2025
/*

File    : TIMER.h
Purpose : Set up struct for TIM15 so we can directly access the memory registers

*/


// TIMER_H
// Header for RCC functions

#ifndef STM32L4_TIMER_H
#define STM32L4_TIMER_H

#include <stdint.h>
#include <math.h>


///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

#define __IO volatile

// Base addresses
#define TIM15_BASE (0x40014000UL) // base address of RCC

// PLL
#define PSC_VAL_TIMER 3000


/**
  * @brief Reset and Clock Control
  */

typedef struct
{
  __IO uint32_t CR1;          /*!< control register 1,                                            Address offset: 0x00 */
  __IO uint32_t CR2;       /*!< control register 2,                         Address offset: 0x04 */
  __IO uint32_t SMCR;        /*!< sl*** mode control register,                                        Address offset: 0x08 */
  __IO uint32_t DIER;     /*!< DMA/interrupt enable register,                                   Address offset: 0x0C */
  __IO uint32_t SR; /*!< status register,                                     Address offset: 0x10 */
  // uint32_t      RESERVED;    /*!< Reserved,                                                                Address offset: 0x14 */
  __IO uint32_t EGR;        /*!< event generation register,                                     Address offset: 0x18 */
  __IO uint32_t CCMR1_output;        /*!< capture/compare more output register,                                       Address offset: 0x1C */
  __IO uint32_t CCMR1_input;        /*!< capture/compare more input register,                                     Address offset: 0x20 */
  // uint32_t      RESERVED0;   /*!< Reserved,                                                                Address offset: 0x24 */
  __IO uint32_t CCER;    /*!< capture/compare enable register                                     Address offset: 0x28 */
  __IO uint32_t CNT;    /*!< counter,                                     Address offset: 0x2C */
  __IO uint32_t PSC;    /*!< prescalar,                                   Address offset: 0x30 */
  __IO uint32_t      ARR;   /*!< auto reload register                                                               Address offset: 0x34 */
  __IO uint32_t      RCR;   /*!< reptition counter register */
  __IO uint32_t CCR1;   /*!< capture/compare register1                                 Address offset: 0x38 */
  __IO uint32_t CCR2;   /*!< capture/copare register 2,                                    Address offset: 0x3C */
  uint32_t      RESERVED0;   /*!< Reserved */
  uint32_t      RESERVED1;   /*!< Reserved */
  __IO uint32_t BTDR;    /*!< break and dead time register,                                      Address offset: 0x40 */
  // uint32_t      RESERVED2;   /*!< Reserved,                                                                Address offset: 0x44 */
  __IO uint32_t DCR;     /*!< DMA control register,                              Address offset: 0x48 */
  __IO uint32_t DMAR;     /*!< DMA address for full transfer,                              Address offset: 0x4C */
  __IO uint32_t OR1;     /*!< option register 1,                              Address offset: 0x50 */
  uint32_t      RESERVED3;   /*!< Reserved, */ 
  uint32_t      RESERVED4;   /*!< Reserved */
  uint32_t      RESERVED5;   /*!< Reserved */                                                          
  __IO uint32_t OR2;    /*!< option register 2,   */                                     
} TIM_15_TypeDef;

#define TIM15 ((TIM_15_TypeDef *) TIM15_BASE)

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void init_delay(void);
void delay(int song_dur);

#endif