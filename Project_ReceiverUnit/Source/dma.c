#include "dma.h"

#include "MKL25Z4.h" 

void dma_init(void)
{
    //enable clock to DMA
    SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
    SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

    //disable DMA channel to allow for cfg
    DMAMUX0->CHCFG[0] = 0;

    //generate DMA interrupt when done
    //increment source, transfer words (16 bits)
    //enable peripheral request
    DMA0->DMA[0].DCR = DMA_DCR_EINT_MASK | DMA_DCR_DINC_MASK | DMA_DCR_SSIZE(2) | DMA_DCR_DSIZE(2) | DMA_DCR_ERQ_MASK | DMA_DCR_CS_MASK;

    //configure interrupts
    NVIC_SetPriority(DMA0_IRQn, 2); //TODO should the priority be higher
    NVIC_ClearPendingIRQ(DMA0_IRQn);
    NVIC_EnableIRQ(DMA0_IRQn);

    //set DMA MUX to use ADC interrupt as trigger
    DMAMUX0->CHCFG[0] = DMAMUX_CHCFG_SOURCE(40); 
}
