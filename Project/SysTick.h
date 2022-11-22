/**
 * @file SysTick.h
 * @author D. Funke
 * @brief Module to configure the SysTick interrupt
 * @date 2022-11-19
 * 
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "event.h"

extern event_t SysTick_event;

/**
 * @brief 
 * 
 */
void SysTick_init(void);

/**
 * @brief 
 * 
 */
void SysTick_Handler(void);

#endif /* SYSTICK_H_ */