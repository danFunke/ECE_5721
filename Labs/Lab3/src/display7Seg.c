#include "display7Seg.h"
#include"inputButtons.h"
#include "MKL25Z4.h"

#include <stdint.h>

#define MASK(x) (1ul << (x))

enum display_leds {
    DISPLAY_LED_A,
    DISPLAY_LED_B,
    DISPLAY_LED_C,
    DISPLAY_LED_D,
    DISPLAY_LED_E,
    DISPLAY_LED_F,
    DISPLAY_LED_G,
    NUM_DISPLAY_LEDS
};

static int display_led_port_offset[NUM_DISPLAY_LEDS] = {
    [DISPLAY_LED_A] = 11,
    [DISPLAY_LED_B] = 10,
    [DISPLAY_LED_C] = 6,
    [DISPLAY_LED_D] = 5,
    [DISPLAY_LED_E] = 4,
    [DISPLAY_LED_F] = 3,
    [DISPLAY_LED_G] = 0,
};

void display_7seg_init(void)
{
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

    // Configure LED GPIO pins
    for (int i = 0; i < NUM_DISPLAY_LEDS; ++i) {
        // Set pin function as GPIO
        PORTC->PCR[display_led_port_offset[i]] &= ~PORT_PCR_MUX_MASK;
        PORTC->PCR[display_led_port_offset[i]] |= PORT_PCR_MUX(1);

        // Set pin as output
        PTC->PDDR |= MASK(display_led_port_offset[i]);

        // Set initial state to off
        PTC->PCOR |= MASK(display_led_port_offset[i]);
    }
}

