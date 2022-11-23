#include "MKL25Z4.h"
#include "SysTick.h"

#include <stdint.h>

#define SYSTEM_CLOCK_FREQUENCY_HZ   (48000000)
#define SYSTICK_INTERVAL_MS         (1)
#define SYSTICK_FREQUENCY_HZ        (SYSTICK_INTERVAL_MS * 1000)
#define SYSTICK_TMR_RELOAD_VAL      ((SYSTEM_CLOCK_FREQUENCY_HZ / SYSTICK_FREQUENCY_HZ) - 1)

event_t system_tick_event = EVENT_INIT(system_tick_event);

static void system_clock_init(void)
{
    // Select PLL/FLL as clock source and select
    // internal reference clock as source for FLL/PLL
    MCG->C1 |= (MCG_C1_CLKS(0) | MCG_C1_IREFS(1));
	
    // Select "Mid range" for DCO range and set DCO frequency of 48MHz
    MCG->C4 |= (MCG_C4_DRST_DRS(1) | MCG->C4 | MCG_C4_DMX32(1));
}

void SysTick_Init(void)
{
    // Set system clock to 48MHz
    system_clock_init();

    // Configure SysTick to generate interrupt every 1ms
    SysTick->LOAD = (uint32_t)SYSTICK_TMR_RELOAD_VAL;

    // Initialize counter value to 0
    SysTick->VAL = 0UL;

    // Select processor clock as SysTick clock source, enable
    // SysTick exception, and Enable SysTick counter
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk  | 
                    SysTick_CTRL_TICKINT_Msk    | 
                    SysTick_CTRL_ENABLE_Msk;

    // Initialize SysTick_IRQn
    NVIC_SetPriority(SysTick_IRQn, 3);
    NVIC_ClearPendingIRQ(SysTick_IRQn);
    NVIC_EnableIRQ(SysTick_IRQn);
}

void SysTick_Handler(void)
{
    // Clear SysTick interrupt
    NVIC_ClearPendingIRQ(SysTick_IRQn);

    // Publish system_tick_event
    event_publish(&system_tick_event, NULL);
}
