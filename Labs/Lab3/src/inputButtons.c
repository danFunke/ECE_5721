#include "inputButtons.h"
#include "MKL25Z4.h"

#include <stdbool.h>

#define MASK(x) (1ul << (x))

static int input_button_port_offset[NUM_INPUT_BUTTONS] = {
    [INPUT_BUTTON_0] = 0,
    [INPUT_BUTTON_1] = 1,
    [INPUT_BUTTON_2] = 2,
    [INPUT_BUTTON_3] = 3,
};

static bool input_button_state[NUM_INPUT_BUTTONS];

void input_buttons_init(void)
{
    // Enable clock to Port D
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;

    // Configure GPIO pins and button state
    for (int i = 0; i < NUM_INPUT_BUTTONS; ++i) {
        // Set pin function as GPIO
        PORTD->PCR[input_button_port_offset[i]] &= ~PORT_PCR_MUX_MASK;
        PORTD->PCR[input_button_port_offset[i]] |= PORT_PCR_MUX(1);

        // Enable pull-up resistor
        PORTD->PCR[input_button_port_offset[i]] |= PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;
        
        // Enable interrupts on rising edge
        PORTD->PCR[input_button_port_offset[i]] |= PORT_PCR_IRQC(0x0a);
    
        // Set pin as input
        PTD->PDDR &= ~(MASK(input_button_port_offset[i]));

        // Set initial state to false
        input_button_state[i] = false;
    }
    
    // Initialize interrupt
    NVIC_SetPriority(PORTD_IRQn, 2);
    NVIC_ClearPendingIRQ(PORTD_IRQn);
    NVIC_EnableIRQ(PORTD_IRQn);
}

uint8_t input_buttons_get_state(void)
{
    uint8_t state = 0;

    for (int i = 0; i < NUM_INPUT_BUTTONS; ++i) {
        if (input_button_state[i]) {
            state |= MASK(i);
        }
    }

    return state;
}

void input_buttons_set_state(int button_index)
{
    input_button_state[button_index] = !input_button_state[button_index];
}