void display_7seg_update(void)
{
    uint8_t input_state = input_buttons_get_state();

    switch(input_state) {
        case 0x00:
            PTC->PSOR |= MASK(display_led_port_offset[DISPLAY_LED_A]) | MASK(display_led_port_offset[DISPLAY_LED_B]) |
                         MASK(display_led_port_offset[DISPLAY_LED_C]) | MASK(display_led_port_offset[DISPLAY_LED_D]) |
                         MASK(display_led_port_offset[DISPLAY_LED_E]) | MASK(display_led_port_offset[DISPLAY_LED_F]);
            
            PTC->PCOR |= MASK(display_led_port_offset[DISPLAY_LED_G]);

            break;
        case 0x01:
            PTC->PSOR |= MASK(display_led_port_offset[DISPLAY_LED_B]) | MASK(display_led_port_offset[DISPLAY_LED_C]);

            PTC->PCOR |= MASK(display_led_port_offset[DISPLAY_LED_A]) | MASK(display_led_port_offset[DISPLAY_LED_D]) |
                         MASK(display_led_port_offset[DISPLAY_LED_E]) | MASK(display_led_port_offset[DISPLAY_LED_F]) |
                         MASK(display_led_port_offset[DISPLAY_LED_G]);
            break;
        case 0x02:
            PTC->PSOR |= MASK(display_led_port_offset[DISPLAY_LED_A]) | MASK(display_led_port_offset[DISPLAY_LED_B]) |
                         MASK(display_led_port_offset[DISPLAY_LED_D]) | MASK(display_led_port_offset[DISPLAY_LED_E]) |
                         MASK(display_led_port_offset[DISPLAY_LED_G]);
            
            PTC->PCOR |= MASK(display_led_port_offset[DISPLAY_LED_C]) | MASK(display_led_port_offset[DISPLAY_LED_F]);
            break;
        case 0x03:
            PTC->PSOR |= MASK(display_led_port_offset[DISPLAY_LED_A]) | MASK(display_led_port_offset[DISPLAY_LED_B]) |
                         MASK(display_led_port_offset[DISPLAY_LED_C]) | MASK(display_led_port_offset[DISPLAY_LED_D]) |
                         MASK(display_led_port_offset[DISPLAY_LED_G]);
            
            PTC->PCOR |= MASK(display_led_port_offset[DISPLAY_LED_E]) | MASK(display_led_port_offset[DISPLAY_LED_F]);
            break;
        case 0x04:
            PTC->PSOR |= MASK(display_led_port_offset[DISPLAY_LED_B]) | MASK(display_led_port_offset[DISPLAY_LED_C]) |
                         MASK(display_led_port_offset[DISPLAY_LED_F]) | MASK(display_led_port_offset[DISPLAY_LED_G]);

            PTC->PCOR |= MASK(display_led_port_offset[DISPLAY_LED_A]) | MASK(display_led_port_offset[DISPLAY_LED_D]) |
                         MASK(display_led_port_offset[DISPLAY_LED_E]);

            break;
        case 0x05:
            PTC->PSOR |= MASK(display_led_port_offset[DISPLAY_LED_A]) | MASK(display_led_port_offset[DISPLAY_LED_C]) |
                         MASK(display_led_port_offset[DISPLAY_LED_D]) | MASK(display_led_port_offset[DISPLAY_LED_F]) |
                         MASK(display_led_port_offset[DISPLAY_LED_G]);

            PTC->PCOR |= MASK(display_led_port_offset[DISPLAY_LED_B]) | MASK(display_led_port_offset[DISPLAY_LED_E]);
            break;
        case 0x06:
            PTC->PSOR |= MASK(display_led_port_offset[DISPLAY_LED_A]) | MASK(display_led_port_offset[DISPLAY_LED_C]) |
                         MASK(display_led_port_offset[DISPLAY_LED_D]) | MASK(display_led_port_offset[DISPLAY_LED_F]) |
                         MASK(display_led_port_offset[DISPLAY_LED_G]) | MASK(display_led_port_offset[DISPLAY_LED_E]);

            PTC->PCOR |= MASK(display_led_port_offset[DISPLAY_LED_B]);
            break;
        case 0x07:
            PTC->PSOR |= MASK(display_led_port_offset[DISPLAY_LED_A]) | MASK(display_led_port_offset[DISPLAY_LED_B]) |
                         MASK(display_led_port_offset[DISPLAY_LED_C]);

            PTC->PCOR |= MASK(display_led_port_offset[DISPLAY_LED_D]) | MASK(display_led_port_offset[DISPLAY_LED_E]) |
                         MASK(display_led_port_offset[DISPLAY_LED_F]) | MASK(display_led_port_offset[DISPLAY_LED_G]);
    
            break;
        case 0x08:
            PTC->PSOR |= MASK(display_led_port_offset[DISPLAY_LED_A]) | MASK(display_led_port_offset[DISPLAY_LED_B]) |
                         MASK(display_led_port_offset[DISPLAY_LED_C]) | MASK(display_led_port_offset[DISPLAY_LED_D]) |
                         MASK(display_led_port_offset[DISPLAY_LED_E]) | MASK(display_led_port_offset[DISPLAY_LED_F]) |
                         MASK(display_led_port_offset[DISPLAY_LED_G]);
            break;
        case 0x09:
            PTC->PSOR |= MASK(display_led_port_offset[DISPLAY_LED_A]) | MASK(display_led_port_offset[DISPLAY_LED_B]) |
                         MASK(display_led_port_offset[DISPLAY_LED_C]) | MASK(display_led_port_offset[DISPLAY_LED_D]) |
                         MASK(display_led_port_offset[DISPLAY_LED_F]) | MASK(display_led_port_offset[DISPLAY_LED_G]);

            PTC->PCOR |= MASK(display_led_port_offset[DISPLAY_LED_E]);
            break;
        case 0x0A:
            PTC->PSOR |= MASK(display_led_port_offset[DISPLAY_LED_A]) | MASK(display_led_port_offset[DISPLAY_LED_B]) |
                         MASK(display_led_port_offset[DISPLAY_LED_C]) | MASK(display_led_port_offset[DISPLAY_LED_E]) |
                         MASK(display_led_port_offset[DISPLAY_LED_F]) | MASK(display_led_port_offset[DISPLAY_LED_G]);

            PTC->PCOR |= MASK(display_led_port_offset[DISPLAY_LED_D]);
            break;
        case 0x0B:
            PTC->PSOR |= MASK(display_led_port_offset[DISPLAY_LED_C]) | MASK(display_led_port_offset[DISPLAY_LED_D]) |
                         MASK(display_led_port_offset[DISPLAY_LED_E]) | MASK(display_led_port_offset[DISPLAY_LED_F]) |
                         MASK(display_led_port_offset[DISPLAY_LED_G]);

            PTC->PCOR |= MASK(display_led_port_offset[DISPLAY_LED_A]) | MASK(display_led_port_offset[DISPLAY_LED_B]);
            break;
        case 0x0C:
            PTC->PSOR |= MASK(display_led_port_offset[DISPLAY_LED_A]) | MASK(display_led_port_offset[DISPLAY_LED_D]) |
                         MASK(display_led_port_offset[DISPLAY_LED_E]) | MASK(display_led_port_offset[DISPLAY_LED_F]);

            PTC->PCOR |= MASK(display_led_port_offset[DISPLAY_LED_B]) | MASK(display_led_port_offset[DISPLAY_LED_C]) |
                         MASK(display_led_port_offset[DISPLAY_LED_G]);
            break;
        case 0x0D:
            PTC->PSOR |= MASK(display_led_port_offset[DISPLAY_LED_B]) | MASK(display_led_port_offset[DISPLAY_LED_C]) |
                         MASK(display_led_port_offset[DISPLAY_LED_D]) | MASK(display_led_port_offset[DISPLAY_LED_E]) |
                         MASK(display_led_port_offset[DISPLAY_LED_G]);

            PTC->PCOR |= MASK(display_led_port_offset[DISPLAY_LED_A]) | MASK(display_led_port_offset[DISPLAY_LED_F]);
            break;
        case 0x0E:
            PTC->PSOR |= MASK(display_led_port_offset[DISPLAY_LED_A]) | MASK(display_led_port_offset[DISPLAY_LED_D]) |
                         MASK(display_led_port_offset[DISPLAY_LED_E]) | MASK(display_led_port_offset[DISPLAY_LED_F]) |
                         MASK(display_led_port_offset[DISPLAY_LED_G]);
            
            PTC->PCOR |= MASK(display_led_port_offset[DISPLAY_LED_B]) | MASK(display_led_port_offset[DISPLAY_LED_C]);
            break;
        case 0x0F:
            PTC->PSOR |= MASK(display_led_port_offset[DISPLAY_LED_A]) | MASK(display_led_port_offset[DISPLAY_LED_E]) |
                         MASK(display_led_port_offset[DISPLAY_LED_F]) | MASK(display_led_port_offset[DISPLAY_LED_G]);
            
            PTC->PCOR |= MASK(display_led_port_offset[DISPLAY_LED_B]) | MASK(display_led_port_offset[DISPLAY_LED_C]) |
                         MASK(display_led_port_offset[DISPLAY_LED_D]);
            break;
        default:
            break;
    }
}
