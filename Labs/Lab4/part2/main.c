#include "adc.h"
#include "display.h"
#include "ir_led.h"

#define NUM_SAMPLES_TO_AVG  (10)

#define T_DELAY_ON  (1000)
#define T_DELAY_OFF (1000)

static void delay(unsigned int time_del)
{
    time_del = 10 * time_del;
    while (time_del--) {}
}

int main(void)
{
    static int on_brightness = 0;
    static int off_brightness = 0;
    static int avg_diff;
    static int diff;
    unsigned n;

    adc_init();
    display_init();
    ir_led_init();

    while (1)
    {
        diff = 0;
        for (n = 0; n < NUM_SAMPLES_TO_AVG; n++) {
            // Measure IR level with IRLED off
            ir_led_write_state(IR_LED_OFF);
            delay(T_DELAY_OFF);
            off_brightness = adc_measure_IR();

            // Measure IR level with IRLED on
            ir_led_write_state(IR_LED_ON);
            delay(T_DELAY_ON);
            on_brightness = adc_measure_IR();

            // Calculate difference
            diff += on_brightness - off_brightness;
        }

        // Calculate average difference
        avg_diff = diff / NUM_SAMPLES_TO_AVG;

        // Light RGB LED according to range
        display_range(avg_diff);
    }
}
