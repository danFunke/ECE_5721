#include "displayLED.h"
#include"inputButtons.h"
#include "MKL25Z4.h"

#include <stdint.h>

#define MASK(x) (1ul << (x))

void display_LED_init(void)
{
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;

    // Configure GPIO pins
    for (int i = 0; i < NUM_INPUT_BUTTONS; ++i) {
        // Set pin function as GPIO
        PORTB->PCR[i] &= ~PORT_PCR_MUX_MASK;
        PORTB->PCR[i] |= PORT_PCR_MUX(1);
    
        // Set pin as output
        PTB->PDDR |= MASK(i);

        // Set initial state to off
        PTB->PSOR |= MASK(i);
    }
}

void display_LED_update(void)
{
    uint8_t input_state = input_buttons_get_state();

    for (int i = 0; i < NUM_INPUT_BUTTONS; ++i) {
        if (input_state & MASK(i)) {
            PTB->PCOR |= MASK(i);
        } else {
            PTB->PSOR |= MASK(i);
        }
    }

}
