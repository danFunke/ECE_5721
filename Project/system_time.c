/**
 * @file system_time.h
 * @author your name (you@domain.com)
 * @brief Module to provide a simple system-level wall clock
 * @date 2022-11-19
 * 
 */

#include "system_time.h"

static volatile uint32_t system_time_ms = 0;

/**
 * @brief 
 * 
 */
static void update_time(event_t *evt, void *ctx)
{
    (void)evt;
    (void)ctx;

    system_time_ms++;
}

static event_handler_t tick_handler = EVENT_HANDLER_INIT(update_time);

void system_time_init(void)
{
    __disable_irq();
    event_subscribe(&SysTick_event, &tick_handler);
    __enable_irq();
}

uint32_t system_time_get_ms(void)
{
    uint32_t ret = 0;
    __disable_irq();
    ret = system_time_ms;
    __enable_irq();

    return ret;
}