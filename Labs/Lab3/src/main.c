#include "inputButtons.h"
#include "displayLED.h"
#include "display7Seg.h"
#include "MKL25Z4.h"
#include <stdint.h>


#define MASK(x) (1ul << (x))

void PORTD_IRQHandler(void)
{
    // If input button 1 is pressed
    if (PORTD->ISFR & MASK(INPUT_BUTTON_0)) {
        input_buttons_set_state(INPUT_BUTTON_0);
    }

    // If input button 2 is pressed
    if (PORTD->ISFR & MASK(INPUT_BUTTON_1)) {
        input_buttons_set_state(INPUT_BUTTON_1);
    }

    // If input button 3 is pressed
    if (PORTD->ISFR & MASK(INPUT_BUTTON_2)) {
        input_buttons_set_state(INPUT_BUTTON_2);
    }

    // If input button 4 is pressed
    if (PORTD->ISFR & MASK(INPUT_BUTTON_3)) {
        input_buttons_set_state(INPUT_BUTTON_3);
    }

    // Clear status flags
    PORTD->ISFR = 0xffffffff;
}


int main(void)
{
    input_buttons_init();
    display_LED_init();
    display_7seg_init();

    __enable_irq();

    while(1) {
        display_LED_update();
        display_7seg_update();
    }
}
