/**
 * @file SysTick.h
 * @author D. Funke
 * @brief Module to configure the SysTick interrupt
 * @date 2022-11-19
 * 
 */

#ifndef SYS_TICK_H_
#define SYS_TICK_H_

#include "event.h"

// Event to broadcast with every system tick
extern event_t system_tick_event;

/**
 * @brief Initializes system tick interrupt to generate an interrupt every 1 ms
 * 
 */
void SysTick_Init(void);

/**
 * @brief System Tick interrupt handler; broadcasts system_tick_event
 * 
 */
void SysTick_Handler(void);

#endif /* SYS_TICK_H_ */