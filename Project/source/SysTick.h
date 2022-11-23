#ifndef SYS_TICK_H_
#define SYS_TICK_H_

#include <stdint.h>
#include "event.h"

// Event to broadcast with every system tick
extern event_t system_tick_event;

void SysTick_Init(void);

void SysTick_Handler(void);

#endif /* SYS_TICK_H_ */