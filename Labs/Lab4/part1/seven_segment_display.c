#include "seven_segment_display.h"

#include <MKL25Z4.h>

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

void seven_segment_display_init(void)
{
    // Enable clock to PORTC and PORTD
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK;

    // Configure PORTC led pins as output GPIO, initialize low
    for (int i = 0; i < NUM_SEVEN_SEGMENT_LEDS; ++i) {
        PORTC->PCR[i] &= ~PORT_PCR_MUX_MASK;
        PORTC->PCR[i] |= PORT_PCR_MUX(1);
        PTC->PDDR |= MASK(i);
        PTC->PCOR |= MASK(i);
    }

    // Configure PORTD led pins as output GPIO, initialize low
    for (int i = 0; i < NUM_SEVEN_SEGMENT_LEDS; ++i) {
        PORTD->PCR[i] &= ~PORT_PCR_MUX_MASK;
        PORTD->PCR[i] |= PORT_PCR_MUX(1);
        PTD->PDDR |= MASK(i);
        PTD->PCOR |= MASK(i);
    }

}

void seven_segment_display_print_0(uint8_t encoded_val)
{
        // Clear old contents
        PTC-> PCOR |= 0xFF;

        // Write new contents
        PTC-> PSOR |= encoded_val;
}

void seven_segment_display_print_1(uint8_t encoded_val)
{
        // Clear old contents
        PTD-> PCOR |= 0xFF;

        // Write new contents
        PTD-> PSOR |= encoded_val;
}