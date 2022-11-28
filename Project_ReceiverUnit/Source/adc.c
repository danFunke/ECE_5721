#include "adc.h"

#include "MKL25Z4.h" 
#include <stdio.h>

#define SAMPLING_TIME (84000) //4 ms interrupts

extern volatile uint8_t m_calculate_dft;

uint16_t temp_samples[DFT_SAMPLES];
static uint16_t sample_index = 0u; 

void adc_init(void)
{
    //enable clock to adc and the input GPIO
    SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

    //select analog for the pin
    PORTE->PCR[ADC_POS] &= PORT_PCR_MUX_MASK;
    PORTE->PCR[ADC_POS] |= PORT_PCR_MUX(0);

    //low power configuration, long sample time, 16-bit single-ended conversion
    //bus clock input
    ADC0->CFG1 = ADC_CFG1_ADLPC_MASK | 
                    ADC_CFG1_ADLSMP_MASK | 
                    ADC_CFG1_MODE(3) | 
                    ADC_CFG1_ADICLK(0);

    //software trigger, compare function disabled, DMA enabled 
    //voltage references VREFH and VREFL
    ADC0->SC2 = ADC_SC2_REFSEL(0);
                // ADC_SC2_DMAEN_MASK;
	
		//configure interrupts
    NVIC_SetPriority(ADC0_IRQn, 3); //TODO should the priority be higher
    NVIC_ClearPendingIRQ(ADC0_IRQn);
    NVIC_EnableIRQ(ADC0_IRQn);
}

void systick_init(void)
{
    //reload value
    SysTick->LOAD = (SAMPLING_TIME);
    
    //configure interrupts
    NVIC_SetPriority(SysTick_IRQn, 3); //TODO should the priority be higher
    NVIC_ClearPendingIRQ(SysTick_IRQn);
    NVIC_EnableIRQ(SysTick_IRQn);

    //force load of reload value
    SysTick->VAL = 0; 

    //enable interrupt, enable systick timer, use master clock source
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | 
                    SysTick_CTRL_TICKINT_Msk | 
                    SysTick_CTRL_ENABLE_Msk; 
}

void SysTick_Handler(void)
{
    //trigger adc conversion here with completion interrupt enabled
    ADC0->SC1[0] = ADC_SC1_AIEN_MASK;
    //ADC0->SC1[0] = 0x00; //start conversion

}

void ADC0_IRQHandler(void)
{
    //DMA0->DMA[0].DCR |= DMA_DCR_START_MASK;
    if (sample_index >= (DFT_SAMPLES - 1))
    {
        sample_index = 0;
        m_calculate_dft = 0x01;
    }

    temp_samples[sample_index] = (uint16_t)ADC0->R[0];
    sample_index++;
}

void retrieve_samples(uint16_t* dest)
{
    memcpy(dest, temp_samples, DFT_SAMPLES);
}
