#include "ir_led.h"
#include "MKL25Z4.h"

#define IR_LED_POS  (1)

#define MASK(x) (1ul << (x))

void ir_led_init(void)
{
    // Enable clock to PORTB
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;

    // Set IR pin to GPIO
    PORTB->PCR[IR_LED_POS] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[IR_LED_POS] |= PORT_PCR_MUX(1);

    // Set pin as output
    PTB->PDDR |= MASK(IR_LED_POS);

    // Initialize state to off
    ir_led_write_state(IR_LED_OFF);
}

void ir_led_write_state(int state)
{
    if (state == IR_LED_OFF) {
        PTB->PSOR = MASK(IR_LED_POS);
    } else {
        PTB->PCOR = MASK(IR_LED_POS);
    }
}
