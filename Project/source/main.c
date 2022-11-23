#include "system_time.h"
#include "SysTick.h"
#include "display.h"
#include <stdint.h>
#include "seven_segment_display_encode.h"
#include "waveform_generator.h"
#include "input_button.h"


static void counter_update(void) {
    static char counter_1 = '0';
    static char counter_2 = '0';
    static char counter_3 = '0';
    static int delta_1 = 1;
    static int delta_2 = 1;
    static int delta_3 = 1;
    static uint32_t last_time = 0;
    uint32_t current_time = system_time_get_ms();

    if ((current_time - last_time) >= 1000) {
        last_time = current_time;
        
        // Update counters
        counter_1 = counter_1 + delta_1;
        counter_2 = counter_2 + delta_2;
        counter_3 = counter_3 + delta_3;
        
        // Update Deltas
        if (counter_1 == '9') {
            delta_1 = -1;
        } else if (counter_1 == '0') {
            delta_1 = 1;
        }

        if (counter_2 == '4') {
            delta_2 = -1;
        } else if (counter_2 == '0') {
            delta_2 = 1;
        }

        if (counter_3 == '7') {
            delta_3 = -1;
        } else if (counter_3 == '0') {
            delta_3 = 1;
        }

        // Write counters to display
        uint8_t encoded_bitmap_1 = seven_segment_display_encode_character(counter_1);
        uint8_t encoded_bitmap_2 = seven_segment_display_encode_character(counter_2);
        uint8_t encoded_bitmap_3 = seven_segment_display_encode_character(counter_3);
        display_write_seven_segment(SEVEN_SEGMENT_DISPLAY_0, encoded_bitmap_1);
        display_write_seven_segment(SEVEN_SEGMENT_DISPLAY_1, encoded_bitmap_2);
        display_write_seven_segment(SEVEN_SEGMENT_DISPLAY_2, encoded_bitmap_3);
    }
}

#include <stdio.h>
#include <string.h>
void amplitude_display_update(void)
{
    uint8_t amp_val = waveform_generator_get_amplitude(DELTA);
    char display_val = (char)amp_val + '0';
    //memset(display_buffer, 0, 1);
    //snprintf(display_buffer, 1, "%d", amp_val);
    uint8_t encoded = seven_segment_display_encode_character(display_val);
    display_write_seven_segment(SEVEN_SEGMENT_DISPLAY_0, encoded);
    
}


int main(void)
{
    system_time_init();
    SysTick_Init();
    display_init();
    waveform_generator_init();
    input_button_init();

    while(1) {
        display_update();
        //counter_update();
        amplitude_display_update();
    }
}
