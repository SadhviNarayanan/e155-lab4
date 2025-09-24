// Sadhvi Narayanan, sanarayanan@g.hmc.edu, 9/21/2025
/*

File    : PWM.h
Purpose : Set up struct for TIM16 so that we can use use it for PWM (frequency setting)

*/


// PWM
// Header for PWM functions

#ifndef PWM_H
#define PWM_H

#include <stdint.h>
#include <math.h>

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

#define __IO volatile

// Base addresses
#define TIM16_BASE (0x40014400UL)

// PLL
#define PSC_VAL_PWM 16
/**
  * @brief Reset and Clock Control
  */

typedef struct
{
  __IO uint32_t CR1;          /*!< control register 1  Address offset: 0x00 */
  __IO uint32_t CR2;          /*!< control register 2, Address offset: 0x04 */
  uint32_t      RESERVED0;
  __IO uint32_t DIER;         /*!< DMA/interrupt enable reg, Address offset: 0x0C */
  __IO uint32_t SR;           /*!< status register, Address offset: 0x10 */
  // uint32_t      RESERVED;    /*!< Reserved,  Address offset: 0x14 */
  __IO uint32_t EGR;          /*!< event generation register, Address offset: 0x18 */
  __IO uint32_t CCMR1_output;        /*!< capture/compare mode register 1, Address offset: 0x1C */
  __IO uint32_t CCMR1_input;        /*!< capture/compare mode register input, Address offset: 0x20 */
  // uint32_t      RESERVED0;   /*!< Reserved, Address offset: 0x24 */
  __IO uint32_t CCER;    /*!< capture/compare enable register, Address offset: 0x28 */
  __IO uint32_t CNT;    /*!< counter, Address offset: 0x2C */
  __IO uint32_t PSC;    /*!< prescalar, Address offset: 0x30 */                                                 
  __IO uint32_t ARR;   /*!< auto reload register, Address offset: 0x38 */
  __IO uint32_t RCR;   /*!< repetition counter register, Address offset: 0x3C */
  __IO uint32_t CCR1;  /*!< capture/compare register 1, Address offset: 0x34 */
  uint32_t      RESERVED1;   /*!< Reserved, */ 
  uint32_t      RESERVED2;   /*!< Reserved */
  uint32_t      RESERVED3;   /*!< Reserved */
  __IO uint32_t BTDR;    /*!< break and dead-time register, Address offset: 0x40 */
  // uint32_t      RESERVED2;   /*!< Reserved, Address offset: 0x44 */
  __IO uint32_t DCR;     /*!< DMA control register, Address offset: 0x48 */
  __IO uint32_t DMAR;     /*!< DMA address for full transfer, Address offset: 0x4C */
  __IO uint32_t OR1;     /*!< option register 1, Address offset: 0x50 */                                                           
  uint32_t      RESERVED5;   /*!< Reserved, */ 
  uint32_t      RESERVED6;   /*!< Reserved */
  uint32_t      RESERVED7;   /*!< Reserved */ 
  __IO uint32_t OR2;    /*!< option register 2,   */                                     
} TIM_16_TypeDef;

#define TIM16 ((TIM_16_TypeDef *) TIM16_BASE)

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void init_PWM(void);
void PWM_freq(int freq);

#endif