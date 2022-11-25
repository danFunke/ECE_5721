#include "system_clock.h"

#include "system_time.h"
#include "SysTick.h"
#include "display.h"
#include "seven_segment_display_encode.h"
#include "waveform_generator.h"
#include "input_button.h"

#include <stdint.h>

int main(void)
{
    system_clock_init();
    SysTick_Init();
    system_time_init();
    waveform_generator_init();
    display_init();
    input_button_init();

    while(1) {
        waveform_generator_update();
        display_update();
        user_interface_update();
    }
}
