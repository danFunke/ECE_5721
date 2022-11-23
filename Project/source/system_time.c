#include "system_time.h"
#include "event.h"
#include "SysTick.h"

#include "MKL25Z4.h"

static uint32_t system_time;

static void tick_event_cb(event_t *evt, void *ctx)
{
    (void)evt;
    (void)ctx;

    // Enter Critical Section
    __disable_irq();

    system_time++;

    // Exit Critical Section
    __enable_irq();
}

static event_handler_t tick_event_handler = EVENT_HANDLER_INIT(tick_event_cb);

void system_time_init(void)
{
    system_time = 0;

    event_subscribe(&system_tick_event, &tick_event_handler);
}

uint32_t system_time_get_ms(void)
{
    uint32_t ret;

    // Enter Critical Section
    __disable_irq();

    ret = system_time;

    // Exit Critical Section
    __enable_irq();

    return ret;
}
