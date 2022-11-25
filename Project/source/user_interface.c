#include "user_interface.h"
#include "display.h"
#include "seven_segment_display_encode.h"
#include "waveform_generator.h"

#include <stdint.h>

void user_interface_update(void)
{
    for (int i = 0; i < NUM_COMPONENT_WAVES; ++i) {
        int wave_val = waveform_generator_get_amplitude(i);
        char display_val = (char)wave_val + '0';
        uint8_t encoded_val = seven_segment_display_encode_character(display_val);
        display_write_seven_segment(i, encoded_val);
    }
}