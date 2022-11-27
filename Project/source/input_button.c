/**
 * @file input_button.c
 * @author D. Funke
 * @brief 
 * @date 2022-11-22
 * 
 */

#include "input_button.h"
#include "waveform_generator.h"

#include <stdint.h>
#include <MKL25Z4.h>

#define MASK(x) (1ul << (x))

void input_button_init(void)
{
    // Enable clock to Port D
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;

    // Configure GPIO pins and button state
    for (int i = 0; i < NUM_INPUT_BUTTONS; ++i) {
        // Set pin function as GPIO
        PORTD->PCR[i] &= ~PORT_PCR_MUX_MASK;
        PORTD->PCR[i] |= PORT_PCR_MUX(1);

        // Enable pull-up resistor
        PORTD->PCR[i] |= PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;
        
        // Enable interrupts on rising edge
        PORTD->PCR[i] |= PORT_PCR_IRQC(0x0a);
    
        // Set pin as input
        PTD->PDDR &= ~(MASK(i));
    }

    // Initialize interrupt
    NVIC_SetPriority(PORTD_IRQn, 2);
    NVIC_ClearPendingIRQ(PORTD_IRQn);
    NVIC_EnableIRQ(PORTD_IRQn);
}

void PORTD_IRQHandler(void) 
{
    // If input button 0 is pressed
    if (PORTD->ISFR & MASK(INC_DELTA)) {
        waveform_generator_increment_amplitude(DELTA_WAVE);
    }

    // If input button 1 is pressed
    if (PORTD->ISFR & MASK(DEC_DELTA)) {
        waveform_generator_decrement_amplitude(DELTA_WAVE);
    }

    // If input button 2 is pressed
    if (PORTD->ISFR & MASK(INC_THETA)) {
        waveform_generator_increment_amplitude(THETA_WAVE);
    }

    // If input button 3 is pressed
    if (PORTD->ISFR & MASK(DEC_THETA)) {
        waveform_generator_decrement_amplitude(THETA_WAVE);
    }

    // If input button 4 is pressed
    if (PORTD->ISFR & MASK(INC_ALPHA)) {
        waveform_generator_increment_amplitude(ALPHA_WAVE);
    }

    // If input button 5 is pressed
    if (PORTD->ISFR & MASK(DEC_ALPHA)) {
        waveform_generator_decrement_amplitude(ALPHA_WAVE);
    }

    // If input button 7 is pressed
    if (PORTD->ISFR & MASK(INC_BETA)) {
        waveform_generator_increment_amplitude(BETA_WAVE);
    }

    // If input button 7 is pressed
    if (PORTD->ISFR & MASK(DEC_BETA)) {
        waveform_generator_decrement_amplitude(BETA_WAVE);
    }

    // Clear status flags
    PORTD->ISFR = 0xffffffff;
}
