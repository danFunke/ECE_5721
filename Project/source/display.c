/**
 * @file display.c
 * @author D. Funke
 * @brief Basic display driver for FRDM-KL25Z board using GPIO peripheral
 * @date 2022-11-16
 * 
 */

#include "display.h"

#include "MKL25Z4.h"
#include "system_time.h"

#define MASK(x) (1ul << (x))

enum seven_segment_leds {
    SEVEN_SEGMENT_LED_A,
    SEVEN_SEGMENT_LED_B,
    SEVEN_SEGMENT_LED_C,
    SEVEN_SEGMENT_LED_D,
    SEVEN_SEGMENT_LED_E,
    SEVEN_SEGMENT_LED_F,
    SEVEN_SEGMENT_LED_G,
    SEVEN_SEGMENT_LED_DP,
    NUM_SEVEN_SEGMENT_LEDS
};

// Buffer to hold display bitmaps
static uint8_t display_bitmaps[NUM_SEVEN_SEGMENT_DISPLAYS];

void display_init(void)
{
    // Enable clock to PORTB and PORTC
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK;

    // Configure enable pins as output GPIO, initialize high
    for (int i = 0; i < NUM_SEVEN_SEGMENT_DISPLAYS; ++i) {
        PORTB->PCR[i] &= ~PORT_PCR_MUX_MASK;
        PORTB->PCR[i] |= PORT_PCR_MUX(1);
        PTB->PDDR |= MASK(i);
        PTB->PSOR |= MASK(i);
    }

    // Configure led pins as output GPIO, initialize low
    for (int i = 0; i < NUM_SEVEN_SEGMENT_LEDS; ++i) {
        PORTC->PCR[i] &= ~PORT_PCR_MUX_MASK;
        PORTC->PCR[i] |= PORT_PCR_MUX(1);
        PTC->PDDR |= MASK(i);
        PTC->PCOR |= MASK(i);
    }

}

void display_write_seven_segment(size_t seven_segment_display_index, uint8_t encoded_bitmap)
{
    if (seven_segment_display_index < NUM_SEVEN_SEGMENT_DISPLAYS) {
        display_bitmaps[seven_segment_display_index] = encoded_bitmap;
    }
}

void display_update(void)
{
    static int display_index = 0;
    static uint32_t last_time = 0;
    uint32_t current_time = system_time_get_ms();
    
    if ((current_time - last_time) > 4) {
        last_time = current_time;
        // Clear all group enables
        for (int i = 0; i < NUM_SEVEN_SEGMENT_DISPLAYS; ++i) {
            PTB->PSOR |= MASK(i);
        }

        // Enable current index
        PTB->PCOR |= MASK(display_index);

        // Clear old contents
        PTC-> PCOR |= 0xFF;

        // Write new contents
        PTC-> PSOR |= display_bitmaps[display_index];

        display_index++;
        display_index %= NUM_SEVEN_SEGMENT_DISPLAYS;
    }
}
