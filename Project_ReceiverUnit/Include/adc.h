#ifndef ADC_H
#define ADC_H

#include <stdint.h>

#define ADC_POS 20
#define DFT_SAMPLES 250				//number of samples in the DFT

void adc_init(void);

void systick_init(void);

void SysTick_Handler(void);

void ADC0_IRQHandler(void);

void retrieve_samples(uint16_t* dest);

#endif
