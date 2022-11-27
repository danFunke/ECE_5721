#include "adc.h"

#include "MKL25Z4.h" 

#define SAMPLING_TIME (84000) //4 ms interrupts


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
    ADC0->CFG1 = ADC_CFG1_ADLPC_MASK | ADC_CFG1_ADLSMP_MASK | ADC_CFG1_MODE(3) | ADC_CFG1_ADICLK(0);

    //software trigger, compare function disabled, DMA enabled 
    //voltage references VREFH and VREFL
    // ADC0->SC2 = ADC_SC2_REFSEL | ADC_SC2_DMAEN; //TODO add back to enable DMA
    ADC0->SC2 = ADC_SC2_REFSEL(0);
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
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk; 
}

void SysTick_Handler(void)
{
    //trigger adc conversion here
    ADC0->SC1[0] = 0x00; //start conversion

}
