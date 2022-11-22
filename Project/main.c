#include "system_clock.h"
#include "SysTick.h"
#include "system_time.h"
#include "waveform_generator.h"
#include "user_interface.h"

int main(void)
{
    system_clock_init();
    SysTick_init();
    system_time_init();
    waveform_generator_init();
    user_interface_init();

    while(1) {
        waveform_generator_update();
        user_interface_update();
    }
}