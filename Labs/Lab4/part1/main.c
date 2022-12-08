#include "adc.h"
#include "seven_segment_display_encode.h"
#include "seven_segment_display.h"

#include <stdio.h>
#include <string.h>

#define BUF_SIZE    (3)
int main(void)
{
    adc_init();
    seven_segment_display_init();

    float temp;
    int temp_int;
    char display_buffer[BUF_SIZE];
    memset(display_buffer, 0, BUF_SIZE);
    char encoded_val_0;
    char encoded_val_1;

    while(1)
    {
        temp = adc_read_temperature();
        temp_int = (int)temp;
        snprintf(display_buffer, BUF_SIZE, "%2d", temp_int);
        encoded_val_0 = seven_segment_display_encode_character(display_buffer[1]);
        encoded_val_1 = seven_segment_display_encode_character(display_buffer[0]);
        seven_segment_display_print_0(encoded_val_0);
        seven_segment_display_print_1(encoded_val_1);
    }
}
